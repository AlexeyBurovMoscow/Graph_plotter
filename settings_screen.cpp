
#include "settings_screen.h"

Settings_screen::Settings_screen(QWidget *parent):QWidget(parent)
{

//---------связи со смежными классами-
    configurator = new Configurator();
//---------связи со смежными окнами-
    pswd_screen = new Password_screen();
    //plts_screen = new Plotters_screen(configurator);

//---------виджеты. создание и компоновка на форме-----------------
    mainlayout = new QVBoxLayout();
    topLayout = new QVBoxLayout();
    leftlayout = new QVBoxLayout();
    rightlayout = new QVBoxLayout();
    downlayout = new QVBoxLayout();
    gridlayout = new QGridLayout();
    mainlayout->addWidget(createTopGroup());
    gridlayout->addWidget(createLeftGroup(),0,0);
    gridlayout->addWidget(createRightGroup(),0,1);
    mainlayout->addLayout(gridlayout);
    mainlayout->addWidget(createDownGroup());
    this->setLayout(mainlayout);
//--------слоты и сигналы-----------
    connect(extended_conf_pb, SIGNAL(clicked(bool)),SLOT(on_Btn_Pswd_clicked()));//сигнал к открытию окна с паролем
    connect(pswd_screen,&Password_screen::ShowSettingsScreen,this,&Settings_screen::ShowExtendedConfigurator);//слушаем сигнал от окна с паролем на отображение этого окна
    connect(apply_settings_pb, SIGNAL(clicked(bool)),SLOT(on_Btn_Next_clicked()));//сигнал к открытию окна с плоттерами
    //connect(plts_screen,&Plotters_screen::ShowSettingsScreen,this,&Settings_screen::show);//слушаем сигнал от окна с плоттерами на отображение этого окна
    connect(discret_sl,SIGNAL(valueChanged(int)),SLOT(on_Slider_Changed(int)));         //слайдер. меняется положение слайдера и перерисовывается надпись, говорящая о частоте опроса датчиков
//--------внешний вид---------------
    setWindowTitle("Окно конфигурации");
    this->setFixedSize(800,480);
}
//---------

//---------методы, создающие группы виджетов------------------
//--------создаем верхнюю группу виджетов---------------------
QGroupBox *Settings_screen::createTopGroup()
{
    top_grb = new QGroupBox(/*tr("Top widgets panel")*/);
    program_name_lbl = new QLabel("Конфигуратор устройства");       //надпись с именем программы
    program_name_lbl->setAlignment(Qt::AlignCenter);
    program_module_lbl = new QLabel("Конфигуратор");                //надпись с модулем программы
    program_module_lbl->setAlignment(Qt::AlignCenter);
    topLayout->addWidget(program_name_lbl);                         //лэйбл с именем программы
    topLayout->addWidget(program_module_lbl);                       //лэйбл с именем модуля
    top_grb->setLayout(topLayout);
    return top_grb;
}

//------создаем левую группу виджетов-----------------------
QGroupBox *Settings_screen::createLeftGroup()
{
    left_grb = new QGroupBox(/*tr("Left widgets panel")*/);
    //слайдер и все что с ним связано
    discret_sl = new QSlider(Qt::Horizontal);
    discret_sl->setRange(1,5);
    discret_sl->setTickInterval(1);
    discret_sl->setTickPosition(QSlider::TicksBelow);

    fdiscret_lbl = new QLabel("Частота опроса датчиков");
    sensor_cntr_lbl = new QLabel("Количество датчиков");

    sensor_cnt_spin = new QSpinBox;
    min_temp_lbl = new QLabel("Нижний предел температуры");
    min_temp_dblspin = new QDoubleSpinBox;
    max_temp_lbl = new QLabel("Верхний предел температуры");
    max_temp_dblspin = new QDoubleSpinBox;
    discret_lbl = new QLabel("Частота опроса");
    //для счетчика сенсоров
    sensor_cnt_spin->setMinimum(1);
    sensor_cnt_spin->setMaximum(4);
    sensor_cnt_spin->setSingleStep(1);
    //для счетчика минимальной температуры
    min_temp_dblspin->setValue(0);
    min_temp_dblspin->setMinimum(-10);
    min_temp_dblspin->setMaximum(10);
    min_temp_dblspin->setSingleStep(0.5);
    min_temp_dblspin->setDecimals(1);
    //для счетчика максимальной температуры
    max_temp_dblspin->setValue(3);
    max_temp_dblspin->setMinimum(-10);
    max_temp_dblspin->setMaximum(10);
    max_temp_dblspin->setSingleStep(0.5);
    max_temp_dblspin->setDecimals(1);

    leftlayout->addWidget(sensor_cntr_lbl); //лэйбл счетчика дaтчиков
    leftlayout->addWidget(sensor_cnt_spin);//счетчик датчиков
    leftlayout->addWidget(min_temp_lbl);    //лэйбл нижнего предела температур
    leftlayout->addWidget(min_temp_dblspin);//нижний предел температур
    leftlayout->addWidget(max_temp_lbl);    //лэйбл верхнего предела температур
    leftlayout->addWidget(max_temp_dblspin);//верхний предел температур
    leftlayout->addWidget(discret_lbl);     //лэйбл дискретизации
    leftlayout->addWidget(discret_sl);      //слайдер чачтоты опроса
    leftlayout->addWidget(fdiscret_lbl);    //лэйбл частоты опроса
    left_grb->setLayout(leftlayout);
    return left_grb;
}
//------создаем правую группу виджетов
QGroupBox *Settings_screen::createRightGroup()
{
    right_grb = new QGroupBox(/*tr("Right widgets panel")*/);
    serial_lbl = new QLabel("Серийный номер устройства");
    serial_le = new QLineEdit();
    container_num_lbl = new QLabel("Регистрационный номер контейнера");
    container_num_le = new QLineEdit();
    //------ограничения на допустимые значения вводимых символов
    serial_le->setValidator(new QRegExpValidator(QRegExp("^([1-9][0-9]*|0)(\\.|,)[0-9]{2}"), this));     //определил ограничения на ввод только цифр в серийный номер
    //----изначально скрытые виджеты-------------
      //эти поля меняются на true если пароль правильный
    serial_le->setEnabled(false);
    container_num_le->setEnabled(false);
    rightlayout->addWidget(serial_lbl);//лэйбл с серийным номером изделия
    rightlayout->addWidget(serial_le);//лайнэдит с серийным номером изделия
    rightlayout->addWidget(container_num_lbl);//лэйбл с номером контейнера
    rightlayout->addWidget(container_num_le);//лайнэдит с номером контейнера
    right_grb->setLayout(rightlayout);
    return right_grb;
}
//------создаем нижнюю группу виджетов
QGroupBox *Settings_screen::createDownGroup()
{
    down_grb = new QGroupBox(/*tr("Down widgets panel")*/);
    apply_settings_pb = new QPushButton("Применить настройки");
    extended_conf_pb = new QPushButton("Расширенный конфигуратор");
    downlayout->addWidget(apply_settings_pb);
    downlayout->addWidget(extended_conf_pb);
    down_grb->setLayout(downlayout);
    return down_grb;
}

