#ifndef PASSWORD_SCREEN_H
#define PASSWORD_SCREEN_H
#include <QtWidgets>

class Password_screen:public QWidget
{
    Q_OBJECT
public:
    explicit Password_screen(QWidget *parent = 0);
    ~Password_screen();
private:
    //-------визуальные компоненты
    QLabel* password_lbl;             //метка "серийный номер"
    QLineEdit* password_le;           //LineEdit для серийного номера
    QPushButton* confirm_password_pb;//кнопка "подтвердить пароль"
signals:
    void ShowSettingsScreen();
private slots:
    void on_Btn_Confirm_clicked();
};

#endif // PASSWORD_SCREEN_H
