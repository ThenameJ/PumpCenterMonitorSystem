/**
* @FileName             alarminfopage.h
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-11-09 10:13:59
* @Author               zhoumingjie
* @email
* @Create Date          2021-11-09 10:13:59
* @
*/
#ifndef ALARMINFOPAGE_H
#define ALARMINFOPAGE_H

#include <QWidget>
#include "basemenupage.h"
#include "onealarminfo.h"
#include <QScrollArea>
#include <QListWidget>
#include <QScrollBar>
#include <QVector>
#include <Qtimer>

class SuspendedScrollBar;
class AlarmInfoPage : public BaseMenuPage
{
    Q_OBJECT
public:
    explicit AlarmInfoPage(QWidget *parent = nullptr);

    virtual ~AlarmInfoPage();

    void initWidget();

    void afterWidget();

    void clearWidget(QLayout *layout);

    void setDeviceNum(const int &num);

private:
    void clearMap(QMap<int, OneAlarmInfo*> &map);

protected:
    void paintEvent(QPaintEvent *event);

    void resizeEvent(QResizeEvent *event);

    void enterEvent(QEvent *event);

    void leaveEvent(QEvent *event);

signals:

public slots:
    void onSlotSetNum(int num);

    void onSlotSetSelfNum(int row, int line);

    void sltValueChangeWidget(int value);

    void onSlotIdAndColor(int id, QColor color, int timeLeft);

    void onSlotSortSignal();

    void onSlotSetConnectNum(const int &num);

    void onTimeOut();

private:
    int m_deviceNum = 0;

    QVBoxLayout *vlayout = Q_NULLPTR;

    QScrollArea *scroll = Q_NULLPTR;

    SuspendedScrollBar *m_pVertScrollBar = Q_NULLPTR;

//    QVector<int> vector;

    QMap<int,OneAlarmInfo*> m_map;

    QTimer *m_timer;

    int m_count = 0;

};



class SuspendedScrollBar : public QScrollBar
{
    Q_OBJECT
public:
    explicit SuspendedScrollBar(Qt::Orientation t , QWidget * parent = 0);
    ~SuspendedScrollBar(){}
public slots:
    void sltValueChangeScrollBar(int);//当使用该组件的控件的滚动条发出valueChanged信号时，该信号被触发
    void sltRangeChanged(int min,int max);//当使用该组件的控件的滚动条发出rangeChanged信号时，该信号被触发
    void sltrangechangedExtra(int min,int max);//当使用该组件的控件的滚动条发出rangeChanged信号时，该信号被触发


};


#endif // ALARMINFOPAGE_H
