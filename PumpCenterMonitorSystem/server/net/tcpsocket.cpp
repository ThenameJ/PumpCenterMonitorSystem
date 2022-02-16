#include "tcpsocket.h"
#include "uimanager.h"
#include <QBuffer>
#include <QString>
#include <QThread>
#include <QHostAddress>

#define AC 0XAC

TcpSocket::TcpSocket(qintptr socketDescriptor, QObject *parent)
    : QTcpSocket(parent), m_socketID(socketDescriptor)
{
    qRegisterMetaType<QByteArray>("qbytearray");
    this->setSocketDescriptor(socketDescriptor);
    connect(this,SIGNAL(readyRead()),this,SLOT(OnReadyRead()));
    connect(this,&QTcpSocket::disconnected,[&](){
        emit sockDisConnect(m_socketID,this->peerAddress().toString(),this->peerPort(),QThread::currentThread());//发送断开连接的用户信息
        this->deleteLater();
        int m = m_socketID;
        emit sendDisConnectSignal(m);
    });
    QByteArray connectSignal;
    QString socketId = QString("%1").arg(m_socketID);
    connectSignal.append(socketId);
    write(connectSignal);
    connect(this,SIGNAL(sendStrutData(QByteArray,int)),uimanager,SIGNAL(sendStrutData(QByteArray,int)));
    connect(this,SIGNAL(sendDisConnectSignal(int)),uimanager,SIGNAL(sendDisConnectSignal(int)));
    connect(uimanager,SIGNAL(disConnectSig(int)),this,SLOT(onSlot(int)));
}

TcpSocket::~TcpSocket()
{

}

void TcpSocket::disConTcp(qint64 socketDescriptor)
{
    if (socketDescriptor == m_socketID)
    {
        this->disconnectFromHost();
    }
    else if (socketDescriptor == -1) //-1为全部断开
    {
        disconnect(dis); //先断开连接的信号槽，防止二次析构
        this->disconnectFromHost();
        this->deleteLater();
    }
}

void TcpSocket::OnReadyRead()
{
    QByteArray buffer = readAll();

#if 0
    int index = 0;
    while(findhead(buffer,index))
    {
        buffer.remove(0,index);
//        char* ptr = buffer.data();
//        quint32 length;
//        memcpy(&length,ptr+4,sizeof(length));
//        //  qDebug()<<"length:"<<length;
//        if(length<buffer.size())
//            return;
//        quint32 type;
//        memcpy(&type,ptr+8,sizeof(type));
        buffer.remove(0,12);//去除无效报文，将头和长度类型去掉
        //发送报文
//        QBuffer buf(&buffer);
//        buf.open(QIODevice::ReadOnly);
//        QDataStream in(&buf);
//        databuf struct_data;
//        in >> struct_data;

//        qDebug() << struct_data.deviceId << struct_data.drugName << struct_data.pumpTime << struct_data.symptoms << struct_data.patientName << struct_data.sex
//                 << struct_data.height << struct_data.weight << struct_data.age;



emit sendStrutData(buffer,m_socketID);
//        if(struct_data.deviceId != 0 || struct_data.drugName != Q_NULLPTR || struct_data.pumpTime != 0)
//        {

//        }
    }
//    emit signalTcpSocketReadData(buffer);
#endif
    if(buffer[0] == AC)
    {
        QByteArray bufferData = buffer.mid(6,buffer.length()-7);
        emit sendStrutData(bufferData,m_socketID);
    }
    else
    {
        disConTcp(m_socketID);
    }
}


void TcpSocket::onSlot(int a)
{
    qint64 ab = a;
    disConTcp(ab);
}


bool TcpSocket::findhead(QByteArray &buffer, int &index)
{
    char * ptr = buffer.data();

    if(buffer.size() < 4)
    {
        return false;
    }
    for(int i = 0;i<buffer.size()-4;i++)
    {
        if(ptr[i] == '@' && ptr[i+1]== '@' && ptr[i+2] == '&' && ptr[i+3]=='&')//找到帧头
        {
            index = i;
            return true;
        }
    }
    return false;
}

