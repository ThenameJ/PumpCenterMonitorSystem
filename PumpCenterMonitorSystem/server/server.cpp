#include "server.h"
#include "messagequeue.h"
#include "servermanager.h"
#include "dbmanager.h"
//#include "connectionsmanager.h"
#include "uibackgrounddatamanager.h"
#include <QMutex>
#include <QThread>

Q_GLOBAL_STATIC(QMutex, lock)

Server *Server::m_pInstance = nullptr;

Server::Server()
{
    m_pMessageQueue = new MessageQueue();
}

Server::~Server()
{

}

Server *Server::instance()
{
    if (!m_pInstance)
    {
        QMutexLocker locker(lock());
        if (!m_pInstance)
        {
            m_pInstance = new Server();
        }
    }

    return m_pInstance;
}

MessageQueue *Server::getMessageQueue()
{
    return m_pMessageQueue;
}

void Server::init()
{
    QThread *th = Q_NULLPTR;

    //UI后台线程
    th = new QThread();
    uibackgrounddata->setMessageQueue(m_pMessageQueue);
    uibackgrounddata->moveToThread(th);
    uibackgrounddata->start();
    th->start();
    th->setPriority(QThread::NormalPriority);
    th->setObjectName("ui back Ground thread.............");

    //网络
    th = new QThread();
    cmsnetserver->setMessageQueue(m_pMessageQueue);
    cmsnetserver->moveToThread(th);
    cmsnetserver->start();
    th->start();
    th->setPriority(QThread::NormalPriority);
    th->setObjectName("Cms Monitor NetManager");

    //数据库
    dbmanager->setMessageQueue(m_pMessageQueue);
    dbmanager->moveToThread(th);
    dbmanager->start();
    th->start();
    th->setPriority(QThread::NormalPriority);
    th->setObjectName("DB Open Success");


//    //
//    th = new QThread();
//    connectionmanager->setMessageQueue(m_pMessageQueue);
//    connectionmanager->moveToThread(th);
//    connectionmanager->start();
//    th->start();
//    th->setPriority(QThread::NormalPriority);
//    th->setObjectName("Client Connections Manager Thread...............");
}

void Server::start()
{
    VariantEv *ev = new VariantEv((QEvent::Type)EV_Init);
    m_pMessageQueue->publish(EV_Init, ev);
}

void Server::quit()
{
    VariantEv *ev = new VariantEv((QEvent::Type)EV_Quit);
    m_pMessageQueue->publish(EV_Quit, ev);
}

void Server::publish(int id, const QEvent *event)
{
    instance()->eventHandle(id, event);
    instance()->getMessageQueue()->publish(id, event);
}


void Server::eventHandle(int id, const QEvent *event)
{
    Q_UNUSED(id);
    Q_UNUSED(event);
//    switch (id)
//    {
//        case EV_AdmitPatient:
//            {
//            }
//        case EV_UpdatePatient:
//            {
//            }
//        default:
//            break;
//    }
}

