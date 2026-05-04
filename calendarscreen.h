#ifndef CALENDARSCREEN_H
#define CALENDARSCREEN_H

#include <QWidget>
#include <QDate>

QT_BEGIN_NAMESPACE
namespace Ui {
class calendarscreen;
}
QT_END_NAMESPACE

class CalendarScreen : public QWidget {
    Q_OBJECT

public:
    explicit CalendarScreen(QWidget *parent = nullptr);

signals:
    void dateSelected(const QDate &date);

private slots:
    void on_calendarWidget_clicked(const QDate &date);

private:
    Ui::calendarscreen *ui;
    void syncUi();
};

#endif // CALENDARSCREEN_H
