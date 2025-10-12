#include "celda.hpp"

celda::celda(void):
    visitada_(false),
    obstaculo_(false)
{}

celda::~celda(void) {
    
}

void celda::set_visitada(bool estado) {
    
    visitada_=estado;
    
}
bool celda::get_visitada(void) {
    
    return visitada_;
    
}
bool celda::set_obst(bool estado) {
    
    obstaculo_=estado;
}
bool celda::get_obst(void) {
    
    return obstaculo_;
}
