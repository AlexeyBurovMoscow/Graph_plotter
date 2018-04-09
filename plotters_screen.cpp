#include "plotters_screen.h"
Plotters_screen::Plotters_screen(Configurator * configurator, QWidget *parent):QWidget(parent)
{
    //--------механика--------------------------
    config = configurator;
    timer = new QTimer(this);
    timer->setTimerType(Qt::TimerType::PreciseTimer);


    //--------связи со смежными окнами----------
    rprt_screen = new Reports_screen(config);
    //--------визуальные компоненты. Создаем и компонуем на форме
    mainlayout = new QVBoxLayout;
    topLayout = new QVBoxLayout;
    downLayout = new QHBoxLayout;
    midLayout = new QGridLayout;
    mainlayout->addWidget(createTopGroup(),0);//(изменяя число в этом методе можно менять отступы элементов на слое)
    mainlayout->addWidget(createMidGroup(),2);//(изменяя число в этом методе можно менять отступы элементов на слое)
    mainlayout->addWidget(createDownGroup(),0);//(изменяя число в этом методе можно менять отступы элементов на слое)
    this->setLayout(mainlayout);
    //-------сигналы и слоты------
    connect(next_pb,SIGNAL(clicked(bool)),SLOT(on_Btn_Next_Clicked()));

    //                              результаты измерений            метки времени                                           результаты измерений                метки времени
    connect(this,SIGNAL(GetTblsData(QVector<QVector<double>*>, QVector<QVector<QDateTime>*>)),rprt_screen,SLOT(SetTblsData(QVector<QVector<double>*>, QVector<QVector<QDateTime>*>)));
    //                                  sensors                     timepoint                                               sensors                             timepoint

    connect(rprt_screen,&Reports_screen::ShowPlottersScreen,this,Plotters_screen::show);
    connect(back_pb,SIGNAL(clicked(bool)),SLOT(on_Btn_Back_Clicked()));
    connect(timer, &QTimer::timeout, this, Plotters_screen::updateSensorSlot);      //соединил таймер с методом опроса датчиков

    //qDebug()<<"configurator.GetSensorCount()"<<configurator->GetSensorCount();
    //--------внешний вид---------------
    setWindowTitle("Окно мониторнинга");
    this->setFixedSize(800,480);
}
//---------методы размещения виджетов по панелям
QGroupBox *Plotters_screen::createTopGroup()
{
    top_grb = new QGroupBox(/*tr("Top widgets panel")*/);
    current_screen_lbl = new QLabel("Мониторинг");                //надпись с модулем программы
    current_screen_lbl->setAlignment(Qt::AlignCenter);
    current_data_time_lbl = new QLabel("Время, дата:");
    current_data_time_lbl->setAlignment(Qt::AlignCenter);
    //top_grb = new QGroupBox(tr("Top widgets panel"));               //лэйбл с именем программы
    topLayout->addWidget(current_screen_lbl);                       //лэйбл с именем модуля
    topLayout->addWidget(current_data_time_lbl);                    //лэйбл со временем/датой
    top_grb->setLayout(topLayout);
    return top_grb;
}
QGroupBox *Plotters_screen::createMidGroup()
{
    int posX=0;int posY = 0;                                     //позиционирование графопостроителей на форме
    double now = QDateTime::currentDateTime().toTime_t();

    mid_grb = new QGroupBox(/*tr("Plotters panel")*/);
   // qDebug()<<"createMidGroup.GetSensorCnt()"<<config->GetSensorCount();
    for (int i = 0; i<config->GetSensorCount();i++)
    {
        //qDebug()<<i;
        plots << new QCustomPlot();
        plotIDlabel<<new QLabel("Датчик #" + QString::number(i + 1));
        localLayout<<new QVBoxLayout;
        localLayout[i]->addWidget(plotIDlabel[i]);
        localLayout[i]->addWidget(plots[i],1);              //(изменяя число в этом методе можно менять отступы элементов на слое)
        if (i%2==0)                                         //красиво размещаем виджеты графопостроителей в GridLayout
                {
                      posY+=1;
                      posX = 0;
                      midLayout->addLayout(localLayout[i],posX,posY);
                }
                if (i%2!=0)
                {
                      posX+=1;
                      midLayout->addLayout(localLayout[i],posX,posY);
                }
                //------оформляем пространство графиков
                plots[i]->addGraph();
                plots[i]->xAxis->setLabel("время");                  //по оси Х откладываем время
                plots[i]->yAxis->setLabel("температура");           //по оси Y откладываем температуру
                plots[i]->addGraph();                                                                        //добавить пространство графика в каждый QcustomPlot
                plots[i]->xAxis->setRange(now,now+config->GetPlotterScale());
                plots[i]->yAxis->setRange(config->GetMinimalT()-1,config->GetMaximalT()+1);               //настраиваем диапазоны графика (по оси Y значения температур от мин. до макс.)
                                                                                                                //-1 / +1 чтобы график не сливался с осью
                plots[i]->xAxis->setTickLabelType(QCPAxis::ltDateTime);                                 // Подпись координат по Оси X в качестве Даты и Времени
                plots[i]->xAxis->setDateTimeFormat("hh:mm:ss");

    }
    mid_grb->setLayout(midLayout);
    return mid_grb;
}
QGroupBox *Plotters_screen::createDownGroup()
{
    down_grb = new QGroupBox(/*tr("Down widgets panel")*/);
    next_pb = new QPushButton("К отчетам");
    back_pb = new QPushButton("К настройкам");
    downLayout->addWidget(next_pb);
    downLayout->addWidget(back_pb);
    down_grb->setLayout(downLayout);
    return down_grb;
}
//---------методы для элементов управления на форме
//---------кнопка "к настройкам-----------"

