/**
* @FileName             monitoroverviewcontent.cpp
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-08-20
* @Author               luteng
* @email
* @Create Date          2021-08-20
* @
*/
#include "monitoroverviewcontent.h"
#include "pumpconfigpage.h"
#include "baseclosemenupage.h"
#include "dbmanager.h"
//#include "alarminfopage.h"
#include "pumpstate.h"
#include <QBuffer>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDebug>
#include <QScrollBar>


MonitorOverViewContent::MonitorOverViewContent(QWidget *parent) : QWidget(parent)
{
    m_pumpNum = 16;
    m_index = 0;
    m_newData_extra = 0;
    m_newData_x = 0;
    m_newData_y = 0;
    QPalette pe;
    pe.setColor(QPalette::Background, QColor(100, 100, 100));
    setAutoFillBackground(true);
    setPalette(pe);
    setMouseTracking(true);


    //
    initContent();
    qRegisterMetaType<databuf>("databuf");
    connect(this,SIGNAL(sendIsLeaveSignal(bool)),uimanager,SIGNAL(sendIsLeaveSignal(bool)));

//    connect(this,SIGNAL(sendConnectNumSignal(int)),uimanager,SIGNAL(sendConnectNumSignal(int)));
    connect(uimanager,SIGNAL(sendSetWorkerNum(int)),this,SLOT(onSlotReciveNumSignal(int)));
    connect(uimanager,SIGNAL(sendOpenConfig(int)),this,SLOT(onSlotShowPumpConfig(int)));
    connect(uimanager,SIGNAL(sendMenuParamSetting(ConfigInfo)),this,SLOT(onSlotReciveParamSetting(ConfigInfo)));
    connect(uimanager,SIGNAL(sendSelfRowSignal(int,int)),this,SLOT(onSlotSelfRowNum(int,int)));
    connect(uimanager,SIGNAL(sendStrutData(QByteArray,int)),this,SLOT(onSlotReciveStrutData(QByteArray,int)));
    connect(uimanager,SIGNAL(sendDisConnectSignal(int)),this,SLOT(onSlotDisConnectClient(int)));
    connect(this,SIGNAL(sendDisconnect(int)),uimanager,SIGNAL(disConnectSig(int)));
    connect(this,SIGNAL(sendCloseAlarm(int,bool)),uimanager,SLOT(onSlotCloseAlarm(int, bool)));
}

MonitorOverViewContent::~MonitorOverViewContent()
{

}


int MonitorOverViewContent::initRandn()
{
    QTime time = QTime::currentTime();
    qsrand(time.msec()*qrand()*qrand()*qrand()*qrand()*qrand()*qrand());
    int randn = qrand() % 20;
    if(randn < 1)
        randn = 3;
    return randn;
}


void MonitorOverViewContent::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
//    initContent();
}


void MonitorOverViewContent::wheelEvent(QWheelEvent *event)
{
    Q_UNUSED(event);
    m_isLeave = true;
    sendIsLeaveSignal(m_isLeave);
}

void MonitorOverViewContent::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_isLeave = false;
    sendIsLeaveSignal(m_isLeave);
}


void MonitorOverViewContent::initContent()
{
    //SuspendedScrollBar *m_pVertScrollBar = new SuspendedScrollBar(Qt::Vertical , this);
    vlayout = new QVBoxLayout();
    vlayout->setSpacing(1);
    vlayout->setMargin(1);
    //
    int x = 4;
    int y = 4;
    for (int i = 0; i < x; i++)//行
    {
        QHBoxLayout *hlayout = new QHBoxLayout();
        hlayout->setSpacing(2);
        hlayout->setMargin(1);
        for (int col = 0; col < y; col++)//列
        {
            EmptyWindow *emptyWindow = new EmptyWindow();
            m_Map.insert(i*4+col+1,emptyWindow);//键值
            hlayout->addWidget(emptyWindow);
        }
        vlayout->addLayout(hlayout);

        if (layout()){
            delete layout();
        }
    }
    setLayout(vlayout);
}

