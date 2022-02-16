#include "tcpserver.h"
#include "threadhandle.h"
#include "uimanager.h"

TcpServer::TcpServer(int numConnections, QObject *parent)
    : QTcpServer(parent)
{
    Q_UNUSED(numConnections)
    qDebug()<<"TcpServer start";
    setMaxPendingConnections(16);
    nConnectCount = 0;

    connect(this,SIGNAL(clearLineEdit()),uimanager,SIGNAL(clearLineEdit()));

    connect(uimanager,&UIManager::sendSetWorkerNum,[&](int num){
        this->setMaxPendingConnections(num);
    });
    connect(uimanager,&UIManager::sendSelfRowSignal,[&](int row, int line){
        if(row == 0)
        {
            row = 1;
        }
        if(line == 0)
        {
            line = 1;
        }
        this->setMaxPendingConnections(row*line);
    });
    connect(this,SIGNAL(sendConnectNumSignal(int)),uimanager,SIGNAL(sendConnectNumSignal(int)));
}

TcpServer::~TcpServer()
{
    qDebug()<<"TcpServer finish";
    emit this->sentDisConnect(-1);
    this->close();
}

void TcpServer::setMaxPendingConnections(int numConnections)
{
    this->QTcpServer::setMaxPendingConnections(numConnections);//调用Qtcpsocket函数，设置最大连接数，主要是使maxPendingConnections()依然有效
    this->maxConnections = numConnections;
}

void TcpServer::incomingConnection(qintptr socketDescriptor) //多线程必须在此函数里捕获新连接
{

//    qDebug() << tcpClient.count();
//    qDebug() << maxConnections;

//    qWarning()<<"new connecting comming......." <<socketDescriptor;

    if (tcpClient.count() >= maxConnections)//继承重写此函数后，QTcpServer默认的判断最大连接数失效，自己实现
    {
        QTcpSocket tcp;
        tcp.setSocketDescriptor(socketDescriptor);
        tcp.disconnectFromHost();
        return;
    }
    TcpSocket* tcpTemp = new TcpSocket(socketDescriptor);
    tcpClient.insert(socketDescriptor,tcpTemp);//插入到连接信息中

//    waitForNewConnection(1000);

    QThread* th = ThreadHandle::getClass().getThread();

    QString ip =  tcpTemp->peerAddress().toString();
    quint16 port = tcpTemp->peerPort();

    //NOTE:断开连接的处理，从列表移除，并释放断开的Tcpsocket，此槽必须实现，线程管理计数也是考的他
    connect(tcpTemp,&TcpSocket::sockDisConnect,this,&TcpServer::sockDisConnectSlot);
    connect(this, &TcpServer::sentDisConnect, tcpTemp, &TcpSocket::disConTcp);//断开信号
    tcpTemp->moveToThread(th);//把tcp类移动到新的线程，从线程管理类中获取

    emit connectClient(socketDescriptor,ip,port);
    nConnectCount++;
    qDebug()<<"new connection" <<"socketDescriptor="<<socketDescriptor;
    qDebug()<<"当前连接个数为："<<nConnectCount;
    emit sendConnectNumSignal(nConnectCount);
}

void TcpServer::sockDisConnectSlot(qint64 socketDescriptor, const QString & ip, quint16 port, QThread * th)
{
    nConnectCount--;
    qDebug() << "disconnect" <<"socketDescriptor="<<socketDescriptor;
    qDebug()<<"当前连接个数为："<<nConnectCount;
    tcpClient.remove(socketDescriptor);//连接管理中移除断开连接的socket
    ThreadHandle::getClass().removeThread(th); //告诉线程管理类那个线程里的连接断开了
    emit sockDisConnect(socketDescriptor,ip,port);
    emit sendConnectNumSignal(nConnectCount);
    emit clearLineEdit();
}

void TcpServer::clear()
{
    if(tcpClient.count() != 0)
    {
        qDebug() << "设备全部断开";
    }
    emit this->sentDisConnect(-1);
    ThreadHandle::getClass().clear();
    tcpClient.clear();
    emit sendConnectNumSignal(tcpClient.count());
    emit clearLineEdit();
}
