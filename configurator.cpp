#include "configurator.h"
#include <QMessageBox>
Configurator::Configurator()
{
    serialnumber = "1111";                        //серийный номер не установлен
    containernum = "1111";                          //номер контейнера не установлен
    countofsensors = 1;                         //количество датчиков не установлено
    discretization = 1;
    minimal_t = 0;
    maximal_t = 1;
}

void Configurator::SetSerialNumber(QString s)    //Установить серийный номер
{
    this->serialnumber = s;
}
QString Configurator::GetSerialNumber()          //Предоставить серийный номер
{
    return this->serialnumber;
}

void Configurator::SetSensorCount(int n)         //установить количество датчиков
{
    this->countofsensors = n;
}
int Configurator::GetSensorCount()              //предоставить количество датчиков
{
    return this->countofsensors;
}

void Configurator::SetContainerNumber(QString s)
{
    this->containernum = s;
}

QString Configurator::ContainerNumber()
{
    return this->containernum;
}

void Configurator::SetPlotterSettings(int scale, int minwin, int maxwin)
{
    this->plotterscale = scale;
    this->plotterminlimit = minwin;
    this->plottermaxlimit = maxwin;
}

int Configurator::GetPlotterScale()
{
    return this->plotterscale;
}

int Configurator::GetPlotterMinLim()
{
    return this->plotterminlimit;
}

int Configurator::GetPlotterMaxLim()
{
    return this->plottermaxlimit;
}

void Configurator::SetDiscretization(double a)   //установить периодичность опроса датчиков
{
    this->discretization = a;
}
double Configurator::GetDiscretization()         //предоставить периодичность опроса датчиков
{
    return this->discretization;
}
void Configurator::SetMinimalT(double min)       //задать минимальную температуру
{
    this->minimal_t = min;
}
double Configurator::GetMinimalT()               //предоставить минимальную температуру
{
    return this->minimal_t;
}
void Configurator::SetMaximalT(double max)       //задать максимальную температуру
{
    this->maximal_t = max;
}
double Configurator::GetMaximalT()               //предоставить максимальную температуру
{
    return this->maximal_t;
}
bool Configurator::CheckWarning()                //проверить, что конфигурация установлена и вывести предупреждающее сообщение, если какой-то параметр остался неопределен
{
QString message = "";
    if(countofsensors==0)
    {
        message.append("количество датчиков = 0\n");
    }
    if (serialnumber.isEmpty())
    {
        message.append("Не введен серийный номер устройства\n");
    }
    if (this->containernum.isEmpty())
    {
        message.append("Не введен регистрационный номер контейнера\n");
    }
    if  (minimal_t>=maximal_t)
    {
        message.append("Проверьте диапазоны температур\n");
    }
    if (!(message.isEmpty()))
    {
        QMessageBox::information(0, "Внимание", message);
        return false;
    }
    return true;
}
//----------деструктор-------
Configurator::~Configurator()
{

}
