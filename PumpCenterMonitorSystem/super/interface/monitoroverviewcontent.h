/**
* @FileName             monitoroverviewcontent.h
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-08-20
* @Author               luteng
* @email
* @Create Date          2021-08-20
* @
*/
#ifndef MONITOROVERVIEWCONTENT_H
#define MONITOROVERVIEWCONTENT_H

#include <QWidget>
#include "pumpstate.h"
#include "uimanager.h"
#include "emptywindow.h"
#include "constant.h"
class MonitorOverViewContent : public QWidget
{
    Q_OBJECT
public:
    explicit MonitorOverViewContent(QWidget *parent = nullptr);

    virtual ~MonitorOverViewContent();
    /**
     * @brief initRandn
     * @return int
     */
    int initRandn();

protected:
    /**
     * @brief resizeEvent
     * @param event
     */
    virtual void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

    virtual void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

    virtual void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;

private:
    /**
     * @brief initContent
     */
    void initContent();

    void afterChangeWin();

    void clearMap(QMap<int, EmptyWindow*> &map);

    void clearMapTab(QMap<int, PumpState*> &map);

    void deleteWin(QLayout *layout);

    void numChange(const int &numOfPump, int &x, int &y, int &extra);

signals:
    void sendIsLeaveSignal(bool);

    void sendConnectNumSignal(int);

    void sendDisconnect(int);

    void sendCloseAlarm(int, bool);
private slots:
    void onSlotReciveNumSignal(int num);

    void onSlotSelfRowNum(int row,int line);

    void onSlotShowPumpConfig(int decviceId);

    void onSlotReciveParamSetting(ConfigInfo data);

    void onSlotReciveStrutData(QByteArray Data,int sockectId);

    void onSlotDisConnectClient(int deviceId);

private:
    int         m_newData_x;
    int         m_newData_y;
    int         m_newData_extra;
    int         m_pumpNum;
    int         m_index;
    QMap<int,PumpState*> m_MapTab;
    QMap<int,EmptyWindow*> m_Map;
    bool        m_isChange = false;
    bool        m_isLeave = false;
    QVBoxLayout *vlayout;
    int         m_connectNum = 0;
};

#endif // MONITOROVERVIEWCONTENT_H
