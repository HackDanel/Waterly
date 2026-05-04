#include "waterscreen.h"
#include "ui_waterscreen.h"   // сгенерировано из waterscreen.ui
#include "mainwindow.h"

WaterScreen::WaterScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::waterscreen)
{
    ui->setupUi(this);
    m_currentDate = QDate::currentDate();
    syncUi();
}

WaterScreen::~WaterScreen() {
    delete ui;
}

void WaterScreen::setCurrentDate(const QDate &date) {
    m_currentDate = date;
    syncUi();
}

void WaterScreen::syncUi() {
    MainWindow *mw = qobject_cast<MainWindow *>(window());   // window() — это метод QWidget
    if (!mw) return;

    m_currentWater = mw->waterForDate(m_currentDate);

    ui->spinNorm->setValue(m_dailyNorm);
    ui->spinWater->setValue(m_currentWater);
}

void WaterScreen::on_pushButtonAdd_clicked() {
    m_currentWater += 100;
    MainWindow *mw = qobject_cast<MainWindow *>(window());
    if (mw)
        mw->setWaterForDate(m_currentDate, m_currentWater);
    syncUi();
}

void WaterScreen::on_pushButtonSub_clicked() {
    m_currentWater = qMax(0, m_currentWater - 100);
    MainWindow *mw = qobject_cast<MainWindow *>(window());
    if (mw)
        mw->setWaterForDate(m_currentDate, m_currentWater);
    syncUi();
}

void WaterScreen::on_pushButtonSetDaily_clicked() {
    m_dailyNorm = ui->spinNorm->value();
}
