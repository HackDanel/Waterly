#include "calendarscreen.h"
#include "ui_calendarscreen.h"

CalendarScreen::CalendarScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::calendarscreen) {
    ui->setupUi(this);
    syncUi();
}




void CalendarScreen::syncUi() {

}

void CalendarScreen::on_calendarWidget_clicked(const QDate &date) {
    emit dateSelected(date);
}
