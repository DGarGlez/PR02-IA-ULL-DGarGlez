#include "./include/aux_functions.h"
#include "./include/cell.h"
#include "./include/labyrinth.h"

/**
 * @brief Uso del programa
 * 
 * @param argc 
 * @param argv 
 */
void Uso(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << RED << BOLD << "Error: Parámetros inválidos.\n" << RESET << GRAY << ITALIC << "Prueba " << RESET << GRAY << BOLD << "'./program <Ruta_input>.txt'\n";
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Función que imprime el menú
 * 
 */
void ImprimirMenu() {
    std::cout << GRAY << BOLD << "Menú de opciones:\n" << RESET;
    std::cout << BOLD << PINK << "1. " << RESET << "Búsqueda A* estática\n";
    std::cout << BOLD << PINK << "2. " << RESET << "Cambiar casilla inicial\n";
    std::cout << BOLD << PINK << "3. " << RESET << "Cambiar casilla final\n";
    std::cout << BOLD << PINK << "4. " << RESET << "Cambiar heurística\n";
    std::cout << BOLD << PINK << "5. " << RESET << "Imprimir laberinto\n";
    std::cout << BOLD << PINK << "6. " << RESET << "Cambiar fichero de entrada\n";
    std::cout << BOLD << PINK << "7. " << RESET << "Búsqueda A* dinámica\n";
    std::cout << BOLD << PINK << "8. " << RESET << "Búsqueda A* modificada\n";
    std::cout << BOLD << PINK << "9. " << RESET << "Salir\n";
}

/**
 * @brief Función que convierte un vector de celdas a un string
 * 
 * @param vector 
 * @return std::string 
 */
std::string VectorToString(CellVector vector) {
    std::string result;
    if (vector.size() == 0) return "No path";  // Si no hay camino
    for (int i = 0; i < vector.size(); i++) {
        result += vector[i].GetPosString();  // Añade la posición del nodo de la forma (x,y)
        if (i != vector.size() - 1) result += " - "; // Añade un guión entre nodos
    }
    return result;
}

/**
 * @brief Función que centra un texto en una cadena
 * 
 * @param text 
 * @param width 
 * @return std::string 
 */
std::string CenterText(const std::string& text, int width) {
    int padding = width - text.size();
    int padding_left = padding / 2;
    int padding_right = padding - padding_left;
    return std::string(padding_left, ' ') + text + std::string(padding_right, ' ');
}

/**
 * @brief Función que almacena la búsqueda en un archivo
 * 
 * @param labyrinth 
 * @param instance_name 
 * @return std::ofstream 
 */
std::ofstream StoreSearch(Labyrinth& labyrinth, std::string& instance_name) {
    std::ofstream output_file;
    if (!std::filesystem::exists("output")) {
        std::filesystem::create_directory("output");
    }
    output_file.open("output/instancias.md", std::ios_base::app);  // Abre el fichero en modo append

    std::string id = instance_name.substr(11);  // Obtiene el identificador de la instancia

    // Realizamos la búsqueda
    Instance table = labyrinth.AStarSearch();

    std::cout << "\nResultado de la búsqueda A* estática:\n";
    if (table.path.size() == 0) {
        std::cout << RED << BOLD << "No se ha encontrado un camino al destino.\n" << RESET;
    } else {
        std::cout << GREEN << BOLD << "Camino encontrado:\n" << RESET;
        for (const auto& cell : table.path) {
            std::cout << cell.GetPosString() << " ";
        }
        std::cout << "\nCoste del camino: " << table.path.back().GetGValue() << "\n";
    }

    // Extraemos la información
    std::string path = VectorToString(table.path);  // Convierte el camino a string
    int generados = table.generated.size();
    int visitados = table.visited.size();
    int cost = 0;
    std::string dibujo = table.dibujo;

    // Si hay camino, obtenemos el coste
    if (path != "No path") cost = table.path.back().GetGValue();

    // Ancho fijo para cada columna
    const int col_widths[] = {10, 5, 5, 7, 20, 22};

    // Cabecera de la tabla
    output_file << "\n";
    output_file << "| " << CenterText("Instancia", col_widths[0])
                << " | " << CenterText("n", col_widths[1])
                << " | " << CenterText("m", col_widths[2])
                << " | " << CenterText("Coste", col_widths[3])
                << " | " << CenterText("Nodos Generados", col_widths[4])
                << " | " << CenterText("Nodos inspeccionados", col_widths[5]) << " |\n";

    output_file << "|-" << std::string(col_widths[0], '-') << "-|-" 
                << std::string(col_widths[1], '-') << "-|-" 
                << std::string(col_widths[2], '-') << "-|-" 
                << std::string(col_widths[3], '-') << "-|-" 
                << std::string(col_widths[4], '-') << "-|-" 
                << std::string(col_widths[5], '-') << "-|\n";

    // Contenido de la tabla
    output_file << "| " << CenterText(id, col_widths[0])
                << " | " << CenterText(std::to_string(labyrinth.GetRows()), col_widths[1])
                << " | " << CenterText(std::to_string(labyrinth.GetColumns()), col_widths[2])
                << " | " << CenterText(std::to_string(cost), col_widths[3])
                << " | " << CenterText(std::to_string(generados), col_widths[4])
                << " | " << CenterText(std::to_string(visitados), col_widths[5]) << " |\n\n";

    output_file << "S: " << labyrinth.GetStartNode().GetPosString() << "\n";
    output_file << "E: " << labyrinth.GetEndNode().GetPosString() << "\n";
    output_file << "Camino: " << path << "\n";

    // Añadimos otros datos adicionales
    output_file << "\n" << dibujo << "\n\n";
    output_file << "Iteraciones: \n\n" << table.iteraciones << "\n\n";

    // Cerramos el archivo
    output_file.close();
    return output_file;
}

/**
 * @brief Función que almacena la búsqueda dinámica en un archivo
 * 
 * @param labyrinth 
 * @param instance_name 
 * @return std::ofstream 
 */
std::ofstream StoreSearchDynamic(Labyrinth& labyrinth, std::string& instance_name) {
    std::ofstream output_file;
    if (!std::filesystem::exists("output")) {
        std::filesystem::create_directory("output");
    }
    output_file.open("output/instancias_dinamicas.md", std::ios_base::app);  // Abre el fichero en modo append

    std::string id = instance_name.substr(11);  // Obtiene el identificador de la instancia

    Labyrinth labyrinth_aux = labyrinth;  // Hacemos una copia del laberinto original para mostrar la ruta recorrida
    Instance table_final;  // Instancia final de la búsqueda dinámica

    Cell inicial = labyrinth.GetStartNode(); // Guardamos el nodo inicial original
    int generados_totales = 0; // Contador de nodos generados totales
    int visitados_totales = 0; // Contador de nodos visitados totales

    srand(time(NULL)); // Semilla para la generación aleatoria
    int probabilidad = 1;  // Probabilidad de cambiar un nodo (0-100)
    int max_muros = (labyrinth.GetRows() * labyrinth.GetColumns()) * 0.2; // Máximo número de muros permitidos
    int num_muros = 0;  // Contador de muros actuales
    for (int i = 0; i < labyrinth.GetRows(); i++) {   // Recorremos las filas
        for (int j = 0; j < labyrinth.GetColumns(); j++) {  // Recorremos las columnas
            if (labyrinth.GetLabyrinth()[i][j].GetKind() == 1) {
                num_muros++; // Contamos los muros iniciales
            }
        }
    }

    // Realizamos la búsqueda
    Instance table = labyrinth.AStarSearch();

    generados_totales += table.generated.size();
    visitados_totales += table.visited.size();

    if (table.path.size() == 0) {
        std::cout << RED << BOLD << "No se ha encontrado un camino al destino.\n" << RESET;
        return output_file; // Si no hay camino, salimos de la función
    }

    table_final.path.push_back(table.path[0]);  // Añadimos el nodo inicial al camino total
    table_final.path.push_back(table.path[1]);  // Añadimos el nodo del primer paso al camino total

    // Guardamos el coste hasta el primer paso
    int coste_final = table.path[1].GetGValue();

    // Contador de iteraciones
    int iter = 0;

    // Contador de iteraciones si no se encuentra camino
    int iter_no_path = 0;

    // mientras el path sea mayor que 2 (mientras no lleguemos al destino) y iter_no_path < 5, cambiamos los obstaculos y realizamos la búsqueda de nuevo
    while (table.path.size() > 2 && iter_no_path < 5) {

        // Marcamos el nodo inicial original en el laberinto auxiliar
        std::pair<int,int> prev_start_pos_aux = labyrinth_aux.GetStartNode().GetPos();      // Guardar la posición anterior
        labyrinth_aux.Node(prev_start_pos_aux).SetKind(7);                                  // Quitar el tipo 3 del nodo anterior
        std::pair<int,int> new_start_pos_aux = inicial.GetPos();                            // Obtener la nueva posición para el nodo inicial
        labyrinth_aux.Node(new_start_pos_aux) = inicial;                                    // Copiar los datos del nuevo nodo inicial
        labyrinth_aux.Node(new_start_pos_aux).SetKind(3);                                   // Establecer el tipo 3 en el nuevo nodo inicial
        labyrinth_aux.SetStartNode(labyrinth_aux.Node(new_start_pos_aux));                  // Actualizar el puntero del nodo inicial en el objeto Labyrinth

        // Imprimomos el laberinto con el camino actual
        output_file << "\nLaberinto con el camino actual (Iteración " << iter++ << "):\n";
        // Recorremos el laberinto auxiliar para marcar el camino final
        for (int i = 0; i < labyrinth_aux.GetRows(); i++) {   // Recorremos las filas
            for (int j = 0; j < labyrinth_aux.GetColumns(); j++) {  // Recorremos las columnas
                for (int k = 0; k < table_final.path.size(); k++) {
                    if (labyrinth_aux.GetLabyrinth()[i][j].GetPos() == table_final.path[k].GetPos() && labyrinth_aux.GetLabyrinth()[i][j].GetKind() != 3 && labyrinth_aux.GetLabyrinth()[i][j].GetKind() != 4) {
                        labyrinth_aux.Node({i, j}).SetKind(7); // Marcamos el camino final con un 7
                    }
                }
            }
        }
        output_file << labyrinth_aux.PrintLabyrinth() << "\n";

        // Cambiamos la posición del nodo inicial al segundo nodo del camino encontrado
        std::pair<int,int> prev_start_pos = labyrinth.GetStartNode().GetPos();  // Guardar la posición anterior
        labyrinth.Node(prev_start_pos).SetKind(1);                              // Quitar el tipo 3 del nodo anterior
        std::pair<int,int> new_start_pos = table.path[1].GetPos();              // Obtener la nueva posición para el nodo inicial
        labyrinth.Node(new_start_pos) = table.path[1];                          // Copiar los datos del nuevo nodo inicial
        labyrinth.Node(new_start_pos).SetKind(3);                               // Establecer el tipo 3 en el nuevo nodo inicial
        labyrinth.SetStartNode(labyrinth.Node(new_start_pos));                  // Actualizar el puntero del nodo inicial en el objeto Labyrinth

        // Actualizamos los obstáculos dinámicamente
        std::vector<std::pair<int, int>> obstaculos_actuales;
        num_muros = 0;
        for (int i = 0; i < labyrinth.GetRows(); i++) {
            for (int j = 0; j < labyrinth.GetColumns(); j++) {
                if (labyrinth.GetLabyrinth()[i][j].GetPos() == labyrinth.GetStartNode().GetPos() ||
                    labyrinth.GetLabyrinth()[i][j].GetPos() == labyrinth.GetEndNode().GetPos()) continue;
                // Decidir aleatoriamente si cambiar el estado
                if (rand() % 2 == 0) {
                    if (labyrinth.GetLabyrinth()[i][j].GetKind() == 0) {
                        labyrinth.Node({i, j}).SetKind(1);
                    } else if (labyrinth.GetLabyrinth()[i][j].GetKind() == 1) {
                        labyrinth.Node({i, j}).SetKind(0);
                    }
                }
                // Contar obstáculos tras el cambio
                if (labyrinth.GetLabyrinth()[i][j].GetKind() == 1) {
                    num_muros++;
                    obstaculos_actuales.push_back({i, j});
                }
            }
        }
        // Si hay demasiados obstáculos, elimina aleatoriamente hasta cumplir el límite
        while (num_muros > max_muros && !obstaculos_actuales.empty()) {
            int idx = rand() % obstaculos_actuales.size();
            auto [i, j] = obstaculos_actuales[idx];
            if (labyrinth.GetLabyrinth()[i][j].GetKind() == 1) {
                labyrinth.Node({i, j}).SetKind(0);
                num_muros--;
            }
            obstaculos_actuales.erase(obstaculos_actuales.begin() + idx);
        }

        // Realizamos la búsqueda de nuevo
        table = labyrinth.AStarSearch();

        generados_totales += table.generated.size();
        visitados_totales += table.visited.size();

        // Actualizamos el laberinto auxiliar
        labyrinth_aux = labyrinth;

        if (table.path.size() == 0) {    // Si no se ha encontrado un camino, aumentamos el contador de iteraciones sin camino
            iter_no_path++;
            std::cout << RED << BOLD << "No se ha encontrado un camino al destino en la iteración " << iter << ".\n" << RESET;
            std::cout << "Re-generando obstáculos...\n";
        } else {
            table_final.path.push_back(table.path[1]);  // Añadimos el nodo del primer paso al camino total
            coste_final = table.path[1].GetGValue(); // Actualizamos el coste total
            iter_no_path = 0; // Reiniciamos el contador de iteraciones sin camino
        }
    }


    std::cout << "\nResultado de la búsqueda A* dinámica:\n";
    if (table_final.path.size() == 0) {
        std::cout << RED << BOLD << "No se ha encontrado un camino al destino.\n" << RESET;
    } else {
        std::cout << GREEN << BOLD << "Camino encontrado:\n" << RESET;
        for (const auto& cell : table_final.path) {
            std::cout << cell.GetPosString() << " ";
        }
        std::cout << "\nCoste del camino: " << coste_final << "\n";
    }

    // Extraemos la información
    std::string path = VectorToString(table_final.path);  // Convierte el camino a string
    int generados = generados_totales;   // Número total de nodos generados en todas las búsquedas
    int visitados = visitados_totales;     // Número total de nodos visitados en todas las búsquedas
    int cost = coste_final;                    // Coste total del camino

    // Recorremos el laberinto auxiliar para marcar el camino final
    for (int i = 0; i < labyrinth_aux.GetRows(); i++) {   // Recorremos las filas
        for (int j = 0; j < labyrinth_aux.GetColumns(); j++) {  // Recorremos las columnas
            for (const auto& cell : table_final.path) {
                if (labyrinth_aux.GetLabyrinth()[i][j].GetPos() == cell.GetPos() && labyrinth_aux.GetLabyrinth()[i][j].GetKind() != 3 && labyrinth_aux.GetLabyrinth()[i][j].GetKind() != 4) {
                    labyrinth_aux.Node(labyrinth_aux.GetLabyrinth()[i][j].GetPos()).SetKind(7); // Marcamos el camino final con un 7
                }
            }
        }
    }

    // Marcamos el nodo inicial original en el laberinto auxiliar
    std::pair<int,int> prev_start_pos = labyrinth_aux.GetStartNode().GetPos();      // Guardar la posición anterior
    labyrinth_aux.Node(prev_start_pos).SetKind(7);                                  // Quitar el tipo 3 del nodo anterior
    std::pair<int,int> new_start_pos = inicial.GetPos();                            // Obtener la nueva posición para el nodo inicial
    labyrinth_aux.Node(new_start_pos) = inicial;                                    // Copiar los datos del nuevo nodo inicial
    labyrinth_aux.Node(new_start_pos).SetKind(3);                                   // Establecer el tipo 3 en el nuevo nodo inicial
    labyrinth_aux.SetStartNode(labyrinth_aux.Node(new_start_pos));                  // Actualizar el puntero del nodo inicial en el objeto Labyrinth

    std::string dibujo = labyrinth_aux.PrintLabyrinth(); // Dibujo del laberinto con el camino final

    // Ancho fijo para cada columna
    const int col_widths[] = {10, 5, 5, 7, 20, 22};

    // Cabecera de la tabla
    output_file << "\n";
    output_file << "| " << CenterText("Instancia", col_widths[0])
                << " | " << CenterText("n", col_widths[1])
                << " | " << CenterText("m", col_widths[2])
                << " | " << CenterText("Coste", col_widths[3])
                << " | " << CenterText("Nodos Generados", col_widths[4])
                << " | " << CenterText("Nodos inspeccionados", col_widths[5]) << " |\n";

    output_file << "|-" << std::string(col_widths[0], '-') << "-|-" 
                << std::string(col_widths[1], '-') << "-|-" 
                << std::string(col_widths[2], '-') << "-|-" 
                << std::string(col_widths[3], '-') << "-|-" 
                << std::string(col_widths[4], '-') << "-|-" 
                << std::string(col_widths[5], '-') << "-|\n";

    // Contenido de la tabla
    output_file << "| " << CenterText(id, col_widths[0])
                << " | " << CenterText(std::to_string(labyrinth.GetRows()), col_widths[1])
                << " | " << CenterText(std::to_string(labyrinth.GetColumns()), col_widths[2])
                << " | " << CenterText(std::to_string(cost), col_widths[3])
                << " | " << CenterText(std::to_string(generados), col_widths[4])
                << " | " << CenterText(std::to_string(visitados), col_widths[5]) << " |\n\n";


    // Vuelvo a colocar el nodo inicial original en el laberinto
    prev_start_pos = labyrinth.GetStartNode().GetPos();  // Guardar la posición anterior
    labyrinth.Node(prev_start_pos).SetKind(1);                              // Quitar el tipo 3 del nodo anterior
    new_start_pos = inicial.GetPos();                    // Obtener la nueva posición para el nodo inicial
    labyrinth.Node(new_start_pos) = inicial;                                // Copiar los datos del nuevo nodo inicial
    labyrinth.Node(new_start_pos).SetKind(3);                               // Establecer el tipo 3 en el nuevo nodo inicial
    labyrinth.SetStartNode(labyrinth.Node(new_start_pos));                  // Actualizar el puntero del nodo inicial en el objeto Labyrinth

    output_file << "S: " << labyrinth.GetStartNode().GetPosString() << "\n";
    output_file << "E: " << labyrinth.GetEndNode().GetPosString() << "\n";
    output_file << "Camino: " << path << "\n";

    // Añadimos otros datos adicionales
    output_file << "\n" << dibujo << "\n\n";
    output_file << "Iteraciones: \n\n" << iter << "\n\n";

    // Cerramos el archivo
    output_file.close();
    return output_file;
}

/**
 * @brief Comprueba si un nodo está disponible para transitar
 * 
 * @param row
 * @param col
 * @param labyrinth
 * @return true
 * @return false
 */
bool IsNodeValid(int row, int col, Labyrinth& labyrinth) {
    if (row < 0 || col < 0) return false; // Si el nodo está fuera del laberinto
    if (row >= labyrinth.GetRows() || col >= labyrinth.GetColumns()) return false; 
    if (labyrinth.Node(std::make_pair(row, col)).GetKind() == 1) return false; // Si el nodo es un muro
    return true;
}

/**
 * @brief Construye el camino de la solución a partir de los padres
 * 
 * @param current_node
 * @param start_node
 * @param parents
 * @return CellVector
 */
CellVector ConstructPath(Cell current_node, 
                            Cell start_node,
                            std::vector<std::pair<Cell,Cell>> parents) {
    CellVector path;
    while (current_node.GetKind() != 3) {         // Mientras no se llegue al nodo inicial
        path.push_back(current_node); 
        for (int i = 0; i < parents.size(); i++) {
            if (parents[i].first == current_node) {
                current_node = parents[i].second;      // Se añade el padre del nodo actual al camino
                break;
            }
        }
    }
    path.push_back(start_node);
    std::reverse(path.begin(), path.end());      // Se invierte el camino para mostrarlo de la forma correcta
    return path;
}

/**
 * @brief Actualiza el padre de un nodo si es mejor que el actual
 * 
 * @param node
 * @param current_node
 * @param labyrinth
 * @param parents
 * @param open_nodes
 */
void UpdateIfBetter(Cell& node, Cell& current_node, 
                          std::vector<CellVector> labyrinth,
                          std::vector<std::pair<Cell,Cell>>& parents,
                          CellVector& open_nodes) {
    int g_value = current_node.GetGValue();
    if (current_node.IsDiagonal(node, labyrinth)) {
        g_value += 7; // Si el nodo es diagonal el coste es 7
    } else {
        g_value += 5; // Si el nodo es adyacente el coste es 5
    }
    for (int i = 0; i < parents.size(); i++) {  
        if (parents[i].first == node) {
            if (g_value < parents[i].first.GetGValue()) {                           // Si el padre actual es mejor que el anterior
                parents[i].second = current_node;                                     // Se actualiza el padre
                parents[i].first.SetGValue(g_value);                                  // Se actualiza el coste g
                parents[i].first.SetFValue(g_value + parents[i].first.GetHValue());   // Se actualiza el coste f
                for (int j = 0; j < open_nodes.size(); j++) {                         // Se actualiza el nodo en la lista de nodos abiertos
                    if (open_nodes[j] == parents[i].first) {
                        open_nodes[j] = parents[i].first;
                        break;
                    }
                }
            }
            break;
        }
    }
}

/**
 * @brief Comprueba si un nodo vecino es inválido para transitar
 * 
 * @param neighbor
 * @param current_node
 * @param closed_nodes
 * @return true
 * @return false
 */
bool InvalidNeighbor(Cell& neighbor, 
                        Cell& current_node, 
                        CellVector& closed_nodes) {
    return neighbor.GetPos() == std::make_pair(-1, -1) ||  // Si el nodo no existe en el laberinto
    IsClosedNode(neighbor, closed_nodes);                  // Si el nodo ya está cerrado
}

// Modificación año pasado
std::ofstream StoreSearchMod(Labyrinth& labyrinth, std::string& instance_name) {
    std::ofstream output_file;

    // Crear el directorio "output" si no existe
    if (!std::filesystem::exists("output")) {
        std::filesystem::create_directory("output");
    }
    output_file.open("output/instancias.md", std::ios_base::app);  // Abre el fichero en modo append

    std::string id = instance_name.substr(11);  // Obtiene el identificador de la instancia

    // Cabecera inicial
    output_file << "Resultados para la instancia " << id << ":\n";
    output_file << std::string(50, '-') << "\n\n";

    // Ejecutar el algoritmo modificado 10 veces
    for (int iteracion_global = 1; iteracion_global <= 10; ++iteracion_global) {
        // Realizar la búsqueda usando el algoritmo A* modificado
        Instance table = labyrinth.ModAStarSearch();

        // Extraer información de la instancia
        std::string path = VectorToString(table.path);  // Convierte el camino a string
        int generados = table.generated.size();
        int visitados = table.visited.size();
        int cost = 0;
        std::string dibujo = table.dibujo;

        // Si hay camino, obtenemos el coste
        if (path != "No path") cost = table.path.back().GetGValue();

        // Ancho fijo para cada columna
        const int col_widths[] = {10, 5, 5, 7, 20, 22};

        // Cabecera de la tabla
        if (iteracion_global == 1) {
            output_file << "| " << CenterText("Iteración", col_widths[0])
                        << " | " << CenterText("n", col_widths[1])
                        << " | " << CenterText("m", col_widths[2])
                        << " | " << CenterText("Coste", col_widths[3])
                        << " | " << CenterText("Nodos Generados", col_widths[4])
                        << " | " << CenterText("Nodos inspeccionados", col_widths[5]) << " |\n";

            output_file << "|-" << std::string(col_widths[0], '-') << "-|-" 
                        << std::string(col_widths[1], '-') << "-|-" 
                        << std::string(col_widths[2], '-') << "-|-" 
                        << std::string(col_widths[3], '-') << "-|-" 
                        << std::string(col_widths[4], '-') << "-|-" 
                        << std::string(col_widths[5], '-') << "-|\n";
        }

        // Contenido de la tabla por iteración
        output_file << "| " << CenterText(std::to_string(iteracion_global), col_widths[0])
                    << " | " << CenterText(std::to_string(labyrinth.GetRows()), col_widths[1])
                    << " | " << CenterText(std::to_string(labyrinth.GetColumns()), col_widths[2])
                    << " | " << CenterText(std::to_string(cost), col_widths[3])
                    << " | " << CenterText(std::to_string(generados), col_widths[4])
                    << " | " << CenterText(std::to_string(visitados), col_widths[5]) << " |\n";

        // Detalles adicionales para cada iteración
        output_file << "Camino: " << path << "\n";
        output_file << "S: " << labyrinth.GetStartNode().GetPosString() << "\n";
        output_file << "E: " << labyrinth.GetEndNode().GetPosString() << "\n";

        // Nodos inspeccionados
        output_file << "Nodos inspeccionados: ";
        for (const auto& cell : table.visited) {
            output_file << "(" << cell.GetIPos() << "," << cell.GetJPos() << ") ";
        }
        output_file << "\n";

        // Dibujo del laberinto
        output_file << "\n" << dibujo << "\n\n";

        // Iteraciones de la ejecución
        output_file << "Iteraciones: \n\n" << table.iteraciones << "\n\n";

        // Separador entre iteraciones
        output_file << std::string(50, '-') << "\n\n";
    }

    // Cerrar el archivo
    output_file.close();
    return output_file;
}