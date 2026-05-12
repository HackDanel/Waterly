#include "waterscreen.h"
#include "ui_waterscreen.h"
#include "mainwindow.h"
#include "waterglasswidget.h"

WaterScreen::WaterScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::waterscreen)
{
    ui->setupUi(this);

    m_currentDate = QDate::currentDate();
    m_glassWidget = ui->waterGlassWidget;

    syncUi();
}

WaterScreen::~WaterScreen()
{
    delete ui;
}


void WaterScreen::setCurrentDate(const QDate &date) {
    m_currentDate = date;
    syncUi();
}

int WaterScreen::computePercent() const
{
    if (m_dailyNorm == 0)
        return 0;
    return qBound(0, (m_currentWater * 100) / m_dailyNorm, 100);
}

void WaterScreen::syncUi()
{
    MainWindow *mw = qobject_cast<MainWindow *>(window());
    if (!mw) return;

    m_currentWater = mw->waterForDate(m_currentDate);

    ui->spinNorm->setValue(m_dailyNorm);
    ui->spinWater->setValue(m_currentWater);

    m_glassWidget->setDailyNorm(m_dailyNorm);
    m_glassWidget->setWaterTaken(m_currentWater);
}

void WaterScreen::on_pushButtonAdd_clicked()
{
    m_currentWater += 100;
    MainWindow *mw = qobject_cast<MainWindow *>(window());
    if (mw)
        mw->setWaterForDate(m_currentDate, m_currentWater);
    syncUi();
}

void WaterScreen::on_pushButtonSub_clicked()
{
    m_currentWater = qMax(0, m_currentWater - 100);
    MainWindow *mw = qobject_cast<MainWindow *>(window());
    if (mw)
        mw->setWaterForDate(m_currentDate, m_currentWater);
    syncUi();
}

void WaterScreen::on_pushButtonSetDaily_clicked()
{
    bool ok;
    int val = ui->spinNorm->text().toInt(&ok);
    if (ok && val >= 0)
        m_dailyNorm = val;
    else
        m_dailyNorm = 2000;

    syncUi();
}
