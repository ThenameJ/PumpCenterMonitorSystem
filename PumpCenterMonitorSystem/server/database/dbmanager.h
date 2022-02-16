#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "imanager.h"
#include <QObject>
#include "constant.h"
#include <QSqlDatabase>

class DBManager : public IManager
{
    Q_OBJECT
    Q_DISABLE_COPY(DBManager)
public:
    virtual ~DBManager();

    static DBManager *instance();

    virtual void start() Q_DECL_OVERRIDE;

    void createDataBase();

    void insertData(databuf info);

    databuf getData(int deviceId);

    QString setRecord(databuf info);

protected:
    explicit DBManager(QObject *parent = nullptr);

    /**
     * @brief init 初始化状态函数
     * @param me
     * @param ev
     */
    static void init(DBManager *me, QEvent const *ev);

    /**
     * @brief worker 工作状态函数
     * @param me
     * @param ev
     */
    static void worker(DBManager *me, QEvent const *ev);


private:
    QSqlDatabase database;
    static DBManager                       *m_pInstance;
};

#define dbmanager DBManager::instance()

#endif // DBMANAGER_H