//-----реакция на ввод пароля----------
void Settings_screen::ShowExtendedConfigurator()
{
    //------делаем активными и видимыми запароленые элементы формы
    setWindowTitle("Extended-configurator");
    serial_lbl->setVisible(true);
    serial_le->setVisible(true);
    serial_le->setEnabled(true);
    container_num_lbl->setVisible(true);
    container_num_le->setEnabled(true);
    this->show();
}
//-------------методы-реакции на элементы управления-----------
//-------------на кнопку "расширенный конфигуратор"
void Settings_screen::on_Btn_Pswd_clicked()
{
    pswd_screen->show();
}
//------------на кнопку "применить настройки"------------------
void Settings_screen::on_Btn_Next_clicked()
{
    sensor_cnt_spin->setEnabled(false);//больше счетчик датчиков поменять нельзя, т.к. во первых-любое подключение датчиков происходит на выключенном устройстве. Во-вторых прога крашится
    configurator->SetSensorCount(sensor_cnt_spin->value());//утащил значения с элементов формы в конфигуратор
    configurator->SetMinimalT(min_temp_dblspin->value());
    configurator->SetMaximalT(max_temp_dblspin->value());
    configurator->SetSerialNumber(serial_le->text());
    configurator->SetContainerNumber(container_num_le->text());
    plts_screen = new Plotters_screen(configurator);
    connect(plts_screen,&Plotters_screen::ShowSettingsScreen,this,&Settings_screen::show);//слушаем сигнал от окна с плоттерами на отображение этого окна
    //комментарии снять после отладки
    if (configurator->CheckWarning())
    {
        //qDebug()<<"widgets="<<configurator->GetSensorCount();
        plts_screen->updateSensors();
        plts_screen->initializeSensors();
        plts_screen->readSensors();
        this->close();
        plts_screen->repaint();
        plts_screen->show();
    }
}
//------------на слайдер--------------------------
void Settings_screen::on_Slider_Changed(int value)
{
    //int scale, min, max;
    int v = value;
    switch (v) {
    case 1:
        v = 1;
        fdiscret_lbl->setText("1 second");
        /*scale = 5;
        min = 2;
        max = 5;*/
        configurator->SetPlotterSettings(5,2,5);
        break;
    case 2:
        v = 2;
        fdiscret_lbl->setText("2 second");
        /*scale = 8;
        min = 8;
        max = 20;*/
        configurator->SetPlotterSettings(8,8,20);
        break;
    case 3:
        v = 3;
        fdiscret_lbl->setText("3 second");                          //здесь прописать параметры. Пока на 2 положения слайдера сделано
        /*scale = 10;
        min = 10;
        max = 25;*/
        configurator->SetPlotterSettings(10,10,25);
        break;
    case 4:
        v = 4;
        fdiscret_lbl->setText("4 second");
        /*scale = 15;
        min = 15;
        max = 30;*/
        configurator->SetPlotterSettings(15,15,30);
        break;
    case 5:
        v = 5;
        fdiscret_lbl->setText("5 second");
        /*scale = 20;
        min = 20;
        max = 40;*/
        configurator->SetPlotterSettings(20,20,40);
        break;
    default:
        v = 1;
        fdiscret_lbl->setText("1 second");
        /*scale = 5;
        min = 2;
        max = 5;*/
        configurator->SetPlotterSettings(5,2,5);
        break;
    }
    configurator->SetDiscretization(v);
    //configurator->SetPlotterSettings(scale, min, max);
}
//-------деструктор----------------
Settings_screen::~Settings_screen()
{

}
