/**
* @FileName             pumpstate.cpp
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-09-14 14:47:47
* @Author               zhoumingjie
* @email
* @Create Date          2021-09-14 14:47:47
* @
*/
#include "pumpstate.h"
#include "qpainter.h"
#include <QDebug>
#include "uimanager.h"


//绿色 0,128,0
//蓝色 50,100,200
//橙色 255,114,86
//红色 220,0,27

PumpState::PumpState(QWidget *parent)
    : QWidget(parent)
{
//    setMouseTracking(true);
    setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    //setAttribute(Qt::WA_TransparentForMouseEvents,true);
    setFocusPolicy(Qt::ClickFocus);
    setMinimumSize(280,170);
    //setMaximumSize();
    m_unit = 0;
    m_color = QColor(0,128,0);
    m_isOver = false;

    m_timer = new QTimer(this);
    m_timer->setTimerType(Qt::PreciseTimer);//高精度定时器 占用CPU资源
    m_timer->setInterval(1000);//每一秒触发一个timeout()信号
    connect(m_timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
    m_timer->start();

    m_alarmTimer = new QTimer(this);
    m_alarmTimer->setTimerType(Qt::PreciseTimer);//高精度定时器 占用CPU资源
    m_alarmTimer->setInterval(500);//每一秒触发一个timeout()信号
    connect(m_alarmTimer,SIGNAL(timeout()),this,SLOT(onAlarmTimeOut()));

    connect(this,SIGNAL(sendOpenRightWin()),uimanager,SIGNAL(sendOpenRightWin()));
    connect(this,SIGNAL(openConfig(int)),uimanager,SIGNAL(sendOpenConfig(int)));
    connect(this,SIGNAL(checkPatientInfo(int)),uimanager,SIGNAL(checkPatientInfo(int)));
    connect(this,SIGNAL(sendIdAndColor(int,QColor,int)),uimanager,SIGNAL(sendIdAndColor(int,QColor,int)));
    connect(this,SIGNAL(sendSortSignal()),uimanager,SIGNAL(sendSortSignal()));
    connect(this,SIGNAL(sendOverSignal()),uimanager,SIGNAL(sendOverSignal()));
    connect(this,SIGNAL(sendOpenAlarm(int, bool)),uimanager,SLOT(onSlotAlarm(int, bool)));
    connect(uimanager,SIGNAL(updateUi()),this,SLOT(onSlotUpdate()));

}


PumpState::~PumpState()
{
    if(m_timer)
    {
        m_timer->stop();
        delete m_timer;
    }
    if(m_alarmTimer)
    {
        m_alarmTimer->stop();
        delete m_alarmTimer;
    }
}

void PumpState::onTimeOut()
{
    ++m_unit;
    //qDebug() << m_unit;
    if((m_randn*60-m_unit)/60 <= 3)
    {
        m_color = QColor(220,1,27);
    }
    else if((m_randn*60-m_unit)/60 > 3 && (m_randn*60-m_unit)/60 <= 7 )
    {
        m_color = QColor(255,114,86);
    }
    else if((m_randn*60-m_unit)/60 > 7 && (m_randn*60-m_unit)/60 <= 15)
    {
        m_color = QColor(50,100,200);
    }
    else
    {
        m_color = QColor(0,128,0);
    }
    update();

    if(m_unit >= m_randn*60)
    {
        m_timer->stop();
        m_alarmTimer->start();
    }
    emit sendIdAndColor(m_deviceId,m_color,m_randn*60-m_unit);
}

void PumpState::onAlarmTimeOut()
{
    if(m_unit >= m_randn*60)
    {
        if(!m_isOver)
        {
            m_color = QColor(255,255,255);
        }
        else
        {
            m_color = QColor(220,0,27);
        }
        m_isOver = !m_isOver;
        update();

        emit sendOverSignal();
        emit sendOpenAlarm(m_deviceId,true);
    }
    emit sendIdAndColor(m_deviceId,m_color,m_randn*60-m_unit);
}


void PumpState::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    m_rectHeight = rect().height();
    m_rectWidth = rect().width();
    //int side = qMin(w, h);
    //qDebug()<< h << w;
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);//启动反锯齿
    painter.setBrush(QBrush(QColor(40,40,40)));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(),5,5);

    m_rangeW = m_rectWidth/3;
    if(m_rangeW >= 150)
    {
        m_rangeW = 150;
    }
    else if(m_rangeW <= 120)
    {
        m_rangeW = 120;
    }
    m_rangeY = m_rectHeight/6;
    if(m_rangeY >= 50)
    {
        m_rangeY = 50;
    }
    else if(m_rangeY <= 38)
    {
        m_rangeY = 38;
    }

    double p = (double)m_rangeW/(double)m_rangeY;
    int widthOfChange = m_rangeW-m_unit*m_rangeW/m_randn/60;
    if(widthOfChange < 0)
    {
        widthOfChange = 0;
    }

    QRect bodyRect = QRect(0,0,m_rangeW,m_rangeY);
    bodyRect.moveCenter(QPoint(m_rectWidth/2,m_rectHeight/2));
    QRect changeRect = QRect(bodyRect.left(),bodyRect.top(),widthOfChange,m_rangeY);
    QRect twoRect = QRect(bodyRect.right(),bodyRect.top()-m_rangeY/6,m_rangeW/20,m_rangeY*4/3);
    QRect threeRect = QRect(twoRect.right(),bodyRect.top()+bodyRect.height()/4,bodyRect.height()/2,bodyRect.height()/2);
    QRect fourRect = QRect(threeRect.right(),bodyRect.top()+m_rangeY/6,m_rangeW/20,bodyRect.height()-m_rangeY/3);
    QRectF arcRect = QRectF(0,0,m_rangeW/p*3/2,m_rangeY*3/2);
    arcRect.moveCenter(QPoint(m_rectWidth/2,m_rectHeight/2));
    arcRect.setLeft(bodyRect.left()-m_rangeW/12);
    arcRect.setRight(bodyRect.left()+arcRect.height()-m_rangeW/12);
    QRect oneRect = QRect(0,0,bodyRect.height()/3,bodyRect.height()/3);
    oneRect.moveCenter(QPoint(m_rectWidth/2,m_rectHeight/2));
    oneRect.setRight(arcRect.left());
    oneRect.setLeft(arcRect.left()-bodyRect.height()/4);

    QRect oneCricleRect = QRect(bodyRect.right(),twoRect.top()-m_rangeW/40,m_rangeW/20,(int)(m_rangeY*p)/20);
    QRect secondCricleRect = QRect(bodyRect.right(),twoRect.bottom()-m_rangeW/40,m_rangeW/20,(int)(m_rangeY*p)/20);
    QRect thirdCricleRect = QRect(threeRect.right(),fourRect.top()-m_rangeW/40,m_rangeW/20,(int)(m_rangeY*p)/20);
    QRect fourCricleRect = QRect(threeRect.right(),fourRect.bottom()-m_rangeW/40,m_rangeW/20,(int)(m_rangeY*p)/20);
    QPolygonF polygon;
    polygon << QPointF(oneRect.left()-m_rangeW/3,m_rectHeight/2) << QPointF(oneRect.left(),m_rectHeight/2-bodyRect.height()/16)
            << QPointF(oneRect.left(),m_rectHeight/2+bodyRect.height()/16);

    QPointF scalePoint(bodyRect.left()+m_rangeW/26,bodyRect.bottom());
    QRect widgetRect = QRect(rect().left(),rect().top(),rect().width(),rect().height());
    QRect worldRect(bodyRect.left()-45,bodyRect.bottom()*7/6,m_rangeW+90,m_rangeY*2/3);
    QRect bedInfoRect = QRect(3,3,m_rangeW*7/8,m_rangeY*2/3);


    painter.save();
    //qDebug() << w << h;
    drawWhiteFrame(&painter,widgetRect);
    drawBody(&painter,bodyRect);
    drawRect(&painter,changeRect);
    drawRect(&painter,twoRect);

    drawRect(&painter,threeRect);
    drawRect(&painter,fourRect);
    drawOthers(&painter,arcRect);
    drawRect(&painter,oneRect);
    drawCricle(&painter,oneCricleRect);
    drawCricle(&painter,secondCricleRect);
    drawCricle(&painter,thirdCricleRect);
    drawCricle(&painter,fourCricleRect);
    drawTriangle(&painter,polygon);
    drawScale(&painter,scalePoint);
    drawWorld(&painter,m_dragName,worldRect);
    drawBedInfo(&painter,bedInfoRect,QString("Room%1-%2").arg(m_deviceId).arg(m_deviceId));
    int x = m_randn-m_unit/60;
    int y = -(m_unit - (m_randn - x) * 60);

    //qDebug() << m_randn*60-m_unit;

    if(x > 0)
    {
        drawTimeInfo(&painter,QString::number(x)+ "Min" +QString::number(y) + "s", bodyRect);
    }
    else
    {
        int m = m_randn*60-m_unit;
        if(m == -1)
        {
            m = 0;
        }
        drawTimeInfo(&painter,QString::number(m)+"s",bodyRect);
    }
    painter.restore();

    if(uimanager->m_fousId == this->m_deviceId)
    {
        painter.setPen(QPen(QColor(255,255,255),4));
        painter.drawLine(0,0,rect().width(),0);
        painter.drawLine(rect().width(),0,rect().width(),rect().height());
        painter.drawLine(rect().width(),rect().height(),0,rect().height());
        painter.drawLine(0,rect().height(),0,0);
    }
}

