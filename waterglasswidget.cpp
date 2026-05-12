#include "waterglasswidget.h"
#include <QPainter>
#include <QFontMetrics>

WaterGlassWidget::WaterGlassWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(60, 150);   // стакан более высокий, чем широкий
}

void WaterGlassWidget::setDailyNorm(int ml)
{
    if (m_dailyNorm != ml) {
        m_dailyNorm = qMax(1, ml);  // чтобы не было / 0
        update();
    }
}

void WaterGlassWidget::setWaterTaken(int ml)
{
    if (m_waterTaken != ml) {
        m_waterTaken = qMax(0, ml);
        int percent = 0;
        if (m_dailyNorm > 0)
            percent = qBound(0, (m_waterTaken * 100) / m_dailyNorm, 100);
        emit valueChanged(m_waterTaken, percent);
        update();
    }
}

// Возвращает прямоугольник “стакана” с небольшими отступами
QRect WaterGlassWidget::glassRect() const
{
    QRect r = rect();
    int pad = 6;
    return r.adjusted(pad, pad, -pad, -pad);
}

void WaterGlassWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QRect r = glassRect();

    // Цвета
    QColor colorGlass = QColor("#d0e0f0");      // светлый фон стакана
    QColor colorWater = QColor("#0078D7");      // “вода”

    // Рисуем контур стакана
    p.setPen(QColor("#8090a0"));
    p.setBrush(colorGlass);
    p.drawRoundedRect(r, 10, 10);

    // Вычисляем уровень воды
    double ratio = 1.0;
    if (m_dailyNorm > 0)
        ratio = static_cast<double>(m_waterTaken) / m_dailyNorm;

    int hFull = static_cast<int>(r.height() * ratio);
    QRect rWater(r.left(), r.bottom() - hFull + 1, r.width(), hFull);
    p.setBrush(colorWater);
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(rWater, 10, 10);

    // Текст поверх: "400 / 2000 мл"

    QString text = QString::number(m_waterTaken) + " / " +
                   QString::number(m_dailyNorm) + " мл";
    QFontMetrics fm = p.fontMetrics();
    int textWidth = fm.horizontalAdvance(text);
    int textHeight = fm.height();
    int textX = r.left() + (r.width() - textWidth) / 2;
    int textY = r.center().y() + textHeight / 2;

    p.setPen(Qt::black);
    p.drawText(textX, textY, text);
}
