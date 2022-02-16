/**
* @FileName             myshowhidebutton.cpp
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-11-09 10:14:16
* @Author               zhoumingjie
* @email
* @Create Date          2021-11-09 10:14:16
* @
*/
#include "myshowhidebutton.h"

MyShowHideButton::MyShowHideButton(QWidget *parent) : QPushButton(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setFocusPolicy(Qt::NoFocus);
}

void MyShowHideButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->hide();
}
