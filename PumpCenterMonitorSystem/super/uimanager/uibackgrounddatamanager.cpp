/**
* @FileName             uibackgrounddatamanager.cpp
* @Brief
* 1:UI 数据的后台管理线程，该对象为独立线程，主要负责将后台数据以均匀的速度推送给UI，避免UI数据阻塞，
* 2:该线程接收后台推送的实时数据，讲数据缓存到数据队列内
* 3:该线程周期性的将数据队列的数据推送给UI,
* 4:当数据队列的数据量过多时会 进行稍微的动态调整， 保证缓存内的数据不能太多
* 5:该线程不能去主动调用其他线程的接口，所有的数据必须由其他线程异步推送，如果主动去调用任意接口都有可能造成该线程自身阻塞；
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-06-09
* @Author               luteng
* @email
* @Create Date          2021-06-09
* @
*/
#include "uibackgrounddatamanager.h"
#include <QThread>
#include <QDebug>
#include <QMutex>
#include <QTimer>

Q_GLOBAL_STATIC(QMutex, createLock)
UIBackgroundDataManager *UIBackgroundDataManager::m_pInstance = nullptr;


UIBackgroundDataManager::~UIBackgroundDataManager()
{

}

UIBackgroundDataManager *UIBackgroundDataManager::instance()
{
    if (!m_pInstance)
    {
        QMutexLocker locker(createLock());
        if (!m_pInstance)
        {
            m_pInstance = new UIBackgroundDataManager(nullptr);
        }
    }

    return m_pInstance;
}

void UIBackgroundDataManager::start()
{
    subscribe(EV_Init);
    subscribe(EV_Quit);
    transform(MANAGER_TRANS(&UIBackgroundDataManager::init));
}

UIBackgroundDataManager::UIBackgroundDataManager(QObject *parent) : IManager(parent)
{
}

void UIBackgroundDataManager::init(UIBackgroundDataManager *me, const QEvent *ev)
{
    switch ((int)ev->type())
    {
        case EV_Init:
            {
                qDebug()<<"current thread:" <<QThread::currentThread()->objectName();
                me->doStart();
                me->transform(MANAGER_TRANS(&UIBackgroundDataManager::worker));
            } break;
        default:
            break;
    }
}

void UIBackgroundDataManager::worker(UIBackgroundDataManager *me, const QEvent *ev)
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

void UIBackgroundDataManager::onslotTimerout()
{
}

void UIBackgroundDataManager::doStart()
{
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    m_timer->setSingleShot(false);
    connect(m_timer, &QTimer::timeout, this, &UIBackgroundDataManager::onslotTimerout);
    m_timer->start();
}
