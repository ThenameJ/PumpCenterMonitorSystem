/**
* @FileName             baseclosemenupage.cpp
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-09-28 14:54:18
* @Author               zhoumingjie
* @email
* @Create Date          2021-09-28 14:54:18
* @
*/
#include "baseclosemenupage.h"
#include "uimanager.h"
#include <QMutex>



Q_GLOBAL_STATIC(QMutex, lock)
BaseCloseMenuPage* BaseCloseMenuPage::m_pInstance = nullptr;
BaseCloseMenuPage::BaseCloseMenuPage(QWidget *parent) : BaseMenuPage(parent)
{

//    setAttribute(Qt::WA_DeleteOnClose,true);
    closeButton = new QToolButton();
    closeButton->setFixedSize(40,40);
    closeButton->setIconSize(QSize(26, 26));
    closeButton->setIcon(uimanager->getResource()->pixmap(Cms::Res::IMAGE_Close));
    closeButton->setStyleSheet("QToolButton{border-style: flat;background: transparent;}");

    connect(closeButton,SIGNAL(clicked(bool)),this,SLOT(close()));
    this->m_newTitleBar->layout()->addWidget(closeButton);
    this->m_newTitleBar->m_topInfoLabel->setGeometry(0,0,rect().width()-40 ,40);

}

BaseCloseMenuPage::~BaseCloseMenuPage()
{
    m_pInstance = nullptr;
}

BaseCloseMenuPage *BaseCloseMenuPage::instance()
{
    if(!m_pInstance)
    {
        QMutexLocker locker(lock());
        if(!m_pInstance)
        {
            m_pInstance = new BaseCloseMenuPage();
        }
    }
    return m_pInstance;
}

void BaseCloseMenuPage::addWidget(QWidget *widget)
{
    widget->setFixedHeight(widget->height()-40);
    this->layout()->addWidget(widget);
}


