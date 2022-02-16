/**
* @FileName             ctrls.pri
* @Brief                摘要
* @Version              1.0.0
* @Current Maintainter  修改者
* @Update Date          2019-04-18
* @Author               luteng
* @email                luteng1230@163.com
* @Create Date          2019-04-18
* @
*/
#include "linewidget.h"
#include <QPaintEvent>
#include <QPainter>
#include <QColor>

LineWidget::LineWidget(LineStyle style, QWidget *parent) : QWidget(parent)
{
    m_lineColor = QColor(55, 55, 55);
    m_lineStyle = style;
}

LineWidget::~LineWidget()
{

}

LineStyle LineWidget::getLineStyle() const
{
    return m_lineStyle;
}

void LineWidget::setLineStyle(const LineStyle style)
{
    m_lineStyle = style;
}

void LineWidget::setLineColor(const QColor color)
{
    if (m_lineColor!= color)
    {
        m_lineColor = color;
        update();
    }
}

QColor LineWidget::getLineColor() const
{
    return m_lineColor;
}

void LineWidget::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
//    pen.setColor(m_lineColor);
//    pen.setWidth(2);
    paint.setPen(Qt::NoPen);
    paint.fillRect(event->rect(), m_lineColor);
//    switch (m_lineStyle)
//    {
//        case Line_H:
//            paint.drawLine(event->rect().left(), event->rect().top(), event->rect().right(), event->rect().top());
//            break;
//        case Line_V:
//            paint.drawLine(event->rect().left(), event->rect().top(), event->rect().left(), event->rect().bottom());
//        default:
//            break;
//    }
//    paint.end();
}
