#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <vector>
#include <string>

#include "Entrega.h"
#include "Tarea.h"
#include "Quiz.h"
#include "Parcial.h"

class Estudiante{

private:

    int codigo;
    std::string nombre;
    std::vector<Entrega> entregas;

public:

    Estudiante();
    Estudiante(int, std::string);
    bool agregarEntrega(std::string, double, int);
    bool eliminarEntrega(Entrega);
    bool operator==(const Estudiante& otro) const;
    std::string toString();
    int getCodigo() const;
    void setCodigo(int);
    std::string getNombre ()const;
    void setNombre(std::string);
    std::vector<Entrega> getEntregas() const;

};

#endif
