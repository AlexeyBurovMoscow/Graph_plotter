#include "calendarwidget.h"

Calendarwidget::Calendarwidget(QWidget *parent) :
    QCalendarWidget(parent)
{
    QTableView *view = this->findChild<QTableView *>();
    view->viewport()->installEventFilter(this);
    view->installEventFilter(this);
    connect(this,SIGNAL(selectionChanged()),this,SLOT(setSelectedDate()));
    minDate = maxDate = QDate::currentDate();
}

void Calendarwidget::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
    if((date >= minDate && date <= maxDate) && date != selectedDate() )
    {
        painter->fillRect (rect, Qt::yellow);
        painter->drawText (rect, Qt::AlignCenter | Qt::AlignHCenter,
        QString::number(date.day ()));
        return;
    }
    QCalendarWidget::paintCell(painter,rect,date);
}

void Calendarwidget::setSelectedDate()
{
    QDate date = selectedDate();
    QString str1, str2;
    if( modifier & Qt::ShiftModifier )
    {
        minDate = qMin(minDate,date);
        str1 = minDate.toString("d.M.yy");
        maxDate = qMax(maxDate,date);
        str2 = maxDate.toString("d.M.yy");
    }
    else
        minDate = maxDate = date;
    updateCells();
}


bool Calendarwidget::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonRelease)
        modifier = 	static_cast<QMouseEvent*>(event)->modifiers();
    if(event->type() == QEvent::KeyPress)
        modifier = 	static_cast<QKeyEvent*>(event)->modifiers();
    return QCalendarWidget::eventFilter(obj, event);
}

