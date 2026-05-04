#include "calendarscreen.h"
#include "ui_calendarscreen.h"

CalendarScreen::CalendarScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::calendarscreen) {
    ui->setupUi(this);
    syncUi();
}




void CalendarScreen::syncUi() {
    // здесь можно добавить визу подсветки дней, где есть данные
}

void CalendarScreen::on_calendarWidget_clicked(const QDate &date) {
    emit dateSelected(date);
}
