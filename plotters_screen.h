#ifndef PLOTTERS_SCREEN_H
#define PLOTTERS_SCREEN_H
#include <QtWidgets>
#include "plotters_screen.h"
#include "reports_screen.h"
#include "configurator.h"
#include "qcustomplot.h"
#include "termosensor.h"
class Plotters_screen:public QWidget
{
    Q_OBJECT
public:
    explicit Plotters_screen(Configurator *configurator, QWidget *parent = 0);
    void updateSensors();               //изменить размер коллекции датчиков
    void initializeSensors();           //раздать имена датчикам
    void readSensors();                 //читать инфу с датчиков. Обновляется по таймеру
    ~Plotters_screen();

private:
    //------механика-----
    Configurator* config;
    QVector<Termosensor> sensvec;               //объявлена коллекция датчиков
    QVector<QVector<double>*> sensors;          // значения сенсоров
    QVector<QVector<double>*> timepick;          // значения временных отметок интерпретированные в графику
    QVector<QVector<QDateTime>*> timepoint;         // значения временных отметок
    QTimer* timer;


    //-------визуальные компоненты
    //-----виджеты, количество которых зависит от количества датчиков
    QVector<QCustomPlot*> plots;                                        //коллекция виджетов-плоттеров
    QVector<QLabel*> plotIDlabel;                                        //коллекция имен графиков
    QVector<QVBoxLayout*> localLayout;                                  //коллекция слоев, на который будут помещены все вышеперечисленные виджеты
    //-----виджеты, количество которых не зависит от количества датчиков---
    QPushButton * next_pb;
    QPushButton * back_pb;
    QLabel * current_screen_lbl;
    QLabel * current_data_time_lbl;
    //--------слои-----------------------------------
    QVBoxLayout * mainlayout;
    QVBoxLayout * topLayout;
    QGridLayout * midLayout;
    QHBoxLayout * downLayout;
    //--------панели----------
    QGroupBox * top_grb;            //панели, где сгруппированы элементы управления
    QGroupBox * mid_grb;
    QGroupBox * down_grb;
    //-------смежные окна----------
    Reports_screen * rprt_screen;
    //------методы----------------
    //методы, которые создают группы виджетов в окне конфигуратора
    QGroupBox *createTopGroup();
    QGroupBox *createMidGroup();
    QGroupBox *createDownGroup();

signals:
    void ShowSettingsScreen();
    void ShowReportsScreen();
    void GetTblsData(QVector<QVector<double>*>, QVector<QVector<QDateTime>*>);
private slots:
    void on_Btn_Back_Clicked();
    void on_Btn_Next_Clicked();
    void updateSensorSlot();
};

#endif // PLOTTERS_SCREEN_H
