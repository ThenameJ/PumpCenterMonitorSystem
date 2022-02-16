/**
* @FileName             interfacetopbar.cpp
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-08-20
* @Author               luteng
* @email
* @Create Date          2021-08-20
* @
*/
#include "interfacetopbar.h"
#include "mainmenu.h"
#include "linewidget.h"
#include "uimanager.h"
#include <QDateTime>
#include <QPainter>
#include <QPen>
#include <QFont>

InterfaceTopBar::InterfaceTopBar(QWidget *parent) : QWidget(parent)
{
    MainMenu *mainMenu = new MainMenu(this);
    mainMenu->setGeometry(0,0,150,rect().height());
    connect(uimanager,SIGNAL(sendConnectNumSignal(int)),this,SLOT(onSlotSetConnectNum(int)));
}

InterfaceTopBar::~InterfaceTopBar()
{

}

void InterfaceTopBar::updateSysTime()
{
    update();
}

void InterfaceTopBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing, true);
    QLinearGradient linearGradient(rect().topLeft(), rect().bottomLeft());
    linearGradient.setColorAt(0.0, QColor(60, 60, 60));
    linearGradient.setColorAt(1.0, QColor(10, 10, 10));
    painter.setBrush(QBrush(linearGradient));
    painter.setPen(Qt::NoPen);
    painter.drawRoundRect(rect(), 5, 5);
    //
    paintTime(&painter, QRect(rect().right() - 300, rect().top(), 300, rect().height()));
    paintHospitalInfo(&painter,QRect(rect().right()/2 - 150, rect().top(), 300, rect().height()));

    paintDeviceNum(&painter,QRect(rect().right()/4-390, rect().top(), 300, rect().height()+14));

}

void InterfaceTopBar::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    createBoundary();

}

void InterfaceTopBar::paintTime(QPainter *painter, const QRect &rect)
{
    if (painter == Q_NULLPTR)
        return;

    painter->save();

    QPen pen;
    pen.setColor(QColor(250, 250, 250));
    painter->setPen(pen);
    QFont mfont = painter->font();
    mfont.setBold(true);
    mfont.setPixelSize(20);
    painter->setPen(pen);
    painter->setFont(mfont);
    painter->drawText(rect, Qt::AlignCenter, QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    painter->restore();
}



void InterfaceTopBar::paintHospitalInfo(QPainter *painter, const QRect &rect)
{
    if(painter == Q_NULLPTR)
    {
        return ;
    }
    painter->save();
    QPen pen;
    pen.setColor(QColor(250,250,250));
    painter->setPen(pen);
    QFont mfont = painter->font();
    mfont.setBold(true);
    mfont.setPixelSize(20);
    //painter->setPen(pen);
    painter->setFont(mfont);
    painter->drawText(rect, Qt::AlignCenter, "XX省XX市第一人民医院");
    painter->restore();
}

void InterfaceTopBar::paintDeviceNum(QPainter *painter, const QRect &rect)
{
    if(painter == Q_NULLPTR)
    {
        return ;
    }
    painter->save();
    QPen pen;
    pen.setColor(QColor(250,250,250));
    painter->setPen(pen);
    QFont mfont = painter->font();
    mfont.setBold(true);
    mfont.setPixelSize(16);
    painter->setFont(mfont);
    painter->drawText(rect, Qt::AlignCenter, QString("当前设备连接数：%1").arg(m_connectNum));
    painter->restore();
}

void InterfaceTopBar::createBoundary()
{
    //画BLT右边的分界线
    int left = rect().left();
    int top = rect().top();
    int height = rect().height();
    left += 150;
    LineWidget *line = new LineWidget(Line_V, this);
    line->setGeometry(left, top, 2, height);
}

void InterfaceTopBar::onSlotSetConnectNum(int connectNum)
{
    if(m_connectNum != connectNum)
    {
        m_connectNum = connectNum;
    }
    update();
}
