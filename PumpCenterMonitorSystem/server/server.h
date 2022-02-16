#ifndef SERVER_H
#define SERVER_H

#include "messagequeue.h"

class Server
{

public:
    ~Server();

    static Server *instance();

    MessageQueue *getMessageQueue();

    void init();

    void start();

    void quit();

    static void publish(int id, const QEvent* event);

protected:
    Server();

    void eventHandle(int id, const QEvent* event);

private:
    static Server           *m_pInstance;
    MessageQueue            *m_pMessageQueue;
};

#define cmsserver Server::instance()

#endif // SERVER_H
