#include "Estudiante.h"
#include "Tarea.h"
#include <vector>
#include <algorithm>
#include <QDebug>

Estudiante::Estudiante(){

    this->codigo = 0;
    this->nombre = "";
    this->entregas = std::vector<Entrega>();

}

Estudiante::Estudiante(int codigo, std::string nombre){

    this->codigo = codigo;
    this->nombre = nombre;
    this->entregas = std::vector<Entrega>();

}

bool Estudiante::agregarEntrega(std::string nombre, double nota, int tipoEntrega){
    bool agrego = false;
    Entrega entregasAux(nombre, nota,0);

    if (tipoEntrega == 0) {
        Tarea tareaAux(nombre, nota);
        entregasAux = tareaAux;
    } else if (tipoEntrega == 1) {
        Quiz quizAux(nombre, nota);
        entregasAux = quizAux;
    } else if (tipoEntrega == 2) {
        Parcial parcialAux(nombre, nota);
        entregasAux = parcialAux;
    }

    auto iterador = std::find(entregas.begin(), entregas.end(), entregasAux);

    if (iterador == entregas.end()) {
        entregas.push_back(entregasAux);
        agrego = true;
    }
    qDebug() << "Tamaño del vector entregas: " << entregas.size();
    return agrego;
}


bool Estudiante::eliminarEntrega(Entrega entrega) {
    bool elimino = false;

    auto iterador = std::remove(entregas.begin(), entregas.end(), entrega);
    if (iterador != entregas.end()) {
        entregas.erase(iterador, entregas.end());
        elimino = true;
    }

    return elimino;

}

bool Estudiante::operator==(const Estudiante& otro) {
    return (this->codigo == otro.codigo) || (this->nombre == otro.nombre);
}

std::string Estudiante::toString(){
    return std::to_string(codigo) + "-" + nombre;
}

int Estudiante::getCodigo() const{
    return this->codigo;
}

void Estudiante::setCodigo(int codigo){
    this->codigo = codigo;
}

std::string Estudiante::getNombre () const{
    return this->nombre;
}

void Estudiante::setNombre(std::string nombre){
    this->nombre = nombre;
}

std::vector<Entrega>& Estudiante::getEntregas(){
    qDebug() << "Tamaño del vector entregas: " << entregas.size();
    return this->entregas;
}
