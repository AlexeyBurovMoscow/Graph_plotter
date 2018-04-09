
#ifndef REPORTS_SCREEN_H
#define REPORTS_SCREEN_H
#include <QtWidgets>
#include <calendarwidget.h>
#include <configurator.h>


class Reports_screen:public QWidget
{
    Q_OBJECT
public:
    explicit Reports_screen(Configurator *configurator, QWidget *parent = 0);
    ~Reports_screen();
private:
    //-----механика-------------
    Configurator* config;
    QDate min_selected_date;
    QDate max_selected_date;
    QDate min_measured_date;
    QDate max_measured_date;
    QVector<QStringList> strList;             //коллекция StringList, куда складываются заголовки отчетов. По количеству датчиков
    //-----смежные классы-------
    Calendarwidget *cw;
    //-------визуальные компоненты
    //-------виджеты, количество которых не зависит от количества датчиков
    QLabel * current_screen_lbl;
    QPushButton * print_pb;
    QPushButton * back_pb;
    QPushButton * apply_pb;
    QPushButton * savef_pb;
    //-------виджеты, количество которых зависит от количества датчиков           
    QVector<QLabel*>tbl_name;                  //коллекция имен отчетов
    QVector<QTableView*>report_tbls;           //коллекция отчетов
    QVector<QStandardItemModel*> model;        //коллекция моделей для оформления отчетов
    QVector<QStandardItem*> item_temperature;  //строка отчетов с температурами
    QVector<QStandardItem*> item_datatime;     //строка отчетов с временными метками
    QVector<QStandardItem*> secondRow;         //вторая строка отчетов
    QVector<QVBoxLayout*> localLayout;         //коллекция слоев, на который будут помещены виджеты с отчетами
    //--------слои-----------------------------------
    QVBoxLayout * mainlayout;
    QVBoxLayout* topLayout;
    //QVBoxLayout* midLayout;
    QGridLayout * midLayout;
    QHBoxLayout * downLayout;
    //---------панели----------
    QGroupBox * top_grb;            //панели, где сгруппированы элементы управления
    QGroupBox * mid_grb;
    QGroupBox * down_grb;
    //------методы----------------
    //методы, которые создают группы виджетов в окне конфигуратора
    QGroupBox *createTopGroup();
    QGroupBox *createMidGroup();
    QGroupBox *createDownGroup();
    //-------методы доступа--------
    void SetMinSelectedDate(QDate min_date);//к выделенным пользователем в календарике
    void SetMaxSelectedDate(QDate max_date);
    QDate GetMinSelectedDate();
    QDate GetMaxSelectedDate();             //к датам в отчете
    void SetMinMeasuredDate(QDate min_date);
    void SetMaxMeasuredDate(QDate max_date);
    QDate GetMinMeasuredDate();
    QDate GetMaxMeasuredDate();
signals:
    void ShowPlottersScreen();


private slots:
    void on_Btn_Back_Clicked();
    void on_PrintBtn_clicked();
    void on_ApplyBtn_clicked();
    void on_SaveF_Btn_clicked();
    void SetTblsData(QVector<QVector<double>*> sensors, QVector<QVector<QDateTime>*> timepoint);
    void UpdateMinMaxDates();   //обновить значение минимальной даты от календаря
};

#endif // REPORTS_SCREEN_H
