#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H
#include <QString>

class Configurator
{
private:
    QString serialnumber;
    QString containernum;
    int countofsensors;
    double discretization;
    double minimal_t;
    double maximal_t;
    int plotterscale = 5;
    int plotterminlimit = 2;
    int plottermaxlimit = 5;
public:
    Configurator();
    void SetDiscretization(double a);   //установить периодичность опроса датчиков
    double GetDiscretization();         //предоставить периодичность опроса датчиков
    void SetMinimalT(double min);                 //задать минимальную температуру
    double GetMinimalT();               //предоставить минимальную температуру
    void SetMaximalT(double max);                 //задать максимальную температуру
    double GetMaximalT();               //предоставить максимальную температуру
    void SetSerialNumber(QString s);    //установить серийный номер
    void SetSensorCount(int n);         //установить количество датчиков
    bool CheckWarning();               //проверить, что конфигурация установлена и вывести предупреждающее сообщение, если какой-то параметр остался неопределен
    QString GetSerialNumber();          //предоставить серийный номер
    int GetSensorCount();
    void SetContainerNumber(QString s);    //установить номер контейнера
    QString ContainerNumber();          //предоставить номер контейнера
    void SetPlotterSettings(int scale, int minwin, int maxwin);  //установить настройки виджетов-плоттеров
    int GetPlotterScale();                  //масштабная сетка плоттера
    int GetPlotterMinLim();                 //минимальное значение по оси Х плоттера
    int GetPlotterMaxLim();                 //максимальное значение по оси Х плоттера
    ~Configurator();
};

#endif
