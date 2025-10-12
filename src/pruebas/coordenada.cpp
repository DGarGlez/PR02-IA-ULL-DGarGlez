#include "coordenada.hpp"

coordenada::coordenada(void):
    fila_(0),
    columna_(0)
{}

coordenada::coordenada(const int& x, const int& y):
    fila_(x),
    columna_(y)
{}
    
coordenada::~coordenada(void) {
    
}

int coordenada::get_fila(void) {
    
    return fila_;
} 
int coordenada::get_columna(void) {
    
    return columna_;
}
void coordenada::set_fila(int val) {
    
    fila_=val;
}
void coordenada::set_columna(int val) {
    
    columna_=val;
}
bool coordenada::operator!=(coordenada x) {
    
    if(fila_==x.get_fila()&&columna_==x.get_columna())
       return false;
    
    return true;
}
bool coordenada::operator==(coordenada x) {
    
    if(fila_==x.get_fila()&&columna_==x.get_columna())
       return true;
       
    return false;
}
