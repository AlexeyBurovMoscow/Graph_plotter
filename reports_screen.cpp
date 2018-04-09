
#include "reports_screen.h"

Reports_screen::Reports_screen(Configurator *configurator,  QWidget *parent):QWidget(parent)
{
//-------механика-------------
    config = configurator;

//-------визуальные компоненты
    mainlayout = new QVBoxLayout;
    topLayout = new QVBoxLayout;
    //midLayout = new QVBoxLayout;
    midLayout = new QGridLayout;
    downLayout = new QHBoxLayout;
    current_screen_lbl = new QLabel("Отчеты");
    print_pb = new QPushButton("Печать отчетов");
    back_pb = new QPushButton("К мониторингу");
    apply_pb = new QPushButton("Выбрать даты");
    mainlayout->addWidget(createTopGroup());
    mainlayout->addWidget(createMidGroup());
    mainlayout->addWidget(createDownGroup());
    print_pb->setEnabled(false);
    back_pb->setEnabled(false);
    savef_pb->setEnabled(false);
    this->setLayout(mainlayout);
//-------слоты и сигналы----------
    connect(back_pb,SIGNAL(clicked(bool)),SLOT(on_Btn_Back_Clicked()));     //связал кнопку "Назад к отчетам" с формой
    connect(print_pb, SIGNAL(clicked(bool)), SLOT(on_PrintBtn_clicked()));  //связал кнопку "Печать" с формой
    connect(apply_pb,SIGNAL(clicked(bool)),SLOT(on_ApplyBtn_clicked()));    //связал кнопку "Применить даты" с формой
    connect(savef_pb,SIGNAL(clicked(bool)),SLOT(on_SaveF_Btn_clicked()));   //связал кнопку "Сохранить в файл" с формой
    //--------внешний вид---------------
    setWindowTitle("Окно отчетов");
    this->setFixedSize(800,480);
}
//-------методы доступа-------------------------------
void Reports_screen::SetMinSelectedDate(QDate min_date)
{
    this->min_selected_date = min_date;
}

void Reports_screen::SetMaxSelectedDate(QDate max_date)
{
    this->max_selected_date = max_date;
}

QDate Reports_screen::GetMinSelectedDate()
{
    return this->min_selected_date;
}

QDate Reports_screen::GetMaxSelectedDate()
{
    return this->max_selected_date;
}

void Reports_screen::SetMinMeasuredDate(QDate min_date)
{
    this->min_measured_date = min_date;
}

void Reports_screen::SetMaxMeasuredDate(QDate max_date)
{
    this->max_measured_date = max_date;
}

QDate Reports_screen::GetMinMeasuredDate()
{
    return this->min_measured_date;
}

QDate Reports_screen::GetMaxMeasuredDate()
{
    return this->max_measured_date;
}
//----методы для компоновки элементов управления------
QGroupBox *Reports_screen::createTopGroup()
{
    top_grb = new QGroupBox(/*tr("Top widgets panel")*/);
    current_screen_lbl = new QLabel("Отчеты");                //надпись с модулем программы
    current_screen_lbl->setAlignment(Qt::AlignCenter);
    //top_grb = new QGroupBox(tr("Top widgets panel"));         //лэйбл с именем программы
    topLayout->addWidget(current_screen_lbl);                 //лэйбл с именем модуля
    top_grb->setLayout(topLayout);
    return top_grb;
}
QGroupBox *Reports_screen::createMidGroup()
{
    mid_grb = new QGroupBox(/*tr("Mid widgets panel")*/);
    //создаем календарь и сразу же определяем минимальную и максимальную выделенную дату
    cw = new Calendarwidget();
    connect(cw,SIGNAL(selectionChanged()),this,SLOT(UpdateMinMaxDates()));//подключаем слот, коотрый обновит минимальную и максимальную выбранную дату по клику пользователя на датах календарика
    this->SetMinSelectedDate(cw->minSelectedDate());
    this->SetMaxSelectedDate(cw->maxSelectedDate());
    midLayout->addWidget(cw);
    midLayout->addWidget(apply_pb);
    mid_grb->setLayout(midLayout);
    return mid_grb;
}
QGroupBox *Reports_screen::createDownGroup()
{
    down_grb = new QGroupBox(/*tr("Down widgets panel")*/);
    print_pb = new QPushButton("Печать отчетов");
    back_pb = new QPushButton("К мониторингу");
    savef_pb = new QPushButton("Сохранить в файл");
    downLayout->addWidget(print_pb);
    downLayout->addWidget(back_pb);
    downLayout->addWidget(savef_pb);
    down_grb->setLayout(downLayout);
    return down_grb;
}

