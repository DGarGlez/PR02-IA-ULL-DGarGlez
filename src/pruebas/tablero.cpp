#include "tablero.hpp"

//---------------------------CONSTRUCTORES Y DESTRUCTOR---------------------------------------

tablero::tablero(void): 
    malla_(),
    N_(),
    M_(),
    heuristica_(),
    movimientos_(),
    meta_(),
    salida_()
{}
    
tablero::tablero(const int& n, const int& m, int coche_y, int coche_x, int meta_y, int meta_x, int FH):
    malla_(),
    N_(n),
    M_(m),
    heuristica_(FH),
    movimientos_(0),
    meta_(),
    salida_()
{
    meta_.set_fila(meta_y);
    meta_.set_columna(meta_x);
    
    salida_.set_fila(coche_y);
    salida_.set_columna(coche_x);
    
	malla_ = new celda*[n];
    
    for (int i=0; i < N_; ++i)
        malla_[i] = new celda[m];

}

tablero::~tablero(void) {
    
    // No es necesario apuntar a null primero en este caso ya que nos interesa eliminar los elementos a los que apunta el puntero y el puntero.
	 for (int i=0; i < N_; ++i)
        delete [] malla_[i];
            
    delete [] malla_; 
    //delete ptr_vehicle;
    
    
}


//------------METODOS PARA INTERACCIONAR CON LOS ATRIBUTOS DE LA CLASE--------------------------

void tablero::set_obst(const int& x, const int& y, const bool& ramdom, const int& num_obst) {
    
   if (ramdom)
    {
            std::random_device rd; // obtain a random number from hardware
            std::mt19937 eng(rd()); // seed the generator
            std::uniform_int_distribution<int> n_range(0, N_-1); // define the range
            std::uniform_int_distribution<int> m_range(0, M_-1); // define the range
            
            for (int i=0; i < num_obst; ++i) {
               int f=n_range(eng);
               int c=m_range(eng);
               if((f!=meta_.get_fila()||c!=meta_.get_columna())&&(f!=salida_.get_fila()||c!=salida_.get_columna())&&malla_[f][c].get_obst()==false)
                    malla_[f][c].set_obst(true);
               else
                  i--;
            }
    }else
            malla_[x][y].set_obst(true);
}
celda& tablero::get_cell(int fil, int col) { 
    
    return malla_[fil][col];
    
}
coordenada tablero::get_meta(void) { 
    
    return meta_; 
    
}
coordenada tablero::get_salida(void) { 
    
    return salida_; 
}
int tablero::get_movimientos(void) {
    
    return movimientos_;
}

//----------------------MÉTODO SELECCIÓN DE FUNCIÓN HEURÍSTICAS----------------------------------

int tablero::calcular_distancia(int val_fila, int val_columna) {
    
    int distancia=0;
    
    switch(heuristica_) {
        
        case 1:
           distancia=(abs(val_fila-meta_.get_fila())+abs(val_columna-meta_.get_columna()));
        break;
        
        case 2:
           if(abs(val_fila-meta_.get_fila())>abs(val_columna-meta_.get_columna()))
              distancia=abs(val_fila-meta_.get_fila());
           else
              distancia=abs(val_columna-meta_.get_columna());
        break;
        
        case 3:
           distancia=sqrt(pow((val_fila-meta_.get_fila()),2)+pow((val_columna-meta_.get_columna()),2));
        break;
    }
    
    return distancia;
}



//--------------------------MÉTODOS ALGORITMO A*.------------------------------------------------

