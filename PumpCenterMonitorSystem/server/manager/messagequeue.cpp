#include "messagequeue.h"
#include <QCoreApplication>
#include <QDebug>

MessageQueue::MessageQueue(QObject *parent)
    : QObject(parent)
{

}

MessageQueue::~MessageQueue()
{

}

void MessageQueue::publish(int id, const QEvent* event)
{
    QMutexLocker locker(&mutex);

    CustomEvent* e = (CustomEvent*)event;
    if (e == nullptr)
        return;

    if (subscriber.contains(id))
    {
        QList<QObject*> value = subscriber.value(id);
        foreach (QObject* v, value)
        {
            QCoreApplication::postEvent(v, e->clone());
        }
    }

    delete event;
    event = Q_NULLPTR;
}

void MessageQueue::publish(QObject *obj, int id, const QEvent *event)
{
    QMutexLocker locker(&mutex);

    CustomEvent* e = (CustomEvent*)event;
    if (e == nullptr)
        return;

    if (subscriber.contains(id))
    {
        QList<QObject*> value = subscriber.value(id);
        foreach (QObject* v, value)
        {
            if (v == obj)
                QCoreApplication::postEvent(v, e->clone());
        }
    }

    delete event;
    event = Q_NULLPTR;
}

void MessageQueue::subscribe(int id, QObject* who)
{
    QMutexLocker locker(&mutex);

    if (who == nullptr)
        return;

    if (subscriber.contains(id))
    {
        QList<QObject*> value = subscriber.value(id);/*赋值事件ID给列表对象中的对象*/
        if (value.contains(who))
            return;/*如果对象列表中包含了这个对象就return*/

        value.push_back(who);/*等同于append（value）*/
        subscriber.insert(id, value);/*插入键事件ID，值IManger对象*/
        return;
    }

    QList<QObject*> value;
    value.push_back(who);
    subscriber.insert(id, value);
}
