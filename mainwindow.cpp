#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "waterscreen.h"
#include "calendarscreen.h"

#include <QStackedWidget>
#include <QToolBar>
#include <QAction>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QMessageBox>
#include <QCloseEvent>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_trayIcon(new QSystemTrayIcon(this))
    , m_reminderTimer(new QTimer(this))
{
    ui->setupUi(this);
    setupStackedWidget();

    if (QSystemTrayIcon::isSystemTrayAvailable()) {
        m_trayIcon->setIcon(QIcon(":/icons/app.png"));
        m_trayIcon->setToolTip("Напоминание о воде");
        m_trayIcon->show();

        connect(m_trayIcon, &QSystemTrayIcon::activated,
                this, &MainWindow::onTrayActivated);
    } else {
        QMessageBox::warning(this, "Tray", "Системный трей недоступен.");
    }

    connect(m_reminderTimer, &QTimer::timeout,
            this, &MainWindow::showWaterReminder);

    m_reminderTimer->start(60 * 60 * 1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupStackedWidget()
{
    QStackedWidget *stack = new QStackedWidget(this);

    WaterScreen *waterWidget = new WaterScreen(this);
    CalendarScreen *calendarWidget = new CalendarScreen(this);

    stack->addWidget(waterWidget);
    stack->addWidget(calendarWidget);

    setCentralWidget(stack);
    stack->setCurrentIndex(0);

    QToolBar *toolbar = addToolBar("Main");
    QAction *actionCalendar = toolbar->addAction("Calendar");

    connect(actionCalendar, &QAction::triggered, [stack]() {
        stack->setCurrentIndex(1);
    });

    connect(calendarWidget, &CalendarScreen::dateSelected,
            waterWidget, &WaterScreen::setCurrentDate);

    connect(calendarWidget, &CalendarScreen::dateSelected,
            [stack]() {
                stack->setCurrentIndex(0);
            });
}

int MainWindow::waterForDate(const QDate &date) const
{
    return m_waterData.value(date, 0);
}

void MainWindow::setWaterForDate(const QDate &date, int ml)
{
    m_waterData[date] = ml;
}

void MainWindow::showWaterReminder()
{
    if (!QSystemTrayIcon::isSystemTrayAvailable())
        return;

    m_trayIcon->showMessage(
        "Напоминание",
        "Пора выпить воды",
        QSystemTrayIcon::Information,
        5000
        );
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (QSystemTrayIcon::isSystemTrayAvailable()) {
        hide();
        event->ignore();
        m_trayIcon->showMessage(
            "Напоминание",
            "Приложение свернуто в трей",
            QSystemTrayIcon::Information,
            3000
            );
    } else {
        event->accept();
    }
}

void MainWindow::onTrayActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger) {
        if (isHidden()) {
            showNormal();
            raise();
            activateWindow();
        } else {
            hide();
        }
    }
}