void PumpState::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(event->button() == Qt::LeftButton)
    {
        //this->setFocusPolicy(Qt::);
//        uimanager->m_fousId = this->m_deviceId;
        uimanager->setFousId(m_deviceId);
        m_mouseLeftPressed = rect().contains(event->pos());
    }
    if (event->buttons().testFlag(Qt::RightButton))
        m_mousePressed = rect().contains(event->pos());
    event->accept();
    update();
}

void PumpState::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if (event->buttons().testFlag(Qt::LeftButton))
        m_doublePressed = rect().contains(event->pos());
    event->accept();
}

void PumpState::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if (m_mousePressed && rect().contains(event->pos()))
    {
        emit sendOpenRightWin();
        m_mousePressed = false;
    }
    if (m_doublePressed && rect().contains(event->pos()))
    {
        emit openConfig(this->getDeviceId());
        m_doublePressed = false;
    }
    if (m_mouseLeftPressed && rect().contains(event->pos()))
    {
        emit checkPatientInfo(this->getDeviceId());
        m_mouseLeftPressed = false;
    }

    event->accept();
}


void PumpState::drawBody(QPainter *painter, const QRect &rect)
{
    painter->save();
    painter->setPen(QPen(m_color,2));
    painter->drawRoundedRect(rect,1,1);
    //painter->fillRect(rect,red);
    painter->restore();
}

