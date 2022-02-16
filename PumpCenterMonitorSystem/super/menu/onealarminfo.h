/**
* @FileName             onealarminfo.h
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-11-09 10:13:07
* @Author               zhoumingjie
* @email
* @Create Date          2021-11-09 10:13:07
* @
*/
#ifndef ONEALARMINFO_H
#define ONEALARMINFO_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QHBoxLayout>
#include <QMouseEvent>

class OneAlarmInfo : public QWidget
{
    Q_OBJECT
public:
    explicit OneAlarmInfo(QWidget *parent = nullptr);

    virtual ~OneAlarmInfo();

    void createLineWidget();

    void setColor(const QColor &color);

    QColor getColor();

    void setRoomInfo(const QString &roomInfo);

    QString getRoomInfo();

    void setTimeLeft(const int &timeLeft);

    int getTimeLeft();

    void setDeviceId(int deviceId);

    void setAlarmInfo(const QString &alarmInfo);

protected:
    virtual void paintEvent(QPaintEvent *event);

    virtual void resizeEvent(QResizeEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void mouseReleaseEvent(QMouseEvent *event);
signals:
    void checkPatientInfo(int);

    void updateUi();
public slots:

private:
    QColor alarmColor = Q_NULLPTR;

    QString m_roomInfo = Q_NULLPTR;

    QLabel *m_roomInfoLabel;

    QLabel *m_alarmInfoLabel;

    int m_timeLeft = 0;

    bool m_mousePressed = false;

    int m_deviceId = 0;
};

#endif // ONEALARMINFO_H
