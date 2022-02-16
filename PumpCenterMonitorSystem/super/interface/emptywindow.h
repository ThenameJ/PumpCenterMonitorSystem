/**
* @FileName             emptywindow.h
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-09-26 12:09:17
* @Author               zhoumingjie
* @email
* @Create Date          2021-09-26 12:09:17
* @
*/

#ifndef EMPTYWINDOW_H
#define EMPTYWINDOW_H
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>

//#include "mainmenu.h"

//enum workWinItems
//{
//    workItem_Add = 0,
//    workItem_Close,
//    workItem_Max,
//};

class EmptyWindow : public QWidget
{
    Q_OBJECT
public:
    EmptyWindow(QWidget *parent = 0);
    virtual ~EmptyWindow();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

//    void resizeEvent(QMouseEvent *event);

signals:
    void emptyWinClicked();
    void rightOpenConfig();
    void clearLineEdit();

private:
//    void createWorkerWin();
//    void drawBedInfo(QPainter *painter, const QRect &rect, const QString &world);
//    QList<MainMenuItemProperty> createWorkMenuItems();
//    QString getMenuIndexStr(const workWinItems index);


private:
    bool m_mousePressed = false;
    bool m_bShowEmptyWin = true;
    bool m_bWhiteFrame = false;
//    QList<QString> m_lWorkMenuList;
//    int rangeW;
//    int rangeY;
};


#endif // EMPTYWINDOW_H