void MonitorOverViewContent::afterChangeWin()
{

    if(m_Map.count() > 0)
    {
        clearMap(m_Map);
    }

    vlayout = new QVBoxLayout();
    vlayout->setSpacing(1);
    vlayout->setMargin(1);
    //
    if(!m_isChange)
        numChange(m_pumpNum,m_newData_x,m_newData_y,m_newData_extra);

    for (int i = 0; i < m_newData_y; i++)//列
    {
        QHBoxLayout *hlayout = new QHBoxLayout();
        hlayout->setSpacing(1);
        hlayout->setMargin(1);
        for (int col = 0; col < m_newData_x; col++)//行
        {
//            int m = initRandn();
//            PumpState *pumpView = new PumpState();
//            pumpView->setPumpTime(m);
//            pumpView->setDeviceId(m_newData_x*i+col+1);
//            m_MapTab.insert(m_newData_x*i+col+1,pumpView);//键值
//            hlayout->addWidget(pumpView);
            EmptyWindow *emptyWindow = new EmptyWindow();
            m_Map.insert(m_newData_x*i+col+1,emptyWindow);//键值
            hlayout->addWidget(emptyWindow);
            //connect(pumpView,SIGNAL(openConfig(int)),this,SLOT(onSlotShowPumpConfig(int)));
        }

        vlayout->addLayout(hlayout);

    if (layout())
        delete layout();
    }

    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->setSpacing(1);
    hlayout->setMargin(1);
    for (int i = 0; i < m_newData_extra; i++)//列
    {
//        int m = initRandn();
//        PumpState *pumpView = new PumpState();
//        pumpView->setPumpTime(m);
//        pumpView->setDeviceId(m_newData_x*m_newData_y+i+1);
//        m_MapTab.insert(m_newData_x*m_newData_y+i+1,pumpView);//键值
//        hlayout->addWidget(pumpView);
        EmptyWindow *emptyWindow = new EmptyWindow();
        m_Map.insert(m_newData_x*m_newData_y+i+1,emptyWindow);//键值
        hlayout->addWidget(emptyWindow);
        //connect(pumpView,SIGNAL(openConfig(int)),this,SLOT(onSlotShowPumpConfig(int)));
    }

    if(m_newData_extra)
    {
        for(int i = 0; i < m_newData_x - m_newData_extra; i++)
        {
            QWidget *extra = new QWidget();
            hlayout->addWidget(extra);
        }
    }

    vlayout->addLayout(hlayout);
    setLayout(vlayout);

}

void MonitorOverViewContent::clearMapTab(QMap<int, PumpState *> &map)
{
    qDeleteAll(map);
    map.clear();
}

void MonitorOverViewContent::clearMap(QMap<int, EmptyWindow*> &map)
{
//    QList<int> iList = map.keys();
//    for(int i = 0; i < iList.size(); i++)
//    {
//        PumpState * pPump = map.value(iList.at(i));
//        if(pPump)
//        {
//            disconnect(pPump, SIGNAL(openConfig(int)),this,SLOT(onSlotShowPumpConfig(int)));
//        }
//    }
    qDeleteAll(map);
    map.clear();
}

void MonitorOverViewContent::deleteWin(QLayout *layout)
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
             deleteWin(child->layout());
         }
         delete child;
    }
}

void MonitorOverViewContent::numChange(const int &numOfPump, int &x, int &y, int &extra)
{
    for(int i = 1; i <= 5; i++)
    {
        if(numOfPump != i*i && numOfPump < i*i)
        {
            x = i;
            y = i - 1;
            if(numOfPump < x*y)
            {
                y = i-2;
            }
            extra = numOfPump - x*y;
            break;
        }
        if(numOfPump == i*i)
        {
            x = i;
            y = i;
            extra = 0;
            break;
        }
        if(numOfPump >25)
        {
            x = 5;
            y = numOfPump/5;
            extra = numOfPump - x*y;
        }
    }
}

void MonitorOverViewContent::onSlotReciveNumSignal(int num)
{
    if(num != m_pumpNum)
    {
        clearMapTab(m_MapTab);
        clearMap(m_Map);
        deleteWin(layout());
        m_pumpNum = num;
        m_connectNum = 0;
        m_isChange = false;
        afterChangeWin();
    }
}

void MonitorOverViewContent::onSlotSelfRowNum(int row, int line)
{
    if(row == 0)
    {
        row = 1;
    }
    if(line == 0)
    {
        line = 1;
    }


    if(row != m_newData_x || line != m_newData_y)
    {
        clearMapTab(m_MapTab);
        clearMap(m_Map);
        deleteWin(layout());
        m_pumpNum = row*line;
        m_newData_x = row;
        m_newData_y = line;
        m_newData_extra = 0;
        m_connectNum = 0;
        m_isChange = true;
        afterChangeWin();
    }
}

