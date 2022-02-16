/**
* @FileName             uimanager.pri
* @Brief                摘要
* @Version              1.0.0
* @Current Maintainter  修改者
* @Update Date          2019-06-29
* @Author               luteng
* @email                luteng1230@163.com
* @Create Date          2019-06-29
* @
*/
#include "uimanager.h"
#include <QTranslator>
#include <QApplication>
#include <QFileInfo>
#include <mutex>
#include <QDebug>
#include <QMutexLocker>
#include <QThread>
#include <QSettings>
#include "server.h"

Q_GLOBAL_STATIC(QMutex, createLock)
UIManager *UIManager::m_pInstance = nullptr;

UIManager::UIManager(QObject *parent) : IManager(parent)
{
    sound = new QSound(":/resource/sound/mid.wav", this);
    sound->setLoops(QSound::Infinite);//设置循环次数
    connect(this,&UIManager::voiceCheckChanged,[&](bool voiceCheck){
        if(m_voiceCheck != voiceCheck)
        {
            m_voiceCheck = voiceCheck;
        }
    });

    m_timer = new QTimer;
    m_timer->setTimerType(Qt::PreciseTimer);//高精度定时器 占用CPU资源
    m_timer->setInterval(1000);//每一秒触发一个timeout()信号
    connect(m_timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));

    m_timer->start();
}

UIManager::~UIManager()
{

}

UIManager *UIManager::instance()
{
    if (!m_pInstance)
    {
        QMutexLocker locker(createLock());
        if (!m_pInstance)
        {
            m_pInstance = new UIManager(nullptr);
        }
    }

    return m_pInstance;
}

void UIManager::start()
{
    subscribe(EV_Init);
    subscribe(EV_Quit);
    transform(MANAGER_TRANS(&UIManager::init));
}

CMSResourceManager *UIManager::getResource()
{
    return CMSResourceManager::instance();
}


void UIManager::init(UIManager *me, const QEvent *ev)
{
    qDebug()<<"uimanager current Thread:" << QThread::currentThread()->objectName();
    switch ((int)ev->type())
    {
        case EV_Init:
            {
                me->transform(MANAGER_TRANS(&UIManager::worker));
            } break;
        default:
            break;
    }
}

void UIManager::worker(UIManager *me, const QEvent *ev)
{
    switch ((quint16)ev->type())
    {
        case EV_Quit:
            me->transform(MANAGER_TRANS(&IManager::quit));
            break;
        default:
            break;
    }
}

void UIManager::onSlotAlarm(int id, bool isOpen)
{
//        QSound::play(":/resource/sound/mid.wav");
    if(isOpen == true)
    {
        if(record[id-1] == 1)
        {
            return;
        }
        record[id-1]++;
    }
}

void UIManager::onSlotCloseAlarm(int id, bool isClose)
{
    if(isClose == false)
    {
        if(record[id-1] == 0)
        {
            return;
        }
        record[id-1]--;
    }
}

void UIManager::onTimeOut()
{
    if(m_voiceCheck)
    {
        int flag = 0;
        for(int i = 0; i < 100; i++)
        {
            if(record[i] == 1)
            {
                flag = 1;
            }
        }
        if(flag == 1)
        {
            if(sound->isFinished())
            {
                sound->play();
            }
        }
        else
        {
            sound->stop();
        }
    }
    else
    {
        sound->stop();
    }

}

void UIManager::setFousId(int fousId)
{
    if(m_fousId != fousId)
    {
        m_fousId = fousId;
    }
}
