/**
* @FileName             pumpstate.h
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-09-14
* @Author               zhoumingjie
* @email
* @Create Date          2021-09-14
* @
*/
#ifndef PUMPSTATE_H
#define PUMPSTATE_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <math.h>
#include <QPushButton>
#include <QMouseEvent>
#include <QList>

class PumpState : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ getColor WRITE setColor)

public:
    PumpState(QWidget *parent = 0);
    virtual ~PumpState();



private slots:
    void onTimeOut();

    void onAlarmTimeOut();

protected:
    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseDoubleClickEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

private:
    /**
     * @brief drawBody
     * @param painter
     * @param rect
     */
    void drawBody(QPainter *painter, const QRect &rect);
    /**
     * @brief drawRect
     * @param painter
     * @param rect
     */
    void drawRect(QPainter *painter, const QRect &rect);
    /**
     * @brief drawOthers
     * @param painter
     * @param rect
     */
    void drawOthers(QPainter *painter, const QRectF &rect);
    /**
     * @brief drawCricle
     * @param painter
     * @param rect
     */
    void drawCricle(QPainter *painter, const QRect &rect);
    /**
     * @brief drawTriangle
     * @param painter
     * @param polygon
     */
    void drawTriangle(QPainter *painter,const QPolygonF &polygon);
    /**
     * @brief drawScale
     * @param painter
     * @param p
     */
    void drawScale(QPainter *painter , QPointF &p);
    /**
     * @brief drawWhiteFrame
     * @param painter
     * @param rect
     */
    void drawWhiteFrame(QPainter *painter, const QRect &rect);
    /**
     * @brief drawChangeBody
     * @param painter
     * @param rect
     */
    void drawChangeBody(QPainter *painter,const QRect &rect);
    /**
     * @brief drawWorld
     * @param painter
     * @param world
     * @param rect
     */
    void drawWorld(QPainter *painter, const QString &world, const QRect &rect);
    /**
     * @brief drawBedInfo
     * @param painter
     * @param rect
     * @param world
     */
    void drawBedInfo(QPainter *painter, const QRect &rect, const QString &world);
    /**
     * @brief drawTimeInfo
     * @param painter
     * @param world
     * @param rect
     */
    void drawTimeInfo(QPainter *painter, const QString &world, const QRect &rect);
    /**
     * @brief getColor
     * @return
     */
    QColor getColor() const;



public:
    /**
     * @brief setPumpTime
     * @param time
     */
    void setPumpTime(int time);
    /**
     * @brief setDeviceId
     * @param id
     */
    void setDeviceId(int id);
    /**
     * @brief getDeviceId
     * @return
     */
    int getDeviceId() const;

    void setRoomInfo(const QString &roomInfo);

    QString getRoomInfo();

    void setDragName(const QString &dragName);

    QString getDragName();

    void setSockectId(const int &sockectId);

    int getSockectId();

public slots:
    /**
     * @brief setColor
     * @param color
     */
    void setColor(const QColor &color);

    void onSlotUpdate();
signals:
    void checkPatientInfo(int);

    void openConfig(int);

    void sendOpenRightWin();

    void sendIdAndColor(int, QColor, int);

    void sendSortSignal();

    void sendOverSignal();

    void sendOpenAlarm(int, bool);

private:
    QTimer              *m_timer = Q_NULLPTR;
    QTimer              *m_alarmTimer = Q_NULLPTR;
    QColor              m_color = Q_NULLPTR;
    int                 m_rectHeight;
    int                 m_rectWidth;
    int                 m_rangeW;
    int                 m_rangeY;
    int                 m_randn = 15;
    int                 m_deviceId = -1;
    double              m_unit;
    bool                m_isOver;
    bool                m_mousePressed = false;
    bool                m_mouseLeftPressed =false;
    bool                m_doublePressed = false;
    QString             m_roomInfo = Q_NULLPTR;
    QString             m_dragName = Q_NULLPTR;
    int                 m_sockectId;
//    QString             m_ = Q_NULLPTR;
//    QString             m_dragName = Q_NULLPTR;
//    QString             m_dragName = Q_NULLPTR;
//    QString             m_dragName = Q_NULLPTR;
//    QString             m_dragName = Q_NULLPTR;
//    QString             m_dragName = Q_NULLPTR;
};

#endif // PUMPSTATE_H