void MonitorOverViewContent::onSlotShowPumpConfig(int decviceId)
{
    m_index = decviceId;
    PumpConfig->setParent(this->parentWidget());
    PumpConfig->show();
    PumpConfig->move(0, 1020 - PumpConfig->height());
    PumpConfig->m_newTitleBar->setTitleText("参数配置");
}

void MonitorOverViewContent::onSlotReciveParamSetting(ConfigInfo data)
{
    QMap<int,PumpState*>::Iterator it;
    it = m_MapTab.find(m_index);
    if(it != m_MapTab.end())
    {
        if(data.pumpTime != 0)
        {
            m_MapTab.find(m_index).value()->setPumpTime(data.pumpTime);
        }
        if(data.drugName != Q_NULLPTR)
        {
            m_MapTab.find(m_index).value()->setDragName(data.drugName);
        }
        emit sendCloseAlarm(m_index, false);
    }
}

void MonitorOverViewContent::onSlotReciveStrutData(QByteArray Data, int sockectId)
{
    QBuffer buf(&Data);
    buf.open(QIODevice::ReadOnly);
    QDataStream in(&buf);
    databuf pumpData;
    in >> pumpData;

    if(pumpData.deviceId == 0)
    {
        emit sendDisconnect(sockectId);
        return;
    }

//    qDebug() << pumpData.deviceId << pumpData.drugName << pumpData.pumpTime;

    if(m_MapTab.value(pumpData.deviceId) != Q_NULLPTR || pumpData.deviceId > m_pumpNum)            //16为当前床位个数
    {
//       if(pumpData.deviceId > m_pumpNum)
//       {
//            return ;
//       }
//       else
//       {
            if(m_connectNum > m_pumpNum)
            {
                return ;
            }
            else
            {
//                pumpData.deviceId = m_connectNum + 1;
                QMap<int,EmptyWindow*>::iterator it;
                for(it = m_Map.begin();it != m_Map.end(); ++it)
                {
                    if(it.value() != Q_NULLPTR )
                    {
                        pumpData.deviceId = it.key();
                        break;
                    }
                }
            }
//       }
    }
    if(m_MapTab.value(pumpData.deviceId) == Q_NULLPTR && pumpData.deviceId <= m_pumpNum)
    {

       if(m_connectNum <= m_pumpNum)
       {
           PumpState *pumpView = new PumpState();
           pumpView->setPumpTime(pumpData.pumpTime);
           pumpView->setDeviceId(pumpData.deviceId);
           pumpView->setDragName(pumpData.drugName);
           pumpView->setSockectId(sockectId);
           if(m_Map.value(pumpData.deviceId))
           {
               vlayout->replaceWidget(m_Map.value(pumpData.deviceId), pumpView);
           }
           m_Map.value(pumpData.deviceId)->setParent(Q_NULLPTR);
           m_Map.remove(pumpData.deviceId);
           m_MapTab.insert(pumpData.deviceId,pumpView);
           ++m_connectNum;
       }
       else
       {
           return;
       }
    }
    VariantEv *fvar = new VariantEv(QEvent::Type(EV_DataInsert));
    fvar->var.setValue(pumpData);
    dbmanager->publish(EV_DataInsert,fvar);
}

void MonitorOverViewContent::onSlotDisConnectClient(int deviceId)
{
    Q_UNUSED(deviceId)
//    qDebug() << m_connectNum;
//    qDebug() << deviceId << "BBBBBBBBBB";
    if(m_connectNum > 0)
    {
        int x = 0;
        QMap<int, PumpState*>::const_iterator i;
        for (i = m_MapTab.constBegin(); i != m_MapTab.constEnd(); ++i)
        {
            if(i.value()->getSockectId() == deviceId)
            {
                x = i.key();
                emit sendCloseAlarm(i.value()->getDeviceId(),false);
                break;
            }
        }
        EmptyWindow *empty = new EmptyWindow;
        if(m_MapTab.value(x))
        {
            vlayout->replaceWidget(m_MapTab.value(x),empty);
        }
        m_Map.insert(x,empty);
        m_MapTab.value(x)->deleteLater();
        m_MapTab.remove(x);

        m_connectNum = m_connectNum - 1;
    }
    if(m_connectNum == 0)
    {
//        clearMapTab(m_MapTab);
    }
}

