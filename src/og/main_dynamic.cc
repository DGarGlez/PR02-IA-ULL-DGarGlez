#include "./include/aux_functions.h"
#include "./include/cell.h"
#include "./include/labyrinth.h"
#include <cstdlib>
#include <random>
#include <chrono>

// Actualiza el laberinto dinámicamente según las reglas
void UpdateDynamicObstacles(Labyrinth& labyrinth, double pin, double pout) {
    int rows = labyrinth.GetRows();
    int cols = labyrinth.GetColumns();
    int max_obstacles = (rows * cols) * 0.25;
    int obstacles = 0;
    std::vector<std::pair<int, int>> obstacle_positions;
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    // Obtener posiciones de inicio y destino
    std::pair<int, int> start_pos = labyrinth.GetStartNode().GetPos();
    std::pair<int, int> end_pos = labyrinth.GetEndNode().GetPos();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Nunca bloquear inicio ni destino
            if ((i == start_pos.first && j == start_pos.second) || (i == end_pos.first && j == end_pos.second)) continue;
            Cell& cell = labyrinth.Node({i, j});
            double u = dist(rng);
            // 50% de probabilidad de cambiar de estado
            if (u < 0.5) {
                // Cambia de estado
                if (cell.GetKind() == 0) {
                    cell.SetKind(1); // Libre a obstáculo
                    obstacles++;
                    obstacle_positions.push_back({i, j});
                } else if (cell.GetKind() == 1) {
                    cell.SetKind(0); // Obstáculo a libre
                }
            } else {
                // Mantiene el estado
                if (cell.GetKind() == 1) {
                    obstacles++;
                    obstacle_positions.push_back({i, j});
                }
            }
        }
    }
    // Si hay demasiados obstáculos, elimina aleatoriamente
    while (obstacles > max_obstacles) {
        int idx = rng() % obstacle_positions.size();
        auto [i, j] = obstacle_positions[idx];
        Cell& cell = labyrinth.Node({i, j});
        if (cell.GetKind() == 1) {
            cell.SetKind(0);
            obstacles--;
        }
        obstacle_positions.erase(obstacle_positions.begin() + idx);
    }
}