//----по кнопке "к мониторингу"
void Reports_screen::on_Btn_Back_Clicked()
{

    this->close();
    cw->setVisible(true);
    apply_pb->setVisible(true);
    print_pb->setEnabled(false);
    back_pb->setEnabled(false);
    savef_pb->setEnabled(false);

    for (int i = 0; i<config->GetSensorCount();++i)
    {
            delete tbl_name[i];
            delete report_tbls[i];
            delete model[i];
    }

    tbl_name.clear();
    report_tbls.clear();
    model.clear();
    item_temperature.clear();
    item_datatime.clear();

    emit ShowPlottersScreen();
}
//---по кнопке "Печать"------
void Reports_screen::on_PrintBtn_clicked()
{
    QString msg = "Print method will be here";
    QMessageBox::information(0, "Debug: " , msg);
}
//-----по кнопке "Применить даты"------
void Reports_screen::on_ApplyBtn_clicked()
{
    QString msg = "Введенная Вами дата \n";
    bool warn = false;
 // сравнить дату, которую выбрал пользователь с датой, которая есть в результатах измерений. Если выбранная дата стоит раньше, чем есть измерения - выдать сообщение
    if(this->GetMinSelectedDate()<this->GetMinMeasuredDate())//для старшей даты
    {
        warn = true;
        msg.append("выходит за нижний предел диапазона измерений по дате \n ");
    }
    if (this->GetMaxSelectedDate()>this->GetMaxMeasuredDate())//для младшей даты
    {
        warn = true;
        msg.append("выходит за верхний предел диапазона измерений по дате \n ");
    }
    if (warn)
    {
        QMessageBox::information(0, "Внимание: " , msg);
        warn = false;
    }
    //--------элементы интерфейса------------------
    cw->setVisible(false);
    apply_pb->setVisible(false);
    print_pb->setEnabled(true);
    back_pb->setEnabled(true);
    savef_pb->setEnabled(true);

    for (int i = 0; i<config->GetSensorCount();i++)
    {
        tbl_name[i]->setVisible(true);
        report_tbls[i]->setVisible(true);
    }
}
//------------по кнопке "сохранить в файл"-------------
void Reports_screen::on_SaveF_Btn_clicked()
{
QString fpath;
QString fname = "reports.xls";
if(!QDir("ApplicationReports").exists())
{
    QDir().mkdir("ApplicationReports");
}
fpath = QDir().absoluteFilePath("ApplicationReports").append("/").append(fname);
qDebug()<<"path to file is"<<fpath;
QFile mFile(fpath);
mFile.open(QIODevice::WriteOnly);
qDebug()<<"file opened";
//--------------------------------парсинг отчетов--------------------------------------------
QTextStream ts( &mFile );
QStringList hlist;  //хранить заголовки таблицы

//-------------------------------разметка таблицы в excel.
    QString str = "timepoint:";

//    //-------горизонтальные заголовки
    for(int c = 0; c < report_tbls[0]->horizontalHeader()->count(); ++c)
    {
        hlist.append("\t" + str + report_tbls[0]->model()->data(report_tbls[0]->model()->index(0,c),Qt::DisplayRole).toString() + "\t\t");
    }
    ts << hlist.join(" ") + "\n";

    //------наполнение данными
    for (int i = 0; i<config->GetSensorCount(); ++i)
    {
        strList << QStringList();   //персональные коллекции замеров. Под каждый датчик

        for(int c = 0; c < report_tbls[i]->horizontalHeader()->count(); ++c)
        {
            if(c==0)
            {
                strList[i].append("sensor#" + QString::number(i));
                strList[i].append("\t" + report_tbls[i]->model()->data(report_tbls[i]->model()->index(1,c),Qt::DisplayRole).toString() + "\t\t");
            }
            else
            {
            strList[i].append("\t" + report_tbls[i]->model()->data(report_tbls[i]->model()->index(1,c),Qt::DisplayRole).toString() + "\t\t");
            }
        }
        ts << strList[i].join(" ") + "\n";
    }
    mFile.close();
    //-----очистка коллекций по закрытию файла
    for (int i = 0; i<config->GetSensorCount(); ++i)
    {
        strList[i].clear();
        hlist.clear();
    }
}

