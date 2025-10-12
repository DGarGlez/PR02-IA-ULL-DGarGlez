#include "include/cell.h"
#include <iostream>
#include <vector>

int main() {
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
	std::vector<std::vector<Cell>> lab(5, std::vector<Cell>(5));
	Cell diag1(1, 1, 0);
	Cell diag2(2, 2, 0);
	std::cout << "¿diag1 y diag2 son diagonales?: " << (diag1.IsDiagonal(diag2, lab) ? "Sí" : "No") << std::endl;
	std::cout << "¿cell1 y cell2 son diagonales?: " << (cell1.IsDiagonal(cell2, lab) ? "Sí" : "No") << std::endl;

	// Probar funciones inline de búsqueda en vectores
	CellVector open{cell1, cell2};
	std::cout << "¿cell1 está en open?: " << (IsOpenNode(cell1, open) ? "Sí" : "No") << std::endl;
	std::cout << "¿diag1 está en open?: " << (IsOpenNode(diag1, open) ? "Sí" : "No") << std::endl;

	return 0;
}
