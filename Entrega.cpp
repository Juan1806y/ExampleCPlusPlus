#include "Entrega.h"

Entrega::Entrega() {

    nombre = "";
    nota = 0;
    porcentaje = 0;
}

Entrega::Entrega(std::string nombre, double nota, double porcentaje) {
    this->nombre=nombre;
    this->nota=nota;
    this->porcentaje=porcentaje;
}

bool Entrega::operator==(const Entrega& otro){
    return (this->nombre == otro.nombre);
}

std::string Entrega::toString() {
    return nombre + "-" + std::to_string(nota);
}

std::string Entrega::getNombre() const{
    return nombre;
}

void Entrega::setNombre(std::string nombre) {
    this->nombre = nombre;
}

double Entrega::getNota() const{
    return nota;
}

void Entrega::setNota(double nota) {
    this->nota = nota;
}

double Entrega::getPorcentaje() const{
    return porcentaje;
}

void Entrega::setPorcentaje(double porcentaje) const{
    this->porcentaje=porcentaje;
}