void Reports_screen::SetTblsData(QVector<QVector<double> *> sensors, QVector<QVector<QDateTime> *> timepoint)
{
QDateTime min;
QDateTime max;
QDate min_d;
QDate max_d;
qDebug()<<"SetTblData";
//--взять минимальную дату из отчетов и запомнить ее, чтобы затем сравнить с минимальной датой, которую выбрал пользователь
    if(!(timepoint[0]->empty()))//датчики опрашиваются синхронно, поэтому проверять можно только 0-коллекцию
    {
        //qDebug()<<"timepoint 0 not empty";
        min = *std::min_element(timepoint[0]->begin(),timepoint[0]->end());//найти самую раннюю из всех временных меток. Можно ориентироваться по 0 коллекции, тк. все они заполняются синхронно
        min_d = min.date();                                                 //взять из нее только дату, отбросить время
        this->SetMinMeasuredDate(min_d);                                    //запомнить, чтобы потом сравнить
        max = *std::max_element(timepoint[0]->begin(),timepoint[0]->end());//найти самую позднюю из всех временых отметок
        max_d = max.date();                                                 //взять из нее дату, отбросить время
        this->SetMaxMeasuredDate(max_d);                                    //запомнить, чтобы потом сравнить
    }
    //по количеству датчиков выполнить:
    QString str1, str2;
    for (int i = 0; i<config->GetSensorCount();i++)
    {

    //-----расчитываем
    int tbl_len = sensors[i]->size();       //длина таблицы с отчетами
    static int posX = 0;                           //координаты размещения на табличном слое
    static int posY = 0;
    //----выделяем виджеты---
    localLayout<<new QVBoxLayout;                               //новый локальный слой, на который добавится таблица с отчетом + ее имя
    tbl_name<< new QLabel("Table ID = " + QString::number(i));  //надписи с именами таблиц
    report_tbls <<new QTableView();                             //новая таблица с отчетами
    model << new QStandardItemModel(2,tbl_len,this);            //модели(2 - количество строк)

    item_temperature << new QStandardItem(tbl_len);
    item_datatime << new QStandardItem(tbl_len);
    localLayout[i]->addWidget(tbl_name[i]);
    localLayout[i]->addWidget(report_tbls[i]);
    //наполняем данными
    for(int j = 0; j< tbl_len; j++)
    {
        //выводятся значения, попадающие в интервал дат, которые указал пользователь
        if((timepoint[i]->at(j).date()>=this->GetMinSelectedDate())&&(timepoint[i]->at(j).date()<=this->GetMaxSelectedDate()))
        {
        //преобразуем в строки
        str1 = QString::number(sensors[i]->at(j));
        str2 = (timepoint[i]->at(j)).toString("d.M.yy.hh:mm:ss");

        //создаем ячейки
        item_temperature[i] = new QStandardItem(QString(str1));
        item_datatime[i] = new QStandardItem(QString(str2));
        //ставим ячейки в модель
        model[i]->setItem(0,j,item_datatime[i]);    //0-строка - дата/время
        model[i]->setItem(1,j,item_temperature[i]); //1-строка - результат измерения
        }
    }
    report_tbls[i]->setModel(model[i]);
    //-----размещаем
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
    //-----скрываем до нажатия кнопки "применить даты"------
    tbl_name[i]->setVisible(false);
    report_tbls[i]->setVisible(false);
    }
}

void Reports_screen::UpdateMinMaxDates()
{
    this->SetMinSelectedDate(cw->minSelectedDate());
    this->SetMaxSelectedDate(cw->maxSelectedDate());
}


//-------деструктор---------
Reports_screen::~Reports_screen()
{

}
