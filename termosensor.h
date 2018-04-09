#ifndef TERMOSENSOR_H
#define TERMOSENSOR_H
#include "configurator.h"

class Termosensor
{
private:
    double id;
    double temperature;
    double minimal_temperature;
    double maximal_temperature;
    Configurator* config;
public:
    Termosensor(Configurator *c);
    Termosensor() = default;
    Termosensor(const Termosensor& t);
    void SetID(int t);
    int GetID();
    double GetTemperature(Configurator *c);
};

#endif // TERMOSENSOR_H
