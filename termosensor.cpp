#include "termosensor.h"
#include "configurator.h"
#include <ctime>

Termosensor::Termosensor(Configurator *c)
{
    this->config = c;
    this->id = 0;
    this->temperature = 0;
    this->minimal_temperature = c->GetMinimalT();
    this->maximal_temperature = c->GetMaximalT();
}

Termosensor::Termosensor(const Termosensor &t)
{
    id = t.id;
    temperature = t.temperature;
}
//сеттеры
void Termosensor::SetID(int t){
    this->id = t;
}

//геттеры
int Termosensor::GetID(){
    return this->id;
}


//определение температуры (пока рандомайзер)
double Termosensor::GetTemperature(Configurator *c){
    //------------------------этот метод надо будет переопределить в соответствии с привязкой к GPIO Raspberry PI
    srand(time(NULL));
    double min_t = c->GetMinimalT() + 2;    //+1 и -1 - имитиция выхода за границы контроллируемого диапазона
    double max_t = c->GetMaximalT() - 2;
    return this->temperature = min_t + rand() % (abs(max_t - (-min_t)));
}