void PumpState::drawRect(QPainter *painter, const QRect &rect)
{
    painter->save();
    painter->drawRoundedRect(rect,1,1);
    painter->fillRect(rect,m_color);
    painter->restore();
}


void PumpState::drawOthers(QPainter *painter, const QRectF &rect)
{
    painter->save();
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(rect);
    painter->setBrush(m_color);
    painter->drawChord(rect,139*16,82*16);
    painter->restore();
}

void PumpState::drawCricle(QPainter *painter, const QRect &rect)
{
    painter->save();
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(rect);
    painter->setBrush(m_color);
//    painter->drawChord(rect,140*16,80*16);
    painter->drawEllipse(rect);
    painter->restore();
}

void PumpState::drawTriangle(QPainter *painter ,const QPolygonF &polygon)
{
    painter->save();
    painter->setBrush(m_color);
    painter->drawPolygon(polygon, Qt::WindingFill);
    painter->drawPolyline(polygon);
    painter->restore();
}

void PumpState::drawScale(QPainter *painter , QPointF &p)
{
    painter->save();
    painter->setPen(QColor(255,255,255));
    for(int i = 0; i < 25; i++)
    {
        if((i+1) % 5 == 0)
        {
            QPointF p1(p.x()+i*m_rangeW*7/180,p.y());
            QPointF p2(p.x()+i*m_rangeW*7/180,p.y()-m_rangeY/5);
            painter->drawLine(p1,p2);
            continue;
        }
        QPointF p1(p.x()+i*m_rangeW*7/180,p.y());
        QPointF p2(p.x()+i*m_rangeW*7/180,p.y()-m_rangeY/10);
        painter->drawLine(p1,p2);
    }
    painter->restore();
}