void Plotters_screen::on_Btn_Back_Clicked()
{
    this->close();
    emit ShowSettingsScreen();
    delete mainlayout;
}
//---------кнопка "к отчетам"----------------
void Plotters_screen::on_Btn_Next_Clicked()
{
    this->close();
    emit GetTblsData(sensors, timepoint);
    rprt_screen->show();
}
//---------механика--------------------------
//--------обновить размер коллекции датчиков
void Plotters_screen::updateSensors()
{
    sensvec.resize(config->GetSensorCount());
}
//--------Подготовить инфраструктуру-----------------
void Plotters_screen::initializeSensors()
{

    for(int i = 0; i<sensvec.size(); i++){
        //именуем датчики
        sensvec[i].SetID(i);                                                                        //присвоить датчикам ID
        //qDebug()<<"init with id = "<< i;
    }

    // инициализаация "большой" коллекции, где будут храниться коллекции значений, полученных с датчиков
    //+инициализация "большой" коллекции, где будут храниться интерпретированные в графику значения временных меток
    for(int i = 0; i < sensors.size(); ++i){
        delete sensors[i];
        delete timepick[i];
        delete timepoint[i];
    }
    sensors.clear();
    timepick.clear();
    timepoint.clear();

    for (int i = 0; i < sensvec.size(); ++i){
        QVector<double>* vect = new QVector<double>();
        QVector<double>* vect1 = new QVector<double>();
        QVector<QDateTime>* vect2 = new QVector<QDateTime>();
        sensors.append(vect);
        timepick.append(vect1);
        timepoint.append(vect2);
    }
    //qDebug()<<"sensors size = "<<sensors.size();
}
//------обновлять инфу по таймеру-------------
void Plotters_screen::updateSensorSlot()
{
    //механика
    QVector<int> min_axis(config->GetSensorCount(),0);//минимальное значение оси времени на графике. Число графиков м.б. разным, поэтому коллекции
    QVector<int> max_axis(config->GetSensorCount(),0);//максимальное значение оси времени на графике.

    static double countshifting = 0;                                     //для перерисовки графика по выходу графика за пределы окна
    QDateTime dt = QDateTime::currentDateTime();                         //текущее время
    double now = dt.toTime_t();                                         //для отстройки графика представляем значение даты и времени в виде double
    //qDebug()<<"now"<<now;


    //выполнение
    countshifting = countshifting + config->GetDiscretization();
    current_data_time_lbl->setText(dt.toString());                      //обновляем дату и время в заголовке окна
    //обновляем значения с датчиков
    for (int i = 0; i<sensvec.size(); ++i)
    {
        double temperature = sensvec[i].GetTemperature(config);
        //-------контроль выхода за установленые диапазоны значений
        if((temperature<config->GetMinimalT())||(temperature>config->GetMaximalT()))
        {
            qDebug()<<"SMS:warning temperature";
            QApplication::beep();
            plots[i]->graph(0)->setPen(QPen(QColor(Qt::red)));
        }
        else
        {
            plots[i]->graph(0)->setPen(QPen(QColor(Qt::blue)));
        }
        plotIDlabel[i]->setText("Датчик №" + QString::number(i)+"  Значение" + QString::number(temperature));//обновляем метку с температурой
        sensors[i]->append(temperature);
        timepick[i]->append(now);
        timepoint[i]->append(dt);
        //на всякий случай чтобы посмотреть содержимое коллекций
        //qDebug()<<*sensors[i];
        //qDebug()<<*timepoint[i];
        //qDebug()<<"sensors-vector"<<sensors.size();
        //qDebug()<<"timepick-vector"<<timepick.size();
        //qDebug()<<"timepoint-vector"<<timepoint.size();


        //-------постройка графика-------

        if (countshifting>config->GetPlotterScale())
        {
            for (int i = 0; i<config->GetSensorCount();i++)
            {
            plots[i]->xAxis->setRange(min_axis[i] +now - config->GetPlotterMinLim(),now + config->GetPlotterMaxLim());
            min_axis[i] = min_axis[i] + config->GetPlotterScale();
            max_axis[i] = max_axis[i] + config->GetPlotterScale();
            }
            countshifting = 0;
        }
        plots[i]->graph(0)->setData(*timepick[i],*sensors[i]);
        plots[i]->replot();
    }
}
//-----начать опрос датчиков--------------
void Plotters_screen::readSensors()
{
timer->start(1000*config->GetDiscretization());
}
//------деструктор-----------------
Plotters_screen::~Plotters_screen()
{
    for(int i = 0; i < sensors.size(); ++i){
        delete sensors[i];
        delete timepick[i];
        delete timepoint[i];
    }
    sensors.clear();
    timepick.clear();
    timepoint.clear();
}
