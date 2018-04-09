#include <QApplication>
#include <settings_screen.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Settings_screen ss;
    ss.show();
    return a.exec();
}
