#include <cstdio>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <regex>
#include <ctime>

#include "tablero.hpp"

using namespace std;

void visualizar(tablero& tabla, int N, int M, coordenada ini, coordenada fin) {
    
    for(int k=0;k<(6+M*3);k++) // Cabecera fina 
       if(k%2==0)
          cout<<"\E[33m█\E[39m";
       else
          cout<<"\E[32m█\E[39m";

    cout<<endl<<"\E[32m██\E[39m\E[43m \E[49m"; // Primer cuadro 0,0
    
    for(int k=0;k<M;k++)    // Fila con guiones debajo cabecera
       cout<<"\E[43m - \E[49m";
    
    cout<<"\E[43m \E[49m\E[32m██\E[39m"<<endl; // Cuadro verde del final de la línea
    
    for(int i=0;i<N;i++) {
        
        if(i%2==0)
           cout<<"\E[33m██\E[39m\E[43m|\E[49m"; // \E33m (activamos caracter de color para siguiente caracter) ██ (usamos caracter)
        else                                    // \E[39m (desactivamos color) \E[43m (activamos sombreado para siguiente caracter) | \E[49m (desactivamos sombreado)
           cout<<"\E[32m██\E[39m\E[43m|\E[49m";
           
        for(int j=0;j<M;j++)
           if(i==ini.get_fila()&&j==ini.get_columna())
              cout<<" \E[36mI\E[39m ";
           else
              if(i==fin.get_fila()&&j==fin.get_columna())
                 cout<<" \E[35mF\E[39m ";
              else
                 if(tabla.get_cell(i,j).get_obst()==true)
                    cout<<" \E[31m■\E[39m ";
                 else
                    if(tabla.get_cell(i,j).get_visitada()==true)
                       cout<<"\E[45m   \E[49m";
                    else
                       cout<<"\E[43m   \E[49m";
              
        if(i%2==0)
           cout<<"\E[43m|\E[49m\E[33m██\E[39m"<<endl;
        else
           cout<<"\E[43m|\E[49m\E[32m██\E[39m"<<endl;
    }
    
    if(N%2==0) // Último cuadrado
       cout<<"\E[33m██\E[39m\E[43m \E[49m";
    else
       cout<<"\E[32m██\E[39m\E[43m \E[49m";
  
    for(int k=0;k<M;k++) // Guión
          cout<<"\E[43m - \E[49m";
    
    if(N%2==0) // Cuadrado final
       cout<<"\E[43m \E[49m\E[33m██\E[39m"<<endl;
    else
       cout<<"\E[43m \E[49m\E[32m██\E[39m"<<endl;
    
    
    for(int k=0;k<(6+M*3);k++) // Segunda cabecera
       if(k%2==0)
          cout<<"\E[33m█\E[39m";
       else
          cout<<"\E[32m█\E[39m";
}

bool test_int(int& value) // Cada vez que haces una entrada. 
{
    cin >> value;
    bool test = cin.good();
    if(!test) 
    {
        system("clear");
	    cin.clear();
	    cin.ignore(); // Eliminamos el contenido
	    cout <<endl<<"\E[31mLa respuesta no ha sido un número\E[39m"<<endl;
        usleep(1e6);
        system("clear");
    }
    /*else
        value = atoi(dummy.c_str());*/
    return test;
}

