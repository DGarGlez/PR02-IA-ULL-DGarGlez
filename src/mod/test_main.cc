#include "include/cell.h"
#include "include/labyrinth.h"
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
	// Crear dos celdas
	Cell cell1(2, 3, 1);
	Cell cell2(4, 5, 2);

	// Mostrar posiciones
	std::cout << "Posición cell1: " << cell1.GetPosString() << std::endl;
	std::cout << "Posición cell2: " << cell2.GetPosString() << std::endl;

	// Mostrar tipo
	std::cout << "Tipo cell1: " << cell1.GetKind() << std::endl;
	std::cout << "Tipo cell2: " << cell2.GetKind() << std::endl;

	// Modificar tipo y mostrar
	cell1.SetKind(3);
	std::cout << "Nuevo tipo cell1: " << cell1.GetKind() << std::endl;

	// Calcular heurística Manhattan y Euclídea
	cell1.CalculateHeuristic(cell2, 1); // Manhattan
	std::cout << "Heurística Manhattan cell1 respecto a cell2: " << cell1.GetHValue() << std::endl;
	cell1.CalculateHeuristic(cell2, 2); // Euclídea
	std::cout << "Heurística Euclídea cell1 respecto a cell2: " << cell1.GetHValue() << std::endl;

	// Setear y mostrar valores g y f
	cell1.SetGValue(10);
	cell1.SetFValue(cell1.GetGValue() + cell1.GetHValue());
	std::cout << "Valores cell1: " << cell1.PrintValues() << std::endl;

	// Comparar igualdad y menor que
	std::cout << "¿cell1 == cell2?: " << (cell1 == cell2 ? "Sí" : "No") << std::endl;
	std::cout << "¿cell1 < cell2?: " << (cell1 < cell2 ? "Sí" : "No") << std::endl;

	// Probar IsDiagonal
	std::vector<std::vector<Cell>> labCell(5, std::vector<Cell>(5));
	Cell diag1(1, 1, 0);
	Cell diag2(2, 2, 0);
	std::cout << "¿diag1 y diag2 son diagonales?: " << (diag1.IsDiagonal(diag2, labCell) ? "Sí" : "No") << std::endl;
	std::cout << "¿cell1 y cell2 son diagonales?: " << (cell1.IsDiagonal(cell2, labCell) ? "Sí" : "No") << std::endl;

	// Probar funciones inline de búsqueda en vectores
	CellVector open{cell1, cell2};
	std::cout << "¿cell1 está en open?: " << (IsOpenNode(cell1, open) ? "Sí" : "No") << std::endl;
	std::cout << "¿diag1 está en open?: " << (IsOpenNode(diag1, open) ? "Sí" : "No") << std::endl;


    // Abrir archivo de instancia de laberinto
    std::ifstream input_file(argv[1]);
    if (!input_file.is_open()) {
        std::cerr << "No se pudo abrir el archivo de laberinto.\n";
        return 1;
    }

    // Crear laberinto
    Labyrinth lab(input_file);
    std::cout << "Laberinto cargado:\n";
    std::cout << lab.PrintLabyrinth() << std::endl;

    // Mostrar nodo inicial y final
    std::cout << "Nodo inicial: " << lab.GetStartNode().GetPosString() << std::endl;
    std::cout << "Nodo final: " << lab.GetEndNode().GetPosString() << std::endl;

    // Cambiar heurística y mostrar
    lab.ChangeHeuristic();
    std::cout << "Heurística elegida: " << lab.GetChosenHeuristic() << std::endl;

    // Ejecutar búsqueda A*
    Instance resultado = lab.AStarSearch();
    std::cout << "\nIteraciones:\n" << resultado.iteraciones << std::endl;
    std::cout << "\nCamino encontrado:\n";
    for (const auto& cell : resultado.path) {
        std::cout << cell.GetPosString() << " ";
    }
    std::cout << std::endl;
    std::cout << "\nDibujo del laberinto resuelto:\n" << resultado.dibujo << std::endl;


	return 0;
}
