#ifndef WATERSCREEN_H
#define WATERSCREEN_H

#include <QWidget>
#include <QDate>

QT_BEGIN_NAMESPACE
namespace Ui {
class waterscreen;   // в нижнем регистре
}
QT_END_NAMESPACE

class MainWindow;

class WaterScreen : public QWidget {
    Q_OBJECT

public:
    explicit WaterScreen(QWidget *parent = nullptr);
    ~WaterScreen();

public slots:
    void setCurrentDate(const QDate &date);

private slots:
    void on_pushButtonAdd_clicked();
    void on_pushButtonSub_clicked();
    void on_pushButtonSetDaily_clicked();

private:
    Ui::waterscreen *ui;
    QDate m_currentDate;
    int m_dailyNorm = 2000;
    int m_currentWater = 0;

    void syncUi();
};

#endif // WATERSCREEN_H
