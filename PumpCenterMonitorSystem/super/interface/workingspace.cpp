/**
* @FileName             workingspace.cpp
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-08-20
* @Author               luteng
* @email
* @Create Date          2021-08-20
* @
*/
#include "workingspace.h"
#include "monitoroverviewcontent.h"
#include "monitortimeleftlist.h"
#include "interfacetopbar.h"
#include <QPaintEvent>
#include <QPainter>
#include <QFont>
#include <QTimer>
#include <QHBoxLayout>
#include <QScrollBar>
#include <QDebug>

WorkingSpace::WorkingSpace(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
    installEventFilter(this);
    //setMouseTracking(true);//只有设置这个鼠标不移动才会触发鼠标移动事件
    m_timer = new QTimer(this);
    m_timer->setSingleShot(false);
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, this, &WorkingSpace::onSlotTimeout);
    m_timer->start();
    //
    initSpace();
    initButton();
    connect(uimanager,SIGNAL(sendShowHideSignal(bool)),this,SLOT(onSlotShowHideSignal(bool)));
    connect(uimanager,SIGNAL(sendIsLeaveSignal(bool)),this,SLOT(onSlotIsLeaveSignal(bool)));
    connect(uimanager,SIGNAL(sendRowNum(int)),this,SLOT(onSlotRowNum(int)));
    connect(m_showHideButton,SIGNAL(clicked(bool)),uimanager,SIGNAL(sendHideRightWindow()));
}

WorkingSpace::~WorkingSpace()
{

}

void WorkingSpace::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.fillRect(event->rect(), QColor(50, 50, 50));
}

void WorkingSpace::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    m_pVertScrollBar->setGeometry(this->width()-8,1,8,this->height()-2);
    m_pHoriScrollBar->setGeometry(1,this->height()-63,this->width()-2,8);
    m_showHideButton->move(this->width()-m_showHideButton->width()-3,566-m_showHideButton->height()/2);
}

bool WorkingSpace::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseMove)
   {
       QMouseEvent *mouseMove = static_cast<QMouseEvent*>(event);
       QRect rect = m_showHideButton->frameGeometry();
       if (rect.contains(mouseMove->pos()))
       {
           m_showHideButton->show();
       }
       else
       {
           m_showHideButton->hide();
       }
   }
    return QWidget::eventFilter(watched, event);
}

void WorkingSpace::onSlotTimeout()
{
    InterfaceTopBar *topbar = qobject_cast<InterfaceTopBar*>(m_subItems.value(SubItem_TopBar));
    if (topbar == Q_NULLPTR)
        return;
    topbar->updateSysTime();
}

void WorkingSpace::onSlotShowHideSignal(bool value)
{
    int iX = this->width() - 8;
    if(!value)
    {
        m_pVertScrollBar->setGeometry(iX,1,6,this->height()-2);
        m_pHoriScrollBar->setGeometry(1,this->height()-63,this->width()-2,8);
    }
    else
    {
        m_pVertScrollBar->setGeometry(iX-402,1,6,this->height()-2);
        m_pHoriScrollBar->setGeometry(1,this->height()-63,this->width()-402,8);
    }

    if(!value)
    {
        m_showHideButton->setIcon(uimanager->getResource()->pixmap(Cms::Res::IMAGE_DoubleLeft));
        m_showHideButton->move(width()-m_showHideButton->width()-3,566-m_showHideButton->height()/2);
    }
    else
    {
        m_showHideButton->setIcon(uimanager->getResource()->pixmap(Cms::Res::IMAGE_DoubleRight));
        m_showHideButton->move(width()-404-m_showHideButton->width(),566-m_showHideButton->height()/2);
    }

}

void WorkingSpace::sltValueChangeWidget(int value)
{
    scroll->verticalScrollBar()->setValue(value);
}

void WorkingSpace::sltHoriValueChangeWidget(int value)
{
    scroll->horizontalScrollBar()->setValue(value);
}


void WorkingSpace::onSlotIsLeaveSignal(bool isLeave)
{
    if(!isLeave)
    {
        m_pVertScrollBar->hide();
    }
    else
    {
        m_pVertScrollBar->show();
    }
}

void WorkingSpace::onSlotRowNum(int row)
{
    if(row > 5)
    {
        m_pHoriScrollBar->show();
    }
    else
    {
        m_pHoriScrollBar->hide();
    }

}


void WorkingSpace::initSpace()
{
    MonitorOverViewContent *overview = new MonitorOverViewContent();
    MonitorTimeLeftList *timeLeftList = new MonitorTimeLeftList();

    scroll = new QScrollArea(this);
    scroll->setWidget(overview);
    scroll->setWidgetResizable(true);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setMouseTracking(true);
    m_pVertScrollBar = new SuspendedScrollBar(Qt::Vertical,scroll);
    m_pHoriScrollBar = new SuspendedScrollBar(Qt::Horizontal,scroll);

    connect(scroll->verticalScrollBar(),SIGNAL(valueChanged(int)),m_pVertScrollBar,SLOT(sltValueChangeScrollBar(int)));
    connect(scroll->verticalScrollBar(),SIGNAL(rangeChanged(int,int)),m_pVertScrollBar,SLOT(sltRangeChanged(int,int)));
    connect(m_pVertScrollBar,SIGNAL(valueChanged(int)),this,SLOT(sltValueChangeWidget(int)));

    connect(scroll->horizontalScrollBar(),SIGNAL(valueChanged(int)),m_pHoriScrollBar,SLOT(sltValueChangeScrollBar(int)));
    connect(scroll->horizontalScrollBar(),SIGNAL(rangeChanged(int,int)),m_pHoriScrollBar,SLOT(sltrangechangedExtra(int,int)));
    connect(m_pHoriScrollBar,SIGNAL(valueChanged(int)),this,SLOT(sltHoriValueChangeWidget(int)));
    //qDebug() << isHide;

    timeLeftList->setFixedWidth(400);
    m_subItems.insert(SubItem_OverView, overview);
    m_subItems.insert(SubItem_LeftTimeList, timeLeftList);
    //
    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->setSpacing(2);
    hlayout->setMargin(2);
    hlayout->addWidget(scroll);
    hlayout->addWidget(timeLeftList);

    //
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setSpacing(0);
    vLayout->setMargin(0);
    //
    InterfaceTopBar *topBar = new InterfaceTopBar();
    topBar->setFixedHeight(55);
    m_subItems.insert(SubItem_TopBar, topBar);
    vLayout->addWidget(topBar);
    vLayout->addLayout(hlayout);
    //
    if (layout())
        delete layout();

    setLayout(vLayout);
}

void WorkingSpace::initButton()
{
    m_showHideButton = new MyShowHideButton(this);
    m_showHideButton->setFocusPolicy(Qt::NoFocus);
    m_showHideButton->setFixedSize(13,42);
    m_showHideButton->setIcon(uimanager->getResource()->pixmap(Cms::Res::IMAGE_DoubleLeft));
    m_showHideButton->setIconSize(m_showHideButton->size());
    m_showHideButton->setStyleSheet("border:none;");
    m_showHideButton->setAttribute(Qt::WA_TranslucentBackground);
    m_showHideButton->hide();
}