void PumpState::drawWhiteFrame(QPainter *painter, const QRect &rect)
{
    painter->save();
    painter->setPen(QPen(QColor(255,255,255),1));
    painter->drawRoundedRect(rect,3,3);
    painter->restore();
}

void PumpState::drawChangeBody(QPainter *painter,const QRect &rect)
{
    painter->save();
    painter->drawRoundedRect(rect,5,5);
    painter->fillRect(rect,m_color);
    painter->restore();
}

void PumpState::drawWorld(QPainter *painter, const QString &world,const QRect &rect)
{
    painter->save();
    QPen pen;
    pen.setColor(QColor(255,255,255));
    painter->setPen(pen);
    QFont mfont = painter->font();
    mfont.setBold(true);
    mfont.setPixelSize(m_rangeW/8);
    painter->setPen(pen);
    painter->setFont(mfont);
    painter->drawText(rect, Qt::AlignCenter, world);
    painter->restore();
}

void PumpState::drawBedInfo(QPainter *painter, const QRect &rect, const QString &world)
{
    painter->save();
    painter->setBrush(QBrush(QColor(220,220,220)));
    painter->setPen(Qt::NoPen);
    painter->drawRoundRect(rect,5,5);

    QPen pen;
    pen.setColor(QColor(40, 40, 40));
    painter->setPen(pen);
    QFont mfont = painter->font();
    mfont.setBold(true);
    mfont.setPixelSize(m_rangeW/8);
    painter->setFont(mfont);
    painter->drawText(rect, Qt::AlignCenter, world);

    painter->restore();
}

void PumpState::drawTimeInfo(QPainter *painter, const QString &world, const QRect &rect)
{

    //qDebug() << world;
    painter->save();
    painter->setPen(QPen(QColor(255,255,255)));
    QFont mfont = painter->font();
    mfont.setBold(true);
    mfont.setPixelSize(m_rangeW/8);
    painter->setFont(mfont);
    painter->drawText(rect, Qt::AlignCenter, world);
    painter->restore();
}


QColor PumpState::getColor() const
{
    return this->m_color;
}

void PumpState::setColor(const QColor &color)
{
    if (this->m_color != color)
    {
        this->m_color = color;
        this->update();
    }
}

void PumpState::onSlotUpdate()
{
    this->update();
}

void PumpState::setPumpTime(int time)
{
//    if(this->m_randn != time)
//    {
    this->m_randn = time;
    this->m_unit = 0;
    m_timer->start();
    this->update();
//    }
}

void PumpState::setDeviceId(int id)
{
    if(this->m_deviceId != id)
    {
        this->m_deviceId = id;
        this->update();
    }
}

int PumpState::getDeviceId() const
{
    return this->m_deviceId;
}

void PumpState::setRoomInfo(const QString &roomInfo)
{
    if(m_roomInfo != roomInfo)
    {
        m_roomInfo = roomInfo;
        update();
    }
}

QString PumpState::getRoomInfo()
{
    return m_roomInfo;
}

void PumpState::setDragName(const QString &dragName)
{
    if(m_dragName != dragName)
    {
        m_dragName = dragName;
        update();
    }
}

QString PumpState::getDragName()
{
    return m_dragName;
}

void PumpState::setSockectId(const int &sockectId)
{
    if(m_sockectId != sockectId)
    {
        m_sockectId = sockectId;
    }
}

int PumpState::getSockectId()
{
    return m_sockectId;
}
