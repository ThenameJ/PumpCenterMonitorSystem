/**
* @FileName             uibackgrounddatamanager.h
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-06-09
* @Author               luteng
* @email
* @Create Date          2021-06-09
* @
*/
#ifndef UIBACKGROUNDDATAMANAGER_H
#define UIBACKGROUNDDATAMANAGER_H

#include <QObject>
#include "imanager.h"

class QTimer;
class UIBackgroundDataManager : public IManager
{
    Q_OBJECT
    Q_DISABLE_COPY(UIBackgroundDataManager)
public:

    virtual ~UIBackgroundDataManager();

    static UIBackgroundDataManager *instance();

    virtual void start() Q_DECL_OVERRIDE;

protected:
    explicit UIBackgroundDataManager(QObject *parent = nullptr);

    /**
     * @brief init 初始化状态函数
     * @param me
     * @param ev
     */
    static void init(UIBackgroundDataManager *me, QEvent const *ev);

    /**
     * @brief worker 工作状态函数
     * @param me
     * @param ev
     */
    static void worker(UIBackgroundDataManager *me, QEvent const *ev);

private slots:
    void onslotTimerout();

private:
    void doStart();

private:
    QTimer                                      *m_timer = Q_NULLPTR;
    static UIBackgroundDataManager              *m_pInstance;
};
#define uibackgrounddata UIBackgroundDataManager::instance()

#endif // UIBACKGROUNDDATAMANAGER_H
