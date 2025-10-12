/**
 * @file tablero.hpp
 * @version 1.0
 * @author 
 * @title Tablero
 * @brief Clase Tablero
 */
 
#include <random>

#include "celda.hpp"
#include "trayectoria.hpp"

class tablero{
	
	private:
	
	   celda**   malla_; 
	   int N_, M_;
	   int heuristica_;
	   int movimientos_;
	   coordenada meta_;
	   coordenada salida_;
	
	public:
	
	   //---------------------------CONSTRUCTORES Y DESTRUCTOR---------------------------------------
	   
	   /**
    	* @brief tablero Constructor por defecto
    	*/
	   tablero(void);
	   
	   /**
    	* @brief tablero Constructor introduciendo parametros
    	* @param n Número de filas del tablero
    	* @param m Número de columnas del tablero
    	* @param coche_y Coordenada del coche en el tablero
    	* @param coche_x Coordenada del coche en el tablero
    	* @param meta_y Coordenada de la meta en el tablero
    	* @param meta_x Coordenada de la meta en el tablero
    	* @param FH indica la función heurística que se va a emplear.
    	*/
	   tablero(const int& n, const int& m, int coche_y, int coche_x, int meta_y, int meta_x, int FH);
	   
	   /**
    	* @brief ~tablero Destructor por defecto
    	*/
	   ~tablero(void);
	   
	   
	   //------------METODOS PARA INTERACCIONAR CON LOS ATRIBUTOS DE LA CLASE -----------------------
	   
	   /**
    	* @brief set_obst Crea obstaculos
    	* @param x Posición en el eje X del obstaculo dentro del tablero
    	* @param y Posición en el eje Y del obstaculo dentro del tablero
    	* @param random Indica si la generación del obstaculo es de forma aleatoria o especificada por el usuario
    	* @param num_obst Indica el número de obstaculos que se desean en el tablero
    	*/
	   void set_obst(const int& x, const int& y, const bool& ramdom, const int& num_obst);
	   
	   /**
    	* @brief get_cell Retorna un objeto dentro del tablero
    	* @return Objeto
    	* @param fil fila del objeto dentro del tablero
    	* @param col columna del objeto dentro del tablero
    	*/
	   celda& get_cell(int fil, int col);
	   
	   /**
    	* @brief get_meta Retorna las coordenadas de la meta dentro de la tabla
    	* @return Objeto que contiene las coordenadas
    	*/
	   coordenada get_meta(void);
	   
	   /**
    	* @brief get_salida Retorna las coordenadas de la posición de salida del vehiculo dentro de la tabla
    	* @return Objeto que contiene las coordenadas
    	*/
	   coordenada get_salida(void);
	   
	   /**
    	* @brief get_movimientos retorna el número de movimientos realizados por el algoritmo según la función heurística seleccionada.
    	* @return Valor entero que indica el número de movimientos.
    	*/
	   int get_movimientos(void);
	   
	   
	   //----------------------MÉTODO SELECCIÓN DE FUNCIÓN HEURÍSTICAS----------------------------------
		
	   /**
    	* @brief calcular_distancia Contiene las funciones heurísticas (La que se aplique dependerá del valor de "heuristica_")
    	* @return Distancia entre la coordenada especificada y la coordenada final.
    	* @param val_fila  fila de la celda a examinar.
    	* @param val_columna  fila de la columna a examinar
    	*/	
	   int calcular_distancia(int val_fila, int val_columna);
	   
	   
	   //--------------------------MÉTODOS ALGORITMO A*.------------------------------------------------
       
       /**
    	* @brief alg_A_estrella Contiene la estructura básica para la ejecución del algoritmo A*
    	* @return Devuelve un vector<coordenada> que representa la solución del algoritmo.
    	*/	
       vector<coordenada> alg_A_estrella(void);
       
       /**
    	* @brief menor_trayectoria Se encarga de localizar la trayectoria de menor coste del vector<trayectoria> abierta y la coloca en la primera posisión.
    	* @return Devuelve la trayectoria de menor coste del vector<trayectoria> abierta.
    	* @param x ==> Equivale a vector<trayectoria> abierta.
    	*/	
       trayectoria menor_trayectoria(vector<trayectoria>& x);
       
       /**
    	* @brief ramificar_nodo se encarga de crear las nuevas trayectorias a partir de la trayectoria "menor" que se ha seleccionado en el metodo menor_trayectoria y las inserta en el vector<trayectoria> abierta.
    	* @param menor ==> Equivale a la menor trayectoria de abierta.
    	* @param x ==> Equivale al vector<trayectoria> abierta.
    	* @param y ==> Equivale al vector<trayectoria> cerrada.
    	*/	
       void ramificar_nodo(trayectoria menor, vector<trayectoria>& x, vector<trayectoria>& y);
       
       /**
    	* @brief crear_trayectoria Se encarga de crear una trayectoria que tendrá como base el contenido de la trayectoria "menor" a la que le añade la coordenada [fil,col] y que tendrá como coste el valor de "acumulado".
    	* @return Devuelve la trayectoria creada.
    	* @param menor ==> trayectoria que se coge como base
    	* @param acumulado ==> Coste que tendrá la nueva trayectoria.
    	* @param fil ==> fila de la coordenada que se debe añadir a "menor" para crear la nueva trayectoria.
    	* @param col ==> columna de la coordenada que se debe añadir a "menor" para crear la nueva trayectoria.
    	*/	
       trayectoria crear_trayectoria(trayectoria menor, int acumulado, int fil, int col);
       
       /**
    	* @brief eliminacion ==> En este metodo se eliminan aquellas trayectorias del vector<trayectoria> abierta que lleven a un mismo punto final con mayor coste, de tal forma que se mantiene la de menor. También se compara con "cerrada" con el mismo fin.
    	* @param nueva ==> Nueva trayectoria que puede ser añadida a abierta.
    	* @param x ==> Equivale a vector<trayectoria> abierta.
    	* @param y ==> Equivale a vector<trayectoria> cerrada.
    	*/	
       void eliminacion(trayectoria nueva, vector<trayectoria>& x, vector<trayectoria>& y);


};