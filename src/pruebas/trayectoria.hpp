/**
 * @file trayectoria.hpp
 * @version 1.0
 * @author 
 * @title Trayectoria
 * @brief Clase Trayectoria
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

#include "coordenada.hpp"

using namespace std;

class trayectoria{
    
   private:
   
      vector<coordenada>   trayecto_;
      int                  coste_;
   
   public:
      
      /**
    	* @brief trayectoria Constructor por defecto
    	*/
      trayectoria(void);
      
      /**
    	* @brief ~trayectoria Destructor por defecto
    	*/
      ~trayectoria(void);
      
      /**
    	* @brief insert_coordenada Inserta una coordenada
    	* @param x Coordenada a insertar
    	*/
      void insert_coordenada(coordenada x);
      
      /**
    	* @brief get_coordenada_final Devuelve la coordenada final
    	* @return Coordenada
    	*/
      coordenada get_coordenada_final(void);
      
      /**
    	* @brief check_coordenada_padre Comprueba si una coordenada especificada es la padre
    	* @param fil ==> fila de la coordenada
    	* @param col ==> Columna de la coordenada
    	* @return Devuelve una respuesta booleana (Verdadero o Falso) de la comprobación
    	*/
      bool check_coordenada_padre(int fil, int col);
      
      /**
    	* @brief get_trayecto Devuelve el vector de coordenadas
    	* @return Devuelve un objeto vector<coordenada>
    	*/
      vector<coordenada> get_trayecto(void);
      
      /**
    	* @brief sz_vector Devuelve el tamaño de trayecto_.
    	* @return Devuelve un valor entero (int) que representa el tamaño del vector de coordenadas "trayecto_"
    	*/
      int sz_vector(void);
      
      /**
    	* @brief set_coste Introduce un coste al trayecto
    	* @param val Valor del coste a introducir
    	*/
      void set_coste(int val);
      
      /**
    	* @brief get_coste Devuelve el valor del coste del trayecto
    	* @return Valor del coste
    	*/
      int get_coste(void);
      
      /**
    	* @brief print_trayecto Visualiza el trayecto
    	*/
      void print_trayecto(void);
      
    
};