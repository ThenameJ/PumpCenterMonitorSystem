/**
* @FileName             mainmenu.cpp
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-09-25 14:48:33
* @Author               zhoumingjie
* @email
* @Create Date          2021-09-25 14:48:33
* @
*/
#include "mainmenu.h"
#include "uimanager.h"
#include <QDebug>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    initMenu();
}

MainMenu::~MainMenu()
{

}


void MainMenu::initMenu()
{

    m_pStatusButton = new QPushButton(this);
    m_pStatusButton->setGeometry(0,0,150,rect().height()*2-5);

    m_pStatusButton->setIconSize(QSize(24, 20));
    m_pStatusButton->setFont(font());
    m_pStatusButton->setStyleSheet("QPushButton{border-style:none;"
                                   "background:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop:0 rgb(60, 60, 60), stop: 1 rgb(10, 10, 10));"
//                                       "background:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop:0 rgb(66, 142, 230), stop: 1 rgb(50, 100, 200));"
                                   "color:white;border-radius:4;"
                                    "}"
                                    "QPushButton::menu-indicator{image:None;}"
                                    );

    m_pmainMenu = new QMenu(this);
    m_pmainMenu->setAttribute(Qt::WA_TranslucentBackground);
    m_pmainMenu->setStyleSheet(
                    "QMenu {\
                    background-color: #FFFFFF;    /* sets background of the menu 设置整个菜单区域的背景色，我用的是白色：white*/\
                    border: 2px solid QColor(40,40,40);    /*整个菜单区域的边框粗细、样式、颜色*/\
                    border-radius:1px;\
                    }"               
                    );


    QFontMetrics metrics(m_pStatusButton->font());
    QString tmpStr = metrics.elidedText("菜单", Qt::ElideRight, m_pStatusButton->width() - 10);
    m_pStatusButton->setText(tmpStr);
    m_pStatusButton->setIcon(uimanager->getResource()->pixmap(Cms::Res::IMAGE_Setting));


    //系统设置项
    MenuItemWidget* action = new MenuItemWidget(m_pStatusButton);
    action->setText(tr("系统设置"));
    action->setPixmap(uimanager->getResource()->pixmap(Cms::Res::IMAGE_Settings));
    action->setMinimumSize(200, 50);
    QWidgetAction *actionWidget = new QWidgetAction(m_pmainMenu);
    actionWidget->setDefaultWidget(action);
    m_pmainMenu->addAction(actionWidget);
    connect(action,SIGNAL(clicked()),uimanager,SIGNAL(sendOpenSystemConfig()));
    //分界线
    m_pmainMenu->addSeparator();
    //退出项
    MenuItemWidget* quitAction = new MenuItemWidget(m_pStatusButton);
    quitAction->setText(tr("关机"));
    quitAction->setPixmap(uimanager->getResource()->pixmap(Cms::Res::IMAGE_PowerOff));
    quitAction->setMinimumSize(200, 50);
    QWidgetAction *quitActionWidget = new QWidgetAction(m_pmainMenu);
    quitActionWidget->setDefaultWidget(quitAction);
    m_pmainMenu->addAction(quitActionWidget);
    connect(quitAction,SIGNAL(clicked()),uimanager,SIGNAL(sendCloseSignal()));


    m_pStatusButton->setMenu(m_pmainMenu);
}



MenuItemWidget::MenuItemWidget(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
}

MenuItemWidget::~MenuItemWidget()
{

}

void MenuItemWidget::setPixmap(const QPixmap &pix)
{
    m_pixmap = pix;
    update();
}


void MenuItemWidget::setText(const QString &text)
{
    m_text = text;
    update();
}


void MenuItemWidget::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    paint.setPen(Qt::NoPen);
    if (m_bEnter)
        paint.fillRect(event->rect(), QColor(100, 100, 100));
    else
        paint.fillRect(event->rect(), Qt::transparent);
    paint.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform, true);

    QRect pixRect = QRect(event->rect().left() + 15, event->rect().top() + (event->rect().height() - 28) / 2, 28, 28);
    QRect textRect = QRect(event->rect().left() + 80, event->rect().top(), event->rect().width() - 55, event->rect().height());
    paint.drawPixmap(pixRect, m_pixmap);
    QPen pen;
    paint.setPen(pen);
    paint.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, m_text);
    //

}


void MenuItemWidget::enterEvent(QEvent *event)
{
    if (m_bEnable)
    {
        m_bEnter = true;
        Q_UNUSED(event);
        update();
    }
}

void MenuItemWidget::leaveEvent(QEvent *event)
{
    m_bEnter = false;
    Q_UNUSED(event);
    update();
}

void MenuItemWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons().testFlag(Qt::LeftButton))
        m_mousePressed = rect().contains(event->pos());
    event->accept();
}

void MenuItemWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_mousePressed && rect().contains(event->pos()))
        emit clicked();

    m_mousePressed = false;
    event->accept();
}
