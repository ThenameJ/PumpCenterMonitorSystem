/**
* @FileName             workingspace.h
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-08-20
* @Author               luteng
* @email
* @Create Date          2021-08-20
* @
*/
#ifndef WORKINGSPACE_H
#define WORKINGSPACE_H

#include <QWidget>
#include <QMap>
#include <QScrollArea>
#include <QWheelEvent>
#include "alarminfopage.h"
#include "myshowhidebutton.h"
class QTimer;
class WorkingSpace : public QWidget
{
public:
    enum SubItemIndex
    {
        SubItem_TopBar = 0,
        SubItem_OverView,
        SubItem_LeftTimeList,
        SubItem_Max
    };
    Q_OBJECT
public:
    explicit WorkingSpace(QWidget *parent = nullptr);

    virtual ~WorkingSpace();

protected:
    virtual void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    virtual void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

    virtual bool eventFilter(QObject *watched, QEvent *event);
private slots:
    /**
     * @brief onSlotTimeout
     */
    void onSlotTimeout();

    void onSlotShowHideSignal(bool value);

    void sltValueChangeWidget(int value);

    void sltHoriValueChangeWidget(int value);

    void onSlotIsLeaveSignal(bool isLeave);

    void onSlotRowNum(int row);
private:
    /**
     * @brief initSpace
     */
    void initSpace();

    void initButton();

private:
    QTimer                          *m_timer = Q_NULLPTR;
    QMap<SubItemIndex, QWidget*>    m_subItems;
    QScrollArea                     *scroll;
    SuspendedScrollBar              *m_pVertScrollBar;
    SuspendedScrollBar              *m_pHoriScrollBar;
    MyShowHideButton                *m_showHideButton;
    int distance = 0;
};

#endif // WORKINGSPACE_H
