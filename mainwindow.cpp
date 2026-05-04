#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "waterscreen.h"
#include "calendarscreen.h"

#include <QStackedWidget>
#include <QToolBar>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setupStackedWidget();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupStackedWidget() {
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
            [stack]() { stack->setCurrentIndex(0); });
}

int MainWindow::waterForDate(const QDate &date) const {
    return m_waterData.value(date, 0);
}



void MainWindow::setWaterForDate(const QDate &date, int ml) {
    m_waterData[date] = ml;
}
