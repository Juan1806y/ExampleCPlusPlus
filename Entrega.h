#ifndef ENTREGA_H
#define ENTREGA_H

#include <vector>
#include <string>

class Entrega{

private:

    std::string nombre;
    double nota;
    mutable double porcentaje;
    void setPorcentajeInternal(double nuevoPorcentaje) {
        porcentaje = nuevoPorcentaje;
    }

public:

    Entrega();
    Entrega(std::string, double, double);
    bool operator==(const Entrega& otro) const;
    std::string toString();
    std::string getNombre() const;
    void setNombre(std::string);
    double getNota() const;
    void setNota(double);
    double getPorcentaje() const;
    void setPorcentaje(double)const;

};

#endif
