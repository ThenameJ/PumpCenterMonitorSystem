#ifndef EVENTID_H
#define EVENTID_H

#include <QEvent>

enum
{
    EV_Start = QEvent::User,
    EV_Init,
    EV_Quit,
    EV_SystemPowerOffResponse,          //软件关机时 模块响应


    //DB
    EV_CreateTable,
    EV_DataInsert,                  //数据插入
    EV_DataExport,                  //数据导出


    EV_MAX
};

#endif // EVENTID_H
