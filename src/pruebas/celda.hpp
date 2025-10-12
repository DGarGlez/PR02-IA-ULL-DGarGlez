/**
 * @file celda.hpp
 * @version 1.0
 * @author 
 * @title Celda
 * @brief Clase Celda
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

using namespace std;

class celda{
	
	private:
	
	   bool visitada_;
	   bool obstaculo_;
	
	public:
		
	   /**
    	* @brief celda Constructor por defecto
    	*/	
	   celda(void);
	   
	   /**
    	* @brief ~celda Destructor por defecto
    	*/	
	   ~celda(void);
	   
	   /**
    	* @brief set_visitada Establece que la celda ha sido visitada o no
    	* @param estado Booleano para indicar si ha sido visitada o no
    	*/
	   void set_visitada(bool estado);
	   
	   /**
    	* @brief get_visitada Devuelve el estado actual de la celda
    	* @return Devuelve un booleano (verdadero o falso) en relación a si ha sido visitada o no
    	*/
	   bool get_visitada(void);
	   
	   /**
    	* @brief set_obst Establece la celda como obstaculo
    	* @param estado Booleano para indicar que la celda sea un obstaculo
    	*/
	   bool set_obst(bool estado);
	   
	   /**
    	* @brief get_obst Devuelve el estado actual de la celda
    	* @return Devuelve un booleano (verdadero o falso) en relación a si es un obstaculo o no
    	*/
	   bool get_obst(void);
	   
};
