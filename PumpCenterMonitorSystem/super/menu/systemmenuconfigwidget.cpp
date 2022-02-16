/**
* @FileName             systemmenuconfigwidget.cpp
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-09-28 14:55:16
* @Author               zhoumingjie
* @email
* @Create Date          2021-09-28 14:55:16
* @
*/
#include "systemmenuconfigwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include "departmentconfig.h"
#include <QMutex>
#include <alarmvoicepage.h>
#include "historypage.h"


Q_GLOBAL_STATIC(QMutex, lock)
SystemMenuConfigWidget* SystemMenuConfigWidget::m_pInstance = nullptr;
SystemMenuConfigWidget::SystemMenuConfigWidget(QWidget *parent) : BaseCloseMenuPage(parent)
{

    //setWindowModality(Qt::ApplicationModal); //窗口置顶并阻塞
    setAttribute(Qt::WA_DeleteOnClose,true);


    QWidget *widget = new QWidget();
    widget->resize(800,700);
    configList = new QListWidget(this);
    configList->addItem(new QListWidgetItem(tr("输注设置")));
    configList->addItem(new QListWidgetItem(tr("本地设置")));
    configList->addItem(new QListWidgetItem(tr("病人资料")));
    configList->addItem(new QListWidgetItem(tr("房间")));

    QVBoxLayout *vlayout = new QVBoxLayout;
    m_demo = new QStackedWidget();
    QLabel *lable1 = new QLabel(tr("待开发。。。"));
    lable1->setAlignment(Qt::AlignCenter);
//    QLabel *lable2 = new QLabel(tr("Window2"));
//    lable2->setAlignment(Qt::AlignCenter);
    m_demo->addWidget(lable1);

    //本地设置
    AlarmVoicePage *alarmVoicePage = new AlarmVoicePage();
    m_demo->addWidget(alarmVoicePage);

    //病人资料
//    QLabel *lable3 = new QLabel(tr("Window3"));
//    lable3->setAlignment(Qt::AlignCenter);
//    m_demo->addWidget(lable3);
    HistoryPage *history = new HistoryPage();
    m_demo->addWidget(history);


    //科室设置
    DepartmentConfig *departmentConfig = new DepartmentConfig();
    m_demo->addWidget(departmentConfig);
    connect(departmentConfig,SIGNAL(sendCloseSignal()),this,SLOT(close()));

    //
    connect(configList,SIGNAL(currentRowChanged(int)),m_demo,SLOT(setCurrentIndex(int)));

    connect(m_demo,&QStackedWidget::currentChanged,[=](int x){
        if(x == 3 || x == 2)
        {
            if(!isReinstated)
            {
                password = new PermissionsPage(this);
                connect(password->closeButton,SIGNAL(clicked(bool)),this,SLOT(onSlotReinstated()));
                connect(password,SIGNAL(changePermissionSig(bool)),this,SLOT(onSlotChangePermission(bool)));
                password->show();
            }
        }
    });
    vlayout->addWidget(m_demo);

    QHBoxLayout *hlayout = new QHBoxLayout;

    hlayout->addWidget(configList);
    hlayout->addLayout(vlayout);
    hlayout->setStretchFactor(configList,1);
    hlayout->setStretchFactor(vlayout,4);
    widget->setLayout(hlayout);
    this->addWidget(widget);
//    if(layout())
//        delete layout();
//    setLayout(hlayout);

}

SystemMenuConfigWidget::~SystemMenuConfigWidget()
{
    m_pInstance = nullptr;
}

SystemMenuConfigWidget *SystemMenuConfigWidget::instance()
{
    if(!m_pInstance)
    {
        QMutexLocker locker(lock());
        if(!m_pInstance)
        {
            m_pInstance = new SystemMenuConfigWidget();
        }
    }
    return m_pInstance;
}

void SystemMenuConfigWidget::setInitItem()
{
    configList->setCurrentRow(0);
}

void SystemMenuConfigWidget::onSlotReinstated()
{
    setInitItem();
    disconnect(password->closeButton,SIGNAL(clicked(bool)),this,SLOT(onSlotReinstated()));
    delete password;
}


void SystemMenuConfigWidget::onSlotChangePermission(bool Reinstat)
{
    if(isReinstated != Reinstat)
    {
        isReinstated = Reinstat;
    }
    disconnect(password,SIGNAL(changePermissionSig(bool)),this,SLOT(onSlotChangePermission(bool)));
}





