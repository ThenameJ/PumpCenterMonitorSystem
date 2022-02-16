#include "dbmanager.h"
#include <QMutex>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include "constant.h"
#include <QDateTime>

Q_GLOBAL_STATIC(QMutex, createLock)
DBManager *DBManager::m_pInstance = nullptr;

DBManager::DBManager(QObject *parent) : IManager(parent)
{
}

void DBManager::init(DBManager *me, const QEvent *ev)
{
    switch ((int)ev->type())
    {
        case EV_Init:
            {
                me->createDataBase();
                me->transform(MANAGER_TRANS(&DBManager::worker));
            } break;
        default:
            break;
    }
}

DBManager::~DBManager()
{

}


DBManager *DBManager::instance()
{
    if (!m_pInstance)
    {
        QMutexLocker locker(createLock());
        if (!m_pInstance)
        {
            m_pInstance = new DBManager(nullptr);
        }
    }
    return m_pInstance;
}

void DBManager::start()
{
    subscribe(EV_Init);
    subscribe(EV_CreateTable);
    subscribe(EV_DataInsert);
    subscribe(EV_DataExport);
    subscribe(EV_Quit);
    transform(MANAGER_TRANS(&DBManager::init));
}


void DBManager::worker(DBManager *me, const QEvent *ev)
{
    switch ((int)ev->type())
    {
        case EV_Quit:
            me->transform(MANAGER_TRANS(&IManager::quit));
            break;

        case EV_DataInsert:
        {
            VariantEv *p = (VariantEv*)ev;
            databuf patientInfo = p->var.value<databuf>();
            me->insertData(patientInfo);
        }
            break;
        case EV_DataExport:
        {

        }
            break;
        default:
            break;
    }
}

void DBManager::createDataBase()
{
//    qDebug() << "ssssssssssssssssss";

    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("patientInfo.db");
    }
    if(!database.open())
    {
        return ;
    }

    QSqlQuery query;
    query.exec("create table patientinfo ("
               "id INTEGER primary key AUTOINCREMENT,"
               "record VARCHAR(40) NOT NULL,"
               "deviceId INTEGER NOT NULL, "
               "symptoms VARCHAR(40) NOT NULL, "
               "patientName VARCHAR(40) NOT NULL, "
               "sex VARCHAR(40) NOT NULL, "
               "height VARCHAR(40) , "
               "weight VARCHAR(40) , "
               "age VARCHAR(40) NOT NULL)");
    query.exec("create table deviceinfo ("
               "id INTEGER primary key AUTOINCREMENT,"
               "deviceId INTEGER NOT NULL, "
               "pumpTime VARCHAR(40) NOT NULL ,"
               "drugName VARCHAR(40) NOT NULL)");
}

void DBManager::insertData(databuf info)
{

    QString insert = QString("INSERT INTO patientinfo (id,record,deviceId,symptoms,patientName,sex,height,weight,age) "
                             "VALUES(NULL,'%1',%2,'%3','%4','%5','%6','%7','%8')")
            .arg(setRecord(info)).arg(info.deviceId).arg(info.symptoms).arg(info.patientName)
            .arg(info.sex).arg(info.height).arg(info.weight).arg(info.age);
//    qDebug() << insert;
    QSqlQuery query;
    query.exec(insert);

    QString insertDevice = QString("INSERT INTO deviceinfo (id,deviceId,pumpTime,drugName)"
                             "VALUES(NULL,%1,'%2','%3')").arg(info.deviceId).arg(info.pumpTime).arg(info.drugName);
    query.exec(insertDevice);
}

databuf DBManager::getData(int deviceId)
{
    QSqlQuery query;
    QString get = QString("select * from patientinfo where deviceId = %1").arg(deviceId);
    query.exec(get);
    databuf getInfo;
    while(query.next())
    {
        getInfo.deviceId = query.value(2).toInt();
        getInfo.symptoms = query.value(3).toString();
        getInfo.patientName = query.value(4).toString();
        getInfo.sex = query.value(5).toString();
        getInfo.height = query.value(6).toString();
        getInfo.weight = query.value(7).toString();
        getInfo.age = query.value(8).toString();
    }
    return getInfo;
}

QString DBManager::setRecord(databuf info)
{
    QString sort;
    QString deviceId;
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyyMMddhh");
    if( info.symptoms == "破伤风" || info.symptoms == "术后治疗")
    {
        sort = "A";
    }
    else
    {
        sort = "B";
    }
    if(info.deviceId < 10)
    {
        deviceId = QString("0%1 0%2").arg(info.deviceId).arg(info.deviceId);
        deviceId.remove(QRegExp("\\s"));//去除空格
    }
    else
    {
        deviceId = QString("%1%2").arg(info.deviceId).arg(info.deviceId);
    }
    QString record = QString("%1%2%3").arg(sort).arg(current_date).arg(deviceId);
    return record;
}





