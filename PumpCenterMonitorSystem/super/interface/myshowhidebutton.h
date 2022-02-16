/**
* @FileName             myshowhidebutton.h
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-11-09 10:14:20
* @Author               zhoumingjie
* @email
* @Create Date          2021-11-09 10:14:20
* @
*/
#ifndef MYSHOWHIDEBUTTON_H
#define MYSHOWHIDEBUTTON_H

#include <QWidget>
#include <QPushButton>

class MyShowHideButton : public QPushButton
{
    Q_OBJECT
public:
    MyShowHideButton(QWidget *parent = nullptr);

protected:
    virtual void leaveEvent(QEvent *event);

};

#endif // MYSHOWHIDEBUTTON_H
