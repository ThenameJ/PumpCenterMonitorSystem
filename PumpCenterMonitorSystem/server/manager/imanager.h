#ifndef BASEMANAGER_H
#define BASEMANAGER_H

#include <QObject>
#include <QEvent>
#include "eventid.h"
#include "messagequeue.h"

//管理事务处理
#define MANAGER_TRANS(obj) (reinterpret_cast<IManager::CallFunc>(obj))
/*把对象类型转换*/
class IManager : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(IManager)
public:
    typedef void (*CallFunc)(void *me, QEvent const *event);

    explicit IManager(QObject *parent = nullptr);

    virtual ~IManager();

    virtual void start() = 0;

    void setMessageQueue(MessageQueue *q);

    MessageQueue *getMessageQueue() const;

    //订阅消息ID
    void subscribe(int id);

    void publish(int id, const QEvent* event);

    void publish(QObject *obj, int id, const QEvent* event);

protected:
    //注册回调函数
    void transform(void (*func)(void *me, const QEvent *event));

    static void quit(IManager *me, QEvent const *event);

    virtual void customEvent(QEvent *event);

private:
    CallFunc            callFunc;

    MessageQueue        *messageQ;
};

#endif // BASEMANAGER_H
