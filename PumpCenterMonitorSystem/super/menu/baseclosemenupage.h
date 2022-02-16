/**
* @FileName             baseclosemenupage.h
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-09-28 14:53:40
* @Author               zhoumingjie
* @email
* @Create Date          2021-09-28 14:53:40
* @
*/
#ifndef BASECLOSEMENUPAGE_H
#define BASECLOSEMENUPAGE_H
#include "basemenupage.h"


class BaseCloseMenuPage : public BaseMenuPage
{
public:
    BaseCloseMenuPage(QWidget *parent = nullptr);

    virtual ~BaseCloseMenuPage();

    static BaseCloseMenuPage* instance();

    virtual void addWidget(QWidget *widget);

    QToolButton *closeButton;
private:
    static BaseCloseMenuPage* m_pInstance;

    //QWidget *m_oneInstance;

};

#define baseClosePage BaseCloseMenuPage::instance()

#endif // BASECLOSEMENUPAGE_H
