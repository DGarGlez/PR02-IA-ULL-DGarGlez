#include "trayectoria.hpp"

trayectoria::trayectoria(void):
    trayecto_(),
    coste_(0)
{
    
}

trayectoria::~trayectoria(void) {
    
}


void trayectoria::insert_coordenada(coordenada x) {
    
    trayecto_.push_back(x);
}
coordenada trayectoria::get_coordenada_final(void) {
    
    vector<coordenada>::iterator x=trayecto_.end()-1;
    coordenada aux=(*x);
    
    return aux;
    
}
bool trayectoria::check_coordenada_padre(int fil, int col) {
    
    vector<coordenada>::iterator x=trayecto_.end()-2;
    coordenada aux=(*x);
    
    if(aux.get_fila()==fil&&aux.get_columna()==col)
       return true;
    
    return false;
}
vector<coordenada> trayectoria::get_trayecto(void) {
    
    return trayecto_;
}
int trayectoria::sz_vector(void) {
    
    return trayecto_.size();
}
void trayectoria::set_coste(int val) {
    
    coste_=val;
}
int trayectoria::get_coste(void) {
    
    return coste_;
}
void trayectoria::print_trayecto(void) {
    
    for(vector<coordenada>::iterator i = trayecto_.begin(); i != trayecto_.end(); i++)
       cout<<(*i).get_fila()<<" - "<<(*i).get_columna()<<endl;
       
    cout<<"-----------"<<endl;
    
}