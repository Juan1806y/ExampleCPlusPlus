#ifndef SISTEMAACADEMICO_H
#define SISTEMAACADEMICO_H

#include <vector>
#include <string>

#include "Estudiante.h"

class SistemaAcademico{

private:

    std::vector<Estudiante> estudiantes;

public:

    SistemaAcademico();
    bool agregarEstudiante(int, std::string);
    bool eliminarEstudiante(Estudiante);
    std::vector<Estudiante>& getEstudiantes() ;

};

#endif
