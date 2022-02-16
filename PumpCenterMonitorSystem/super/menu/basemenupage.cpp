/**
* @FileName             basemenupage.cpp
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-09-28 14:54:02
* @Author               zhoumingjie
* @email
* @Create Date          2021-09-28 14:54:02
* @
*/
#include "basemenupage.h"
#include "uimanager.h"

BaseMenuPage::BaseMenuPage(QWidget *parent) : QWidget(parent)
{
    QPalette pe;
    pe.setColor(QPalette::Background, QColor(220,220,220));
    setAutoFillBackground(true);
    setPalette(pe);

    mainLayout = new QVBoxLayout;

    m_newTitleBar = new BaseTitleBar();
    m_newTitleBar->setTitleText("NULL");
    mainLayout->setMargin(1);
    mainLayout->setSpacing(1);
    mainLayout->addWidget(m_newTitleBar);
    mainLayout->addStretch();

    //content->setFixedHeight(content->height()-40);
    //mainLayout->addWidget(content);

    if(layout())
        delete layout();

    setLayout(mainLayout);
}

BaseMenuPage::~BaseMenuPage()
{
}

void BaseMenuPage::addWidget(QWidget *widget)
{
    mainLayout->addWidget(widget);
}


/********************************************************************/




BaseTitleBar::BaseTitleBar(QWidget *parent) : QWidget(parent)
{
    QPalette pe;
    pe.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pe);

    QWidget *topBar = new QWidget();
    topBar->setFixedHeight(40);
    topBar->setStyleSheet("background-color:rgb(100,100,100);");
    QHBoxLayout *toplayout = new QHBoxLayout();

    m_topInfoLabel = new QLabel(topBar);
    m_topInfoLabel->setStyleSheet("color:white");


//    QToolButton *closeButton = new QToolButton();
//    closeButton->setFixedSize(40,40);
//    closeButton->setIconSize(QSize(26, 26));
//    closeButton->setIcon(uimanager->getResource()->pixmap(Cms::Res::IMAGE_Close));
//    closeButton->setStyleSheet("QToolButton{border-style: flat;background: transparent;}");

    toplayout->addWidget(topBar);
//    toplayout->addWidget(closeButton);
    toplayout->setMargin(0);
    toplayout->setSpacing(0);

    if(layout())
        delete layout();

    setLayout(toplayout);
}

BaseTitleBar::~BaseTitleBar()
{

}

void BaseTitleBar::setTitleText(const QString &text)
{
    m_titleInfo = text;
    m_topInfoLabel->setText(m_titleInfo);
    m_topInfoLabel->setAlignment(Qt::AlignCenter);
}

void BaseTitleBar::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    m_topInfoLabel->setGeometry(0,0,rect().width(),40);
}
