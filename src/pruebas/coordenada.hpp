/**
 * @file coordenada.hpp
 * @version 1.0
 * @author 
 * @title Coordenada
 * @brief Clase Coordenada
 */
 
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <errno.h>
#include <ctime>
#include <set>
#include <math.h>
#include <assert.h>
#include <vector>

using namespace std;

class coordenada{
  
  private:
  
     int fila_;
     int columna_;
     
  public:
     
     /**
     * @brief coordenada Constructor por defecto
     */
     coordenada(void);
     
     /**
     * @brief coordenada Constructor introduciendo parametros
     * @param x Equivale a la fila. 
     * @param y Equivale a la columna.
     */
     coordenada(const int& x, const int& y); // Constructor por parámetros
     
     /**
     * @brief ~coordenada Destructor por defecto
     */
     ~coordenada(void);
     
     /**
     * @brief get_fila Devuelve la fila de la coordenada
     * @return Posición
     */
     int get_fila(void);
     
     /**
     * @brief get_fila Devuelve la columna de la coordenada
     * @return Posición
     */
     int get_columna(void);
     
     /**
     * @brief set_fila Introduce una nueva fila para la coordenada
     * @param val Posición a introducir
     */
     void set_fila(int val);
     
     /**
     * @brief set_columna Introduce una nueva columna para la coordenada
     * @param val Posición a introducir
     */
     void set_columna(int val);
     
     /**
     * @brief != Comprueba si dos coordenadas son distintas
     * @param x Coordenada a comparar
     * @return Retorna un booleano (verdadero o falso) para responder a la comparación
     */
     bool operator!=(coordenada x);
     
     /**
     * @brief == Comprueba si dos coordenadas son iguales
     * @param x Coordenada a comparar
     * @return Retorna un booleano (verdadero o falso) para responder a la comparación
     */
     bool operator==(coordenada x);
     

};