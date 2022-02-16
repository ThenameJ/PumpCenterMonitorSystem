/**
* @FileName             alarminfopage.cpp
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-11-09 10:13:51
* @Author               zhoumingjie
* @email
* @Create Date          2021-11-09 10:13:51
* @
*/
#include "alarminfopage.h"
#include "uimanager.h"
#include <QDebug>
#include <QScrollBar>
#include <QPropertyAnimation>
#include <QPair>


AlarmInfoPage::AlarmInfoPage(QWidget *parent) : BaseMenuPage(parent)
{
    QPalette pe;
    pe.setColor(QPalette::Background, QColor(40,40,40));
    setAutoFillBackground(true);
    setPalette(pe);

    connect(uimanager,SIGNAL(sendSetWorkerNum(int)),this,SLOT(onSlotSetNum(int)));
    connect(uimanager,SIGNAL(sendIdAndColor(int,QColor,int)),this,SLOT(onSlotIdAndColor(int,QColor,int)));
    connect(uimanager,SIGNAL(sendSelfRowSignal(int,int)),this,SLOT(onSlotSetSelfNum(int,int)));
    connect(uimanager,SIGNAL(sendSortSignal()),this,SLOT(onSlotSortSignal()));
    connect(uimanager,SIGNAL(sendConnectNumSignal(int)),this,SLOT(onSlotSetConnectNum(int)));

    this->m_newTitleBar->setTitleText("报警信息");
    QWidget *tableWidget = new QWidget;
    vlayout = new QVBoxLayout;
    vlayout->setSpacing(3);
    vlayout->setMargin(5);

    m_timer = new QTimer(this);
    m_timer->setTimerType(Qt::PreciseTimer);//高精度定时器 占用CPU资源
    m_timer->setInterval(1050);//每一秒触发一个timeout()信号
    connect(m_timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
//    m_timer->start();

    vlayout->addStretch();
    tableWidget->setLayout(vlayout);
    scroll = new QScrollArea(this);
    scroll->setWidget(tableWidget);
    scroll->setWidgetResizable(true);
    scroll->setFixedHeight(rect().height());
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pVertScrollBar = new SuspendedScrollBar(Qt::Vertical, scroll);
    connect(scroll->verticalScrollBar(),SIGNAL(valueChanged(int)),m_pVertScrollBar,SLOT(sltValueChangeScrollBar(int)));
    connect(m_pVertScrollBar,SIGNAL(valueChanged(int)),this,SLOT(sltValueChangeWidget(int)));
    connect(scroll->verticalScrollBar(),SIGNAL(rangeChanged(int,int)),m_pVertScrollBar,SLOT(sltRangeChanged(int,int)));
    this->addWidget(scroll);
}

AlarmInfoPage::~AlarmInfoPage()
{

}

void AlarmInfoPage::initWidget()
{
    for(int i = 0; i < 11; i++)
    {
        OneAlarmInfo *alarmInfo = new OneAlarmInfo;
        alarmInfo->setMaximumHeight(40);
        alarmInfo->setMinimumHeight(40);
        vlayout->addWidget(alarmInfo);
    }
}




void AlarmInfoPage::afterWidget()
{
    //vector.clear();
    if(m_deviceNum <= 0)
    {
        return;
    }
    for(int i = 0; i < m_deviceNum; i++)
    {
        OneAlarmInfo *alarmInfo = new OneAlarmInfo;
        alarmInfo->setMaximumHeight(40);
        alarmInfo->setMinimumHeight(40);
//        qDebug() << vector.count();
        alarmInfo->setRoomInfo(QString("Room%1-%2").arg(i+1).arg(i+1));
        m_map.insert(i,alarmInfo);
        //vector.append(i+1);
    }
//    vlayout->addStretch();
}

void AlarmInfoPage::clearWidget(QLayout *layout)
{
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr)
    {
         if(child->widget())
         {
             child->widget()->setParent(nullptr);
         }
         else if(child->layout())
         {
             clearWidget(child->layout());
         }
         delete child;
    }
}

void AlarmInfoPage::clearMap(QMap<int, OneAlarmInfo *> &map)
{
    qDeleteAll(map);
    map.clear();
}

void AlarmInfoPage::setDeviceNum(const int &num)
{
   if(m_deviceNum != num)
   {
       m_deviceNum = num;
   }
}


void AlarmInfoPage::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QPen pen;
    pen.setColor(QColor(200,200,200));
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawRect(rect());
}


void AlarmInfoPage::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
//    initWidget();
//    if(m_deviceNum != 0)
//    {
//        clearWidget(vlayout);
//    }
//    afterWidget();
    //infoSort();
    int iX = this->width() - 6;
    m_pVertScrollBar->setGeometry(iX,1,6,this->height()-2);
}


void AlarmInfoPage::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_pVertScrollBar->show();
}


void AlarmInfoPage::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_pVertScrollBar->hide();
}


void AlarmInfoPage::onSlotSetNum(int num)
{
    if(m_deviceNum != num)
    {
        m_deviceNum = num;
        clearWidget(vlayout);
        clearMap(m_map);
        //afterWidget();
    }
}

void AlarmInfoPage::onSlotSetSelfNum(int row, int line)
{
    if(m_deviceNum != row*line)
    {
        m_deviceNum = row*line;
        clearWidget(vlayout);
        clearMap(m_map);
        //afterWidget();
    }
}


void AlarmInfoPage::sltValueChangeWidget(int value)
{
    scroll->verticalScrollBar()->setValue(value);
}

void AlarmInfoPage::onSlotIdAndColor(int id, QColor color, int timeLeft)
{
    if(m_map.value(id-1) == Q_NULLPTR)
    {
        OneAlarmInfo *alarmInfo = new OneAlarmInfo;
        alarmInfo->setMaximumHeight(40);
        alarmInfo->setMinimumHeight(40);
//        qDebug() << vector.count();
        alarmInfo->setRoomInfo(QString("Room%1-%2").arg(id).arg(id));
        m_map.insert(id-1,alarmInfo);
    }
    m_map.value(id-1)->setColor(color);
    m_map.value(id-1)->setTimeLeft(timeLeft);
    m_map.value(id-1)->setDeviceId(id);
//    qDebug() << id << timeLeft;
    if(m_map.count() > 0)
    {
        if(!m_timer->isActive())
        {
            m_timer->start();
        }
    }
}

void AlarmInfoPage::onSlotSortSignal()
{

}

void AlarmInfoPage::onSlotSetConnectNum(const int &num)
{
    setDeviceNum(num);
    clearWidget(vlayout);
    clearMap(m_map);
//    afterWidget();
}

void AlarmInfoPage::onTimeOut()
{
    if(m_map.count() == 0)
    {
        m_timer->stop();
    }
//    qDebug() << m_map.count() << m_deviceNum;
    if(m_map.count() < m_deviceNum)
    {
        return;
    }
//    if(m_count != m_map.count())
//    {
//        m_count = m_map.count();
//    }

    clearWidget(vlayout);

    QMap<int, int> getMap;

    QMap<int, OneAlarmInfo*>::const_iterator it;
    for (it = m_map.constBegin(); it != m_map.constEnd(); ++it)
    {
        getMap.insert(it.key(),it.value()->getTimeLeft());
    }

    typedef QPair<int, int> p;
    QVector<p> vecter;
    for(auto ite = getMap.begin();ite != getMap.end(); ++ite)
    {
        p ele(ite.key(),ite.value());
        vecter.append(ele);
    }
    qSort(vecter.begin(),vecter.end(),[](p ele1, p ele2){
        return ele1.second < ele2.second;
    });

    QVector<p>::iterator iter;
    for (iter=vecter.begin();iter!=vecter.end();iter++)
    {
        vlayout->addWidget(m_map.value((*iter).first));
    }

    if(m_map.count() < 11)
    {
        vlayout->addStretch();
    }
}


SuspendedScrollBar::SuspendedScrollBar(Qt::Orientation t ,  QWidget *parent) : QScrollBar(parent)
{
    this->setOrientation(t);//设置水平或者垂直滚动条
    this->setStyleSheet("QScrollBar{"
                        "border:none;"
                        //"background:transparent;"
                    "}"
                    "QScrollBar:vertical"
                    "{"
                        "width:6px;"
                        "background:transparent; "
                        "margin:0px,0px,0px,0px;"
                        "padding-top:0px;"
                        "padding-bottom:0px;"
                    "}"
                    "QScrollBar::handle:vertical"
                    "{"
                        "width:6px;"
                        "background:rgba(250,250,250,60%);"
                        "border-radius:3px;"
                        "min-height:60;"
                    "}"
                    "QScrollBar::handle:vertical:hover"
                    "{"
                        "width:6px;"
                        "background:rgba(200,200,200,60%);"
                        "border-radius:3px;"
                        "min-height:60;"
                    "}"
                    "QScrollBar::add-line:vertical"
                    "{"
                        "height:0px;width:0px;"
                        "subcontrol-position:bottom;"
                    "}"
                    "QScrollBar::sub-line:vertical"
                    "{"
                        "height:0px;width:0px;"
                        "subcontrol-position:top;"
                    "}"
                    "QScrollBar::add-line:vertical:hover"
                    "{"
                        "height:0px;width:0px;"
                        "subcontrol-position:bottom;"
                    "}"
                    "QScrollBar::sub-line:vertical:hover"
                    "{"
                        "height:0px;width:0px;"
                        "subcontrol-position:top;"
                    "}"
                    "QScrollBar::sub-page:vertical{"
                        "background: none;"
                    "}"
                    "QScrollBar::add-page:vertical"
                    "{"
                        "background: none;"
                    "}"

                    "QScrollBar:horizontal"
                    "{"
                        "height:6px;"
                        "background:transparent; "
                        "margin:0px,0px,0px,0px;"
                        "padding-top:0px;"
                        "padding-bottom:0px;"
                    "}"
                    "QScrollBar::handle:horizontal"
                    "{"
                        "height:6px;"
                        "background:rgba(250,250,250,60%);"
                        "border-radius:3px;"
                        "min-width:60;"
                    "}"
                    "QScrollBar::handle:horizontal:hover"
                    "{"
                        "height:6px;"
                        "background:rgba(200,200,200,60%);"
                        "border-radius:3px;"
                        "min-width:60;"
                    "}"
                    "QScrollBar::add-line:horizontal"
                    "{"
                        "height:0px;width:0px;"
                        "subcontrol-position:bottom;"
                    "}"
                    "QScrollBar::sub-line:horizontal"
                    "{"
                        "height:0px;width:0px;"
                        "subcontrol-position:top;"
                    "}"
                    "QScrollBar::add-line:horizontal:hover"
                    "{"
                        "height:0px;width:0px;"
                        "subcontrol-position:bottom;"
                    "}"
                    "QScrollBar::sub-line:horizontal:hover"
                    "{"
                        "height:0px;width:0px;"
                        "subcontrol-position:top;"
                    "}"
                    "QScrollBar::sub-page:horizontal{"
                        "background: none;"
                    "}"
                    "QScrollBar::add-page:horizontal"
                    "{"
                        "background: none;"
                    "}");

    this->setRange(0 , 0);
    this->hide();
}


void SuspendedScrollBar::sltRangeChanged(int min,int max)
{
    this->setMinimum(min);
    this->setRange(0 , max);
    this->setPageStep(0.75 * (this->height() + max));
    if(max <= 0)
    {
        this->hide();
    }
}

void SuspendedScrollBar::sltrangechangedExtra(int min, int max)
{
    this->setMinimum(min);
    this->setRange(0 , max);
    this->setPageStep(0.75 * (this->width() + max));
//    if(max <= 0)
//    {
//        this->hide();
//    }
}

void SuspendedScrollBar::sltValueChangeScrollBar(int value)
{
    this->setValue(value);
}








