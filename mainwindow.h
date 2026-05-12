#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QDate>
#include <QSystemTrayIcon>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class WaterScreen;
class CalendarScreen;

class MainWindow : public QMainWindow {
    Q_OBJECT

private slots:
    void showWaterReminder();
    void onTrayActivated(QSystemTrayIcon::ActivationReason reason);

protected:
    void closeEvent(QCloseEvent *event) override;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int waterForDate(const QDate &date) const;
    void setWaterForDate(const QDate &date, int ml);

signals:
    void currentDateChanged(const QDate &date);

private:
    Ui::MainWindow *ui;
    QMap<QDate, int> m_waterData;
    QSystemTrayIcon *m_trayIcon;
    QTimer *m_reminderTimer;

    void setupStackedWidget();
};


#endif // MAINWINDOW_H
