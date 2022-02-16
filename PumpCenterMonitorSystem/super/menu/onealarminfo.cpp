/**
* @FileName             onealarminfo.cpp
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-11-09 10:13:13
* @Author               zhoumingjie
* @email
* @Create Date          2021-11-09 10:13:13
* @
*/
#include "onealarminfo.h"
#include "linewidget.h"
#include "uimanager.h"
#include <QDebug>

OneAlarmInfo::OneAlarmInfo(QWidget *parent) : QWidget(parent)
{
    alarmColor = QColor(200,200,200);

    m_roomInfoLabel = new QLabel(tr("房间"),this);
    m_alarmInfoLabel = new QLabel(tr("报警信息"),this);
    //Info1->setStyleSheet("background-color: rgb(250, 0, 0);");
    m_roomInfoLabel->setAlignment(Qt::AlignCenter);
    m_alarmInfoLabel->setAlignment(Qt::AlignCenter);
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(m_roomInfoLabel);
    hlayout->addWidget(m_alarmInfoLabel);
    hlayout->setSpacing(0);
    hlayout->setMargin(0);
    hlayout->setStretchFactor(m_roomInfoLabel,1);
    hlayout->setStretchFactor(m_alarmInfoLabel,2);

    setLayout(hlayout);

    connect(this,SIGNAL(checkPatientInfo(int)),uimanager,SIGNAL(checkPatientInfo(int)));

    connect(this,SIGNAL(updateUi()),uimanager,SIGNAL(updateUi()));
}

OneAlarmInfo::~OneAlarmInfo()
{

}

void OneAlarmInfo::createLineWidget()
{
    int left = rect().left();
    int top = rect().top();
    int height = rect().height();
    left += 122;
    LineWidget *line = new LineWidget(Line_V, this);
    line->setLineColor(QColor(180,180,180));
    line->setGeometry(left, top, 1, height);
}

void OneAlarmInfo::setColor(const QColor &color)
{
    if(alarmColor != color)
    {
        alarmColor = color;
        update();
    }
}

QColor OneAlarmInfo::getColor()
{
    return alarmColor;
}

void OneAlarmInfo::setRoomInfo(const QString &roomInfo)
{
    if(m_roomInfo != roomInfo)
    {
        m_roomInfo = roomInfo;
        m_roomInfoLabel->setText(m_roomInfo);
        update();
    }
}

QString OneAlarmInfo::getRoomInfo()
{
    return m_roomInfo;
}

void OneAlarmInfo::setTimeLeft(const int &timeLeft)
{
    if(m_timeLeft != timeLeft)
    {
        m_timeLeft = timeLeft;
        update();
    }
}

int OneAlarmInfo::getTimeLeft()
{
    return this->m_timeLeft;
}

void OneAlarmInfo::setDeviceId(int deviceId)
{
    if(m_deviceId != deviceId)
    {
        m_deviceId = deviceId;
        update();
    }
}

void OneAlarmInfo::setAlarmInfo(const QString &alarmInfo)
{
    if(m_alarmInfoLabel->text() != alarmInfo)
    {
        m_alarmInfoLabel->setText(alarmInfo);
        update();
    }
}

void OneAlarmInfo::paintEvent(QPaintEvent *event)
{
    //绿色 0,128,0
    //蓝色 50,100,200
    //橙色 255,114,86
    //红色 220,0,27
    Q_UNUSED(event);
    QPalette pe;
    pe.setColor(QPalette::Background, alarmColor);
    setAutoFillBackground(true);
    setPalette(pe);
    QPainter painter(this);
    QPen pen;
    pen.setColor(QColor(200,200,200));
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawRect(rect());
    if(alarmColor == QColor(0,128,0))
    {
        setAlarmInfo(tr("输液正常"));
    }
    else if(alarmColor == QColor(50,100,200))
    {
        setAlarmInfo(tr("低级警告"));
    }
    else if(alarmColor == QColor(255,114,86))
    {
        setAlarmInfo(tr("中级警告"));
    }
    else if(alarmColor == QColor(220,1,27))
    {
        setAlarmInfo(tr("高级警告"));
    }
    else
    {
        setAlarmInfo(tr("紧急处理"));
    }
}

void OneAlarmInfo::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    createLineWidget();
}

void OneAlarmInfo::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(event->button() == Qt::LeftButton)
    {
        m_mousePressed = rect().contains(event->pos());
    }
    event->accept();
}

void OneAlarmInfo::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if (m_mousePressed && rect().contains(event->pos()))
    {
        uimanager->m_fousId = this->m_deviceId;
        emit updateUi();
        m_mousePressed = false;
        emit checkPatientInfo(this->m_deviceId);
    }
    event->accept();
}
