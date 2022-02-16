#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>
#include <QVariant>
#include "constant.h"

class TcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpSocket(qintptr socketDescriptor, QObject *parent = nullptr);
    ~TcpSocket();

signals:
    void sockDisConnect(qint64, const QString &, quint16, QThread *);

    void sendStrutData(QByteArray,int);

    void sendDisConnectSignal(int);

public slots:
    void disConTcp(qint64 socketDescriptor);
private slots:
    void OnReadyRead();

    void onSlot(int a);
public:
    bool findhead(QByteArray &buffer, int &index);
private:
    qintptr                 m_socketID;
    QMetaObject::Connection dis;
    QByteArray              m_datasBuff;
};

#endif // TCPSOCKET_H
