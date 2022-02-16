/**
* @FileName             monitortimeleftlist.cpp
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-08-20
* @Author               luteng
* @email
* @Create Date          2021-08-20
* @
*/
#include "monitortimeleftlist.h"
#include "patientinfowin.h"
#include "uimanager.h"
#include "basemenupage.h"
#include "alarminfopage.h"

MonitorTimeLeftList::MonitorTimeLeftList(QWidget *parent) : QWidget(parent)
{
    QPalette pe;
    pe.setColor(QPalette::Background, Qt::gray);
    setAutoFillBackground(true);
    setPalette(pe);
    initSpace();
    connect(uimanager,SIGNAL(sendHideRightWindow()),this,SLOT(onSlotShowHideRightWindow()));
    connect(uimanager,SIGNAL(sendEmptyWinDoubleClicked()),this,SLOT(onSlotShowRightWindow()));
    connect(uimanager,SIGNAL(sendOpenRightWin()),this,SLOT(onSlotShowRightWindow()));
    connect(uimanager,SIGNAL(sendOverSignal()),this,SLOT(onSlotShowRightWindow()));
    connect(this,SIGNAL(sendShowHideSignal(bool)),uimanager,SIGNAL(sendShowHideSignal(bool)));
    hide();
}

MonitorTimeLeftList::~MonitorTimeLeftList()
{

}

void MonitorTimeLeftList::initSpace()
{
    PatientInfoWin *patientInfo = new PatientInfoWin();

    AlarmInfoPage *alarmInfo = new AlarmInfoPage();

    QVBoxLayout *vLayout = new QVBoxLayout();

    vLayout->setSpacing(0);
    vLayout->setMargin(0);
    vLayout->addWidget(patientInfo);
    vLayout->addWidget(alarmInfo);

    if(layout())
        delete layout();

    setLayout(vLayout);
}

void MonitorTimeLeftList::onSlotShowRightWindow()
{
    show();
    if(isChange)
        emit sendShowHideSignal(isChange);
    isChange = false;

}

void MonitorTimeLeftList::onSlotShowHideRightWindow()
{
    if(!isChange)
    {
        hide();
    }
    else
    {
        show();
    }
    emit sendShowHideSignal(isChange);
    isChange = !isChange;
}
