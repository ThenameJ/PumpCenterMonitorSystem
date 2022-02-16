#include "servermanager.h"
#include <mutex>
#include <QMutexLocker>
#include <QThread>
#include <QDebug>

#include "tcpserver.h"

Q_GLOBAL_STATIC(QMutex, createLock)

ServerManager *ServerManager::m_pInstance = nullptr;

ServerManager::ServerManager(QObject *parent) : IManager(parent)
{
    qRegisterMetaType<Cms::ProtocolType>("procotoltype");
}

void ServerManager::init(ServerManager *me, const QEvent *ev)
{
    qDebug()<<"current Thread:" << QThread::currentThread()->objectName();
    switch ((int)ev->type())/*int类型强制转换ev->type()返回值Type类型，在evenid.h文件中枚举判断值。*/
    {
        case EV_Init:
            {
                me->startTcp();
                me->transform(MANAGER_TRANS(&ServerManager::worker));
                /*把CMSNetServerManager::worker变成IManager::CakkFuntion类型*/
            } break;
        default:
            break;
    }
}

void ServerManager::worker(ServerManager *me, const QEvent *ev)
{
    switch ((quint16)ev->type())
    {
        case EV_Quit:
            me->mainExit();
            me->transform(MANAGER_TRANS(&IManager::quit));
            break;
        default:
            break;
    }
}

void ServerManager::exitOperate()
{
    mainExit();
}

void ServerManager::startTcp()
{
    TcpServer *sSeriesServer = new TcpServer;
    sSeriesServer->listen(QHostAddress::Any, 6666);
    m_tcpServers.insert(Cms::Protocol_pump, sSeriesServer);
//    connect(sSeriesServer, SIGNAL(connectNewClient(Cms::ProtocolType,qint64)), this, SIGNAL(connectNewClient(Cms::ProtocolType,qint64)));
}

ServerManager::~ServerManager()
{
    qDebug()<<__FUNCTION__;
    mainExit();
}

void ServerManager::start()
{
    subscribe(EV_Init);/*调用IManager类中的函数，参数是int类型*/
    subscribe(EV_Quit);
    transform(MANAGER_TRANS(&ServerManager::init));
}

void ServerManager::mainExit()
{
    foreach (auto ser, m_tcpServers)
    {
        ser->clear();/*调用类cmstcpserver中的函数*/
    }
}

ServerManager *ServerManager::instance()
{
    if (!m_pInstance)
    {
        QMutexLocker locker(createLock());
        if (!m_pInstance)
        {
            m_pInstance = new ServerManager(nullptr);
        }
    }

    return m_pInstance;
}
