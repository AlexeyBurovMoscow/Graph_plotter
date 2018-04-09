
#ifndef SETTINGS_SCREEN_H
#define SETTINGS_SCREEN_H
#include <QtWidgets>
#include <configurator.h>
#include "password_screen.h"
#include "plotters_screen.h"

class Settings_screen:public QWidget
{
    Q_OBJECT
public:
    explicit Settings_screen(QWidget *parent = 0);
    ~Settings_screen();
private:
    //-----смежные окна---------
    Password_screen *pswd_screen;
    Plotters_screen *plts_screen;
    //-----смежные классы-------
    Configurator *configurator;             //указатель на конфигуратор
    //-----визуальные компоненты-
    //--------слои-----------------------------------
    QVBoxLayout* topLayout;
    QVBoxLayout* leftlayout;
    QVBoxLayout* rightlayout;
    QVBoxLayout* downlayout;
    QVBoxLayout* mainlayout;
    QGridLayout* gridlayout;
    //--------сначала все поля ----------------------
    QFrame *frame;                  //рамка
    QLabel *program_name_lbl;       //надпись с именем программы
    QLabel *program_module_lbl;     //надпись с модулем программы
    QLabel* discret_lbl;            //метка "дискретизация"

    QSlider* discret_sl;            //слайдер для регулирования частоты опроса датчиков
    QLabel* fdiscret_lbl;           //лэйб на котором меняется надпись по регулировке частоты опроса

    QLabel* sensor_cntr_lbl;        //метка "количество сенсоров"
    QSpinBox* sensor_cnt_spin;      //спин-бокс для ввода количества сенсоров

    QPushButton* extended_conf_pb;  //кнопка для расширенного конфигурирования
    QPushButton* apply_settings_pb;  //кнопка "применить настройки"

    QLabel *min_temp_lbl;           //метки максимальная и минимальная температура
    QLabel *max_temp_lbl;

    QDoubleSpinBox* min_temp_dblspin;//дабл-спинбоксы для минимальной и макс. температур
    QDoubleSpinBox* max_temp_dblspin;

    QGroupBox * top_grb;            //панели, где сгруппированы элементы управления
    QGroupBox * down_grb;
    QGroupBox * left_grb;
    QGroupBox * right_grb;
    //-------потом запароленные поля--------------------
    QLabel* serial_lbl;             //метка "серийный номер"
    QLineEdit* serial_le;           //LineEdit для серийного номера
    QLabel* container_num_lbl;      //метка "номер контейнера"
    QLineEdit* container_num_le;    //Line Edit для номера контейнера

    //методы, которые создают группы виджетов в окне конфигуратора
    QGroupBox *createTopGroup();
    QGroupBox *createLeftGroup();
    QGroupBox *createRightGroup();
    QGroupBox *createDownGroup();
signals:

private slots:
    void on_Btn_Pswd_clicked();         //метод вызывающий окно пароля
    void on_Btn_Next_clicked();         //метод, вызывающий окно с построителем графиков
    void ShowExtendedConfigurator();    //метод, вызывающий расширенное окно настроек
    void on_Slider_Changed(int value);  //метод, реагирующий на изменение положение слайдера
};

#endif // SETTINGS_SCREEN_H
