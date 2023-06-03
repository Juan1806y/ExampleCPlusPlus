#include "SistemaAcademico.h"
#include <algorithm>

SistemaAcademico::SistemaAcademico() {
    estudiantes = std::vector<Estudiante>();
}

bool SistemaAcademico::agregarEstudiante(int codigo, std::string nombre) {
    bool agrego = false;
    Estudiante estudianteAux(codigo, nombre);
    auto iterador = std::find(estudiantes.begin(), estudiantes.end(), estudianteAux);
    if (iterador == estudiantes.end()) {
        estudiantes.push_back(estudianteAux);
        agrego = true;
    }
    return agrego;
}

bool SistemaAcademico::eliminarEstudiante(Estudiante e) {
    bool elimino = false;

    auto iter = std::remove(estudiantes.begin(), estudiantes.end(), e);
    if (iter != estudiantes.end()) {
        estudiantes.erase(iter, estudiantes.end());
        elimino = true;
    }

    return elimino;
}

std::vector<Estudiante>& SistemaAcademico::getEstudiantes() {
    return this->estudiantes;
}
