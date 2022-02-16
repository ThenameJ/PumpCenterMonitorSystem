/**
* @FileName             ctrls.pri
* @Brief                线控件 为了优化界面效果，有时需要在控件之间留一条间隔，用线控件代替
* @Version              1.0.0
* @Current Maintainter  修改者
* @Update Date          2019-04-18
* @Author               luteng
* @email                luteng1230@163.com
* @Create Date          2019-04-18
* @
*/
#ifndef LINEWIDGET_H
#define LINEWIDGET_H

#include <QWidget>

enum LineStyle
{
    Line_V,         //纵向
    Line_H,         //横向
    LINE_Max
};

class QColor;
class LineWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LineWidget(LineStyle style = Line_V, QWidget *parent = nullptr);
    virtual ~LineWidget();

    LineStyle getLineStyle() const;

    void setLineStyle(const LineStyle style);

    void setLineColor(const QColor color);

    QColor getLineColor() const;
protected:
    virtual void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
private:
    LineStyle m_lineStyle;
    QColor    m_lineColor;
};

#endif // LINEWIDGET_H