vector<coordenada> tablero::alg_A_estrella(void) {
    
    vector<trayectoria> abierta, cerrada;
    trayectoria camino;
    
    camino.insert_coordenada(salida_);
    abierta.push_back(camino);
    
    trayectoria menor=camino;
 
    
    while(menor.get_coordenada_final()!=meta_ && abierta.empty()==false) {
  
          vector<trayectoria>::iterator i=abierta.end()-1;
          
          for(vector<trayectoria>::iterator j = cerrada.begin(); j != cerrada.end(); j++)
             if((*j).get_coordenada_final()==(*i).get_coordenada_final())
                if((*j).get_coste()>(*i).get_coste()) {
                   cerrada.erase(j);
                   j--;
                }
          
          
          cerrada.push_back(*i);
          abierta.erase(i);
          
          ramificar_nodo(menor,abierta,cerrada);
          menor=menor_trayectoria(abierta);
          movimientos_++;

    }
    
    return menor.get_trayecto();
    
}
void tablero::eliminacion(trayectoria nueva, vector<trayectoria>& x, vector<trayectoria>& y) {

    bool insertar=true;
                
    for(vector<trayectoria>::iterator j=y.begin();j!=y.end();j++)
       if(nueva.get_coordenada_final()==(*j).get_coordenada_final()&&nueva.get_coste()>(*j).get_coste())
          insertar=false;
                
    for(vector<trayectoria>::iterator i=x.begin();i!=x.end()&&insertar==true;i++)
       if(nueva.get_coordenada_final()==(*i).get_coordenada_final())
          if(nueva.get_coste()<(*i).get_coste()) {
             x.erase(i);
             insertar=false;
             x.push_back(nueva);
             break;
          }
          else{
             insertar=false;
             break;
		  }
                
    if(insertar==true)
       x.push_back(nueva);
    
}
void tablero::ramificar_nodo(trayectoria menor, vector<trayectoria>& x, vector<trayectoria>& y) {
    
    int pos_fil=menor.get_coordenada_final().get_fila();
    int pos_col=menor.get_coordenada_final().get_columna();
    int acumulado=0;

    if (pos_fil-1>= 0)
       if (!malla_[pos_fil-1][pos_col].get_obst())
          if(menor.sz_vector()==1) {
             acumulado=menor.sz_vector()+calcular_distancia(pos_fil-1,pos_col);
             x.push_back(crear_trayectoria(menor,acumulado,pos_fil-1,pos_col));
                         
          }
          else 
             if(!menor.check_coordenada_padre(pos_fil-1,pos_col)) {
                acumulado=menor.sz_vector()+calcular_distancia(pos_fil-1,pos_col);
                trayectoria nueva=crear_trayectoria(menor,acumulado,pos_fil-1,pos_col);
               
                eliminacion(nueva,x,y);    
             }
    
    acumulado=0;
    
    if (pos_col-1>= 0)
      if (!malla_[pos_fil][pos_col-1].get_obst())
         if(menor.sz_vector()==1) {
            acumulado=menor.sz_vector()+calcular_distancia(pos_fil,pos_col-1);
            x.push_back(crear_trayectoria(menor,acumulado,pos_fil,pos_col-1));
         }
         else
            if(!menor.check_coordenada_padre(pos_fil,pos_col-1)) {
               acumulado=menor.sz_vector()+calcular_distancia(pos_fil,pos_col-1);
               trayectoria nueva=crear_trayectoria(menor,acumulado,pos_fil,pos_col-1);
                
               eliminacion(nueva,x,y);
            }
            
    acumulado=0;
    
    if (pos_col+1<=M_-1)
      if (!malla_[pos_fil][pos_col+1].get_obst())
         if(menor.sz_vector()==1) {
            acumulado=menor.sz_vector()+calcular_distancia(pos_fil,pos_col+1);
            x.push_back(crear_trayectoria(menor,acumulado,pos_fil,pos_col+1));
         }
         else
            if(!menor.check_coordenada_padre(pos_fil,pos_col+1)) {
               acumulado=menor.sz_vector()+calcular_distancia(pos_fil,pos_col+1);
               trayectoria nueva=crear_trayectoria(menor,acumulado,pos_fil,pos_col+1);

               eliminacion(nueva,x,y);
            }

    acumulado=0;
    
    if (pos_fil+1<=N_-1)
      if (!malla_[pos_fil+1][pos_col].get_obst())
         if(menor.sz_vector()==1) {
            acumulado=menor.sz_vector()+calcular_distancia(pos_fil+1,pos_col);
            x.push_back(crear_trayectoria(menor,acumulado,pos_fil+1,pos_col));
         }
         else
            if(!menor.check_coordenada_padre(pos_fil+1,pos_col)) {
               acumulado=menor.sz_vector()+calcular_distancia(pos_fil+1,pos_col);
               trayectoria nueva=crear_trayectoria(menor,acumulado,pos_fil+1,pos_col);

               eliminacion(nueva,x,y);
            }
            
}
trayectoria tablero::crear_trayectoria(trayectoria menor, int acumulado, int fil, int col) {
    
    trayectoria aux=menor;
    coordenada  aux2(fil,col);
    aux.insert_coordenada(aux2);
    aux.set_coste(acumulado);
    
    return aux;
}
trayectoria tablero::menor_trayectoria(vector<trayectoria>& x) {
    
    trayectoria aux;
    
    if(x.empty()==false) {
    
       vector<trayectoria>::iterator k=x.begin();
    
       for(vector<trayectoria>::iterator i=k+1;i!=x.end();i++)
          if((*k).get_coste()>(*i).get_coste())
             k=i;
          
       aux=(*k);
       x.erase(k);
       x.push_back(aux);
    }
    
    return aux;
       
}

