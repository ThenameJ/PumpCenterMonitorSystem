#ifndef CMSNETSERVERMANAGER_H
#define CMSNETSERVERMANAGER_H

#include <QObject>
#include "imanager.h"
#include "imagesourceid.h"

class TcpServer;
class TcpSocket;
class ServerManager : public IManager
{
    Q_OBJECT
    Q_DISABLE_COPY(ServerManager)
public:
    static ServerManager *instance();

    virtual ~ServerManager();

    /**
     * @brief start
     */
    virtual void start() Q_DECL_OVERRIDE;

signals:
    /**
     * @brief connectNewClient一个新的客户端连接
     * @param newSocket
     */
    void connectNewClient(Cms::ProtocolType protocol, qint64 socketDescriptor);

//    /**
//     * @brief disconnected
//     * @param socketID
//     */
//    void disconnected(qint64 socketID);

protected:

    explicit ServerManager(QObject *parent = nullptr);

    /**
     * @brief init 初始化状态函数
     * @param me
     * @param ev
     */
    static void init(ServerManager *me, QEvent const *ev);

    /**
     * @brief worker 工作状态函数
     * @param me
     * @param ev
     */
    static void worker(ServerManager *me, QEvent const *ev);

public:
    void exitOperate();

private:
    void startTcp();

    void mainExit();
private:
    static ServerManager  *m_pInstance;
    QMap<Cms::ProtocolType, TcpServer*> m_tcpServers;
};

#define cmsnetserver ServerManager::instance()

#endif // CMSNETSERVERMANAGER_H