int main(void) {
    
    int filas, columnas, n_obstaculos, vehiculo_if, vehiculo_ic, vehiculo_of, vehiculo_oc, heuristica;
    bool check=0;
    string reply="";
    string coordenadas_obs="";
    
    system("clear");
    cout<<endl<<"\E[1;43mDIMENSIONES DEL TABLERO.\E[49m"<<endl;
    
    while(true)
    {
        cout<<endl<<"\E[31mIntroduzca el número de filas de la tabla: \E[39m";
        if(test_int(filas))
            break;
    }
    
    while(true)
    {
	    cout<<"\E[31mIntroduzca el número de columnas de la tabla: \E[39m";
	    if(test_int(columnas))
            break;
    }
	
	system("clear");
	cout<<endl<<"\E[43mPOSICIÓN INICIAL DEL VEHÍCULO.\E[49m"<<endl;
	
	while(true)
	{
	    cout<<endl<<"\E[31mIntroduzca la fila: \E[39m";
        if(test_int(vehiculo_if))
            break;
	}
	while(true)
	
	{
        cout<<"\E[31mIntroduzca la columna: \E[39m";
        if(test_int(vehiculo_ic))
            break;
	}
    
    system("clear");
    cout<<endl<<"\E[43mPOSICIÓN OBJETIVO DEL VEHÍCULO.\E[49m"<<endl;
    
    while(true)
    {
        cout<<endl<<"\E[31mIntroduzca la fila: \E[39m";
        if(test_int(vehiculo_of))
            break;
    }
    
    while(true)
    {
        cout<<"\E[31mIntroduzca la columna: \E[39m";
        if(test_int(vehiculo_oc))
            break;
    }
    
    system("clear");
    cout<<endl<<"\E[43mFUNCIÓN HEURÍSTICA.\E[49m"<<endl;
    
     while(true)
    {
        cout<<endl<<"1.-Distancia de Manhattan.";
        cout<<endl<<"2.-Distancia de Mahalanobis.";
        cout<<endl<<"3.-Distancia Euclídea."<<endl;
        cout<<endl<<"\E[31mIndique con un valor numérico la función heurística que desea emplear [1|2|3]: \E[39m";
        if(test_int(heuristica))
            break;
    }
    
	tablero T(filas, columnas,vehiculo_if,vehiculo_ic,vehiculo_of,vehiculo_oc,heuristica);
	
	system("clear");
	
	do
	{
        if(check) {
            cout <<endl<<endl<<"\E[31mLa respuesta ha sido distinta a 'no' y a 'si'\E[39m"<<endl;
            usleep(1e6);
        }
            
        system("clear");
        cout<<endl<<"\E[43mDETERMINACIÓN DE OBSTÁCULOS.\E[49m"<<endl;
        cout <<endl<< "\E[31m¿Desea introducir manualmente la posición de los obstaculos?: \E[39m";
        cin >> reply;
        
        system("clear");
        check=1;
        
    }while(reply!="si" && reply!="no");
    
    check=0;
    
    if(reply=="si")
    {    
        cout<<endl<<"\E[43mDETERMINACIÓN DE OBSTÁCULOS.\E[49m"<<endl;
        cout<<endl<<"\E[31mSiga la siguiente NOMENCLATURA para introducir las coordenadas de cada obstaculo: "<<endl;
        cout<<"n_1-m_1,n_2-m_2 ... >> \E[39m";
        cin>>coordenadas_obs;
    
        int n_1=-1,n_2=-1;
        int sz=coordenadas_obs.size();
        
        for(int i=0;i<sz; i++) {
    
            if(coordenadas_obs[i]!='-' && coordenadas_obs[i]!=',') {
                
                if(n_1==-1) {
                    
                    string numero="";
                    numero+=coordenadas_obs[i];
                    if(i<sz-1)
                        while(coordenadas_obs[i+1]!='-' && coordenadas_obs[i+1]!=',') {
                           numero+=coordenadas_obs[i+1];
                           i++;
                        }
    
                    n_1=atoi(numero.c_str());
                }
                else 
                   if(n_2==-1) {
                       
                       string num="";
                       num+=coordenadas_obs[i];
                       if(i<sz-1)
                          while(coordenadas_obs[i+1]!='-' && coordenadas_obs[i+1]!=',') {
                             num+=coordenadas_obs[i+1];
                             i++;
                             
                             if(i==sz-1) 
                                break;
                          }
                       
                       n_2=atoi(num.c_str());
                   }
            }
            
            if(n_1!=-1 && n_2!=-1)
            {
                T.set_obst(n_1, n_2, false, 0);
                n_1=-1;    n_2=-1;
            }
        }
       
    }
    else {
        
        system("clear");
        cout<<endl<<"\E[43mDETERMINACIÓN DE OBSTÁCULOS.\E[49m"<<endl;
        while(true)
        {
            cout<<endl<<"\E[31mIntroduza el número de obstaculos que desee: \E[39m";
            if(test_int(n_obstaculos))
                break;
        }
	    
	    T.set_obst(0, 0, true, n_obstaculos);
        
    }
    
    vector<coordenada> solucion;
    
    unsigned time_0,time_1;
    
    time_0=clock();
    solucion=T.alg_A_estrella();
    time_1=clock();
    
    double execution_time=(double(time_1-time_0)/CLOCKS_PER_SEC);
    
    if(solucion.empty()==false) {
       for(vector<coordenada>::iterator i=solucion.begin();i!=solucion.end();i++)
          T.get_cell((*i).get_fila(),(*i).get_columna()).set_visitada(true);  
    
          system("clear");
          cout<<endl;
	      visualizar(T, filas, columnas, T.get_salida(), T.get_meta());
	      cout<<endl<<endl<<"\E[4;32m\E[32m>>>> Tiempo de ejecución del algoritmo: "<<execution_time<<" segundos.\E[39m\E[4;39m"<<endl;
	      cout<<endl<<"\E[4;32m\E[32m>>>> Número de movimientos del algoritmo: "<<T.get_movimientos()<<"\E[39m\E[4;39m";
	      cout<<endl<<endl;
    }  
    else {
       system("clear");
       cout<<endl;
       visualizar(T, filas, columnas, T.get_salida(), T.get_meta());
       cout<<endl<<endl<<"\E[41mNO EXISTE SOLUCIÓN PARA EL CASO EXPUESTO.\E[49m\E[32m ==> ";
       cout<<"\E[4;32mTiempo de ejecución del algoritmo: "<<execution_time<<" segundos.\E[39m\E[4;39m"<<endl;
       cout<<endl<<"\E[4;32m\E[32m>>>> Número de movimientos del algoritmo: "<<T.get_movimientos()<<"\E[39m\E[4;39m";
       cout<<endl<<endl;
    }
    
	return 0;
}