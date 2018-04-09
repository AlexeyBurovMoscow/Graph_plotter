#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H


#include <QCalendarWidget>
#include <QTableView>
#include <QObject>
#include <QtGui>


class Calendarwidget : public QCalendarWidget
{
    Q_OBJECT
public:
    Calendarwidget(QWidget *parent = 0);
    bool eventFilter(QObject *obj, QEvent *event);
    void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const;

    QDate minSelectedDate() const { return minDate; }
    QDate maxSelectedDate() const { return maxDate; }

public slots:
    void setSelectedDate();

private:
    Qt::KeyboardModifiers modifier;
    QDate minDate;
    QDate maxDate;
};

#endif // CALENDARWIDGET_H