int main(int argc, char* argv[]) {
    Uso(argc, argv);
    std::string nombre_fichero{argv[1]};
    std::ifstream fichero_entrada{nombre_fichero, std::ios_base::in};
    if (fichero_entrada.fail()) {
        std::cerr << RED << BOLD << "Fallo al abrir el fichero de entrada.\n" << RESET;
        return 1;
    }
    Labyrinth labyrinth(fichero_entrada);
    double pin = 0.5, pout = 0.5;
    int pasos = 0, reintentos = 0, total_generados = 0, total_inspeccionados = 0;
    double suma_proporcion_obstaculos = 0.0;
    bool destino_alcanzado = false;
    Cell agente = labyrinth.GetStartNode();
    std::pair<int, int> start_pos_fijo = labyrinth.GetStartNode().GetPos();
    std::pair<int, int> end_pos_fijo = labyrinth.GetEndNode().GetPos();

    while (!destino_alcanzado) {
        // Mantener el punto inicial y final fijos
        labyrinth.Node(start_pos_fijo).SetKind(3); // Marcar inicio fijo
        labyrinth.Node(end_pos_fijo).SetKind(4);   // Marcar destino fijo

        // Ejecutar A* desde la posición actual del agente
        std::pair<int, int> start_pos = agente.GetPos();
        Instance resultado = labyrinth.AStarSearch();
        int intentos_actual = 0;
        // Si no hay camino, reintentar hasta 5 veces tras actualizar el laberinto
        while (resultado.path.size() == 0 && intentos_actual < 5) {
            UpdateDynamicObstacles(labyrinth, pin, pout);
            labyrinth.Node(start_pos_fijo).SetKind(3);
            labyrinth.Node(end_pos_fijo).SetKind(4);
            resultado = labyrinth.AStarSearch();
            intentos_actual++;
            reintentos++;
        }
        if (resultado.path.size() == 0) {
            std::cout << RED << BOLD << "Destino inalcanzable tras 5 reintentos.\n" << RESET;
            break;
        }
        // Imprimir laberinto y camino
        std::cout << GREEN << BOLD << "\nPaso " << pasos+1 << ":\n" << RESET;
        // Imprimir la posición del agente como 'A' en el laberinto
        std::string lab_print = labyrinth.PrintLabyrinth({}, {}, agente, resultado.path);
        std::pair<int,int> pos_agente = agente.GetPos();
        int fila = pos_agente.first;
        int columna = pos_agente.second;
        int fila_actual = 0, col_actual = 0;
        std::stringstream lab_modificado;
        for (char c : lab_print) {
            if (c == '\n') {
                fila_actual++;
                col_actual = 0;
                lab_modificado << c;
                continue;
            }
            if (fila_actual == fila && col_actual == columna) {
                lab_modificado << 'A';
            } else if (c == 'I') {
                lab_modificado << 'I'; // El inicio siempre se muestra como 'I' si el agente no está ahí
            } else {
                lab_modificado << c;
            }
            col_actual++;
        }
        std::cout << lab_modificado.str() << std::endl;
        std::cout << "Camino óptimo: ";
        for (const auto& cell : resultado.path) std::cout << cell.GetPosString() << " ";
        std::cout << "\nCoste: " << resultado.path.back().GetGValue() << std::endl;
        // Métricas
        total_generados += resultado.generated.size();
        total_inspeccionados += resultado.visited.size();
        pasos++;
        // Proporción de obstáculos
        int obstaculos = 0;
        for (int i = 0; i < labyrinth.GetRows(); ++i)
            for (int j = 0; j < labyrinth.GetColumns(); ++j)
                if (labyrinth.Node({i, j}).GetKind() == 1) obstaculos++;
        double prop = (double)obstaculos / (labyrinth.GetRows() * labyrinth.GetColumns());
        suma_proporcion_obstaculos += prop;
        // Avanzar agente solo una casilla
        if (resultado.path.size() > 1) {
            // Limpiar la posición anterior del agente (si no es el inicio fijo)
            if (start_pos != start_pos_fijo) labyrinth.Node(start_pos).SetKind(0);
            Cell agente_anterior = agente;
            agente = resultado.path[1]; // El agente avanza al siguiente nodo
            // Reflejar la nueva posición en el laberinto
            labyrinth.Node(agente.GetPos()).SetKind(3);
            // Si el agente no avanza, terminar para evitar bucle infinito
            if (agente.GetPos() == agente_anterior.GetPos()) {
                std::cout << RED << BOLD << "\nEl agente no puede avanzar más. Fin de la ejecución.\n" << RESET;
                break;
            }
        } else {
            agente = resultado.path[0]; // Ya está en el destino
            destino_alcanzado = true;
            labyrinth.Node(agente.GetPos()).SetKind(3);
            std::cout << GREEN << BOLD << "\n¡Destino alcanzado!\n" << RESET;
        }
        // Mantener inicio y destino fijos tras cada actualización
        labyrinth.Node(start_pos_fijo).SetKind(3);
        labyrinth.Node(end_pos_fijo).SetKind(4);
        // Si el agente está en el destino, terminar
        if (agente.GetPos() == end_pos_fijo) {
            destino_alcanzado = true;
            std::cout << GREEN << BOLD << "\n¡Destino alcanzado!\n" << RESET;
        }
    }
    // Imprimir métricas finales
    std::cout << YELLOW << BOLD << "\nMétricas finales:\n" << RESET;
    std::cout << "Pasos realizados: " << pasos << std::endl;
    std::cout << "Reintentos sin éxito: " << reintentos << std::endl;
    std::cout << "Nodos generados totales: " << total_generados << std::endl;
    std::cout << "Nodos inspeccionados totales: " << total_inspeccionados << std::endl;
    std::cout << "Proporción media de obstáculos: " << (suma_proporcion_obstaculos/pasos) << std::endl;
    return 0;
}
