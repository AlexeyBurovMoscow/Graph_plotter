
#include "password_screen.h"

Password_screen::Password_screen(QWidget *parent):QWidget(parent)
{
    //------визуальные компоненты
    QLabel* password_lbl = new QLabel("Введите пароль");             //метка "серийный номер"
    QLineEdit* password_le = new QLineEdit;                         //поле для ввода пароля
    QPushButton* confirm_password_pb = new QPushButton("Подтвердить");//кнопка "подтвердить пароль"
    QVBoxLayout* passwordlayout = new QVBoxLayout();
    this->setLayout(passwordlayout);
    passwordlayout->setMargin(10);
    passwordlayout->setSpacing(20);
    passwordlayout->addWidget(password_lbl);
    passwordlayout->addWidget(password_le);
    passwordlayout->addWidget(confirm_password_pb);
    //------слоты и сигналы----
    connect(confirm_password_pb,SIGNAL(clicked(bool)),SLOT(on_Btn_Confirm_clicked()));
    //------внешний вид--------
    setWindowTitle("Введите пароль");
}

void Password_screen::on_Btn_Confirm_clicked()
{
    this->close();
    emit ShowSettingsScreen();
}

//------деструктор-----------------
Password_screen::~Password_screen()
{

}
