/**
* @FileName             emptywindow.cpp
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-09-26 12:09:27
* @Author               zhoumingjie
* @email
* @Create Date          2021-09-26 12:09:27
* @
*/

#include "emptywindow.h"
#include "uimanager.h"

#include <QDebug>

EmptyWindow::EmptyWindow(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
    setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);

    this->installEventFilter(this);
    this->setFocusPolicy(Qt::StrongFocus);
    setMinimumSize(280,170);
//    m_lWorkMenuList << "add" << "close";

    connect(this,SIGNAL(emptyWinClicked()),uimanager,SIGNAL(sendEmptyWinDoubleClicked()));
    connect(this,SIGNAL(clearLineEdit()),uimanager,SIGNAL(clearLineEdit()));
    //connect(this,SIGNAL(rightOpenConfig()),uimanager,SIGNAL(recRightOpenConfig()));

}

EmptyWindow::~EmptyWindow()
{

}

void EmptyWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter paint(this);
    QPen pen;
    pen.setColor(Qt::black);
    paint.setPen(pen);
    //反锯齿
    paint.setRenderHint(QPainter::Antialiasing, true);
    paint.fillRect(rect(), QColor(40,40,40));

    if(m_bShowEmptyWin)
    {
        QPixmap map = uimanager->getResource()->pixmap(Cms::Res::IMAGE_EmptyBed);
        paint.drawPixmap(rect().center().x() - 8, rect().center().y() - 8, 16, 16, map);
    }

    if(hasFocus())
    {
        paint.save();
        paint.setPen(QPen(QColor(255,255,255),4,Qt::SolidLine));
        paint.drawRect(rect());
        uimanager->m_fousId = 0;
        emit clearLineEdit();
        paint.restore();
    }

    //m_bShowEmptyWin = false;

//    int w = rect().width();
//    int h = rect().height();
//    rangeW = w/3;
//    if(rangeW >= 150)
//    {
//        rangeW = 150;
//    }
//    else if(rangeW <= 120)
//    {
//        rangeW = 120;
//    }
//    rangeY = h/6;
//    if(rangeY >= 50)
//    {
//        rangeY = 50;
//    }
//    else if(rangeY <= 38)
//    {
//        rangeY = 38;
//    }
//    QRect bedInfoRect = QRect(3,3,rangeW*7/8,rangeY*2/3);

//    drawBedInfo(&paint,bedInfoRect,"Room??-??");


}

void EmptyWindow::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
//    if(event->button() == Qt::RightButton)
//    {
//        emit rightOpenConfig();
//    }


}


void EmptyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(m_mousePressed && rect().contains(event->pos()))
        emit emptyWinClicked();
    m_mousePressed = false;
    event->accept();
}


//void EmptyWindow::resizeEvent(QMouseEvent *event)
//{
//    Q_UNUSED(event);
//    createWorkerWin();

//}

void EmptyWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->buttons().testFlag(Qt::LeftButton))
    {
        m_mousePressed = rect().contains(event->pos());
    }
    event->accept();
}




//void EmptyWindow::createWorkerWin()
//{

//    int width = rect().width();
//    int height = rect().height();
//    QFont myfont = font();
//    myfont.setFamily("Arial");
//    MainMenu *workItems = new MainMenu(MenuStyle_Empty,this);

//    QPixmap map;
//    workItems->setMenuHead("ZMJ", map);
//    workItems->setMainMenuItems(createWorkMenuItems());
//    connect(workItems,&MainMenu::selectMenuItemIndex,[=](QString text)
//    {
//        int index = m_lWorkMenuList.indexOf(text);

//    });
//    workItems->setGeometry(3,3,rangeW*7/8,rangeY*2/3);
//    myfont.setBold(true);
//    myfont.setItalic(false);
//    myfont.setPixelSize(22);
//    workItems->setFont(myfont);
//}

//void EmptyWindow::drawBedInfo(QPainter *painter, const QRect &rect, const QString &world)
//{
//    painter->save();
//    painter->setBrush(QBrush(QColor(220,220,220)));
//    painter->setPen(Qt::NoPen);
//    painter->drawRoundRect(rect,5,5);

//    QPen pen;
//    pen.setColor(QColor(40, 40, 40));
//    painter->setPen(pen);
//    QFont mfont = painter->font();
//    mfont.setBold(true);
//    mfont.setPixelSize(rangeW/8);
//    painter->setFont(mfont);
//    painter->drawText(rect, Qt::AlignCenter, world);

//    painter->restore();
//}

//QList<MainMenuItemProperty> EmptyWindow::createWorkMenuItems()
//{
//    QList<MainMenuItemProperty> list;

//    MainMenuItemProperty add;
//    add.objName = getMenuIndexStr(workItem_Add);
//    add.title = "Add";
//    list.append(add);

//    MainMenuItemProperty close;
//    close.objName = getMenuIndexStr(workItem_Close);
//    close.title = "Close";
//    list.append(close);

//    return list;

//}

//QString EmptyWindow::getMenuIndexStr(const workWinItems index)
//{
//    if (index < 0 || index >= m_lWorkMenuList.size())
//    {
//        return "Null";
//    }
//    return m_lWorkMenuList.at(index);
//}
