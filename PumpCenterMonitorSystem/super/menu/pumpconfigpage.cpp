/**
* @FileName             pumpconfigpage.cpp
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-09-26 15:59:26
* @Author               zhoumingjie
* @email
* @Create Date          2021-09-26 15:59:26
* @
*/
#include "pumpconfigpage.h"
#include "pumpparampage.h"
#include <QMutex>



Q_GLOBAL_STATIC(QMutex, lock)
PumpConfigPage* PumpConfigPage::m_pInstance = nullptr;
PumpConfigPage::PumpConfigPage(QWidget *parent) : BaseCloseMenuPage(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setAttribute(Qt::WA_QuitOnClose,false);
    PumpConfigPageInit();
    this->resize(800,700);
}

PumpConfigPage::~PumpConfigPage()
{
    m_pInstance = nullptr;
}

PumpConfigPage *PumpConfigPage::instance()
{
    if (!m_pInstance)
    {
        QMutexLocker locker(lock());
        if (!m_pInstance)
        {
            m_pInstance = new PumpConfigPage();
        }
    }
    return m_pInstance;
}

void PumpConfigPage::PumpConfigPageInit()
{
//    QPalette pe;
//    pe.setColor(QPalette::Background, QColor(100,100,100));
//    setAutoFillBackground(true);
//    setPalette(pe);
    this->setAttribute(Qt::WA_DeleteOnClose,true);

    QWidget *widget = new QWidget();
    widget->resize(800,700);
    m_tabWidget = new QTabWidget(this);
    m_tabWidget->setTabPosition(QTabWidget::North);
    m_tabWidget->setTabShape(QTabWidget::Triangular);
    m_tabWidget->setTabsClosable(false);


    m_tabWidget->addTab(new pumpParamPage(),tr("参数配置"));
    m_tabWidget->addTab(new QWidget(),tr("其他"));

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(m_tabWidget);
    widget->setLayout(hlayout);

    this->addWidget(widget);

}

void PumpConfigPage::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);//启动反锯齿
    painter.setPen(QPen(QColor(0,0,0),3));
    painter.drawRect(0,0,this->width(),this->height());
}
