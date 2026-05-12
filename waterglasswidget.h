#ifndef WATERGLASSWIDGET_H
#define WATERGLASSWIDGET_H

#include <QWidget>

class WaterGlassWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WaterGlassWidget(QWidget *parent = nullptr);

    void setDailyNorm(int ml);
    void setWaterTaken(int ml);

Q_SIGNALS:
    void valueChanged(int, int percent);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_dailyNorm = 2000;
    int m_waterTaken = 0;

    QRect glassRect() const;   // рабочий прямоугольник “стакана”
};

#endif // WATERGLASSWIDGET_H
