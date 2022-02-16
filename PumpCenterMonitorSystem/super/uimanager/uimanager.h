/**
* @FileName             uimanager.pri
* @Brief                摘要
* @Version              1.0.0
* @Current Maintainter  修改者
* @Update Date          2019-06-29
* @Author               luteng
* @email                luteng1230@163.com
* @Create Date          2019-06-29
* @
*/
#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <QObject>
#include <QTranslator>
#include <QRect>
#include "imanager.h"
#include "cmsresourcemanager.h"
#include "constant.h"
#include "pumpparampage.h"
#include <QSound>
#include <QTimer>

struct ShowMenuRectInfo
{
    QRect  invalidRect;     //全部区域
    int    paramWidth;      //菜单宽度
    int    waveHeight;      //波形高度
};

class UIConfigCache;
class UIManager : public IManager
{
    Q_OBJECT
    Q_DISABLE_COPY(UIManager)
public:
    virtual ~UIManager();

    static UIManager *instance();

    virtual void start() Q_DECL_OVERRIDE;

    /**
     * @brief getResource
     * @return
     */
    CMSResourceManager *getResource();

protected:
    explicit UIManager(QObject *parent = nullptr);

    /**
     * @brief init 初始化状态函数
     * @param me
     * @param ev
     */
    static void init(UIManager *me, QEvent const *ev);

    /**
     * @brief worker 工作状态函数
     * @param me
     * @param ev
     */
    static void worker(UIManager *me, QEvent const *ev);

signals:
    /**
     * @brief sendOpenRightWin
     */
    void sendOpenRightWin();
    /**
     * @brief sendOpenConfig
     */
    void sendOpenConfig(int);
    /**
     * @brief sendCloseSignal
     */
    void sendCloseSignal();
    /**
     * @brief sendOpenSystemConfig
     */
    void sendOpenSystemConfig();
    /**
     * @brief sendSetWorkerNum
     */
    void sendSetWorkerNum(int);
    /**
     * @brief sendMenuParamSetting
     */
    void sendMenuParamSetting(ConfigInfo);
    /**
     * @brief sendHideRightWindow
     */
    void sendHideRightWindow();
    /**
     * @brief sendEmptyWinDoubleClicked
     */
    void sendEmptyWinDoubleClicked();
    /**
     * @brief sendShowHideSignal
     */
    void sendShowHideSignal(bool);

    void sendSelfRowSignal(int,int);

    void sendIsLeaveSignal(bool);

    void sendIdAndColor(int,QColor,int);

    void sendSortSignal();

    void sendStrutData(QByteArray,int);

    void sendDisConnectSignal(int);

    void sendConnectNumSignal(int);

    void sendOverSignal();

    void checkPatientInfo(int);

    void voiceCheckChanged(bool);

    void updateUi();

    void clearLineEdit();

    void disConnectSig(int);

    void sendRowNum(int);

private slots:
    void onSlotAlarm(int id, bool isOpen);

    void onSlotCloseAlarm(int id, bool isClose);

    void onTimeOut();
private:
    static UIManager                       *m_pInstance;

public:

    void setFousId(int fousId);

    int m_fousId = 0;

    bool m_voiceCheck = true;

    QSound *sound;

    int record[100] = {0};

    QTimer              *m_timer = Q_NULLPTR;
};

#define uimanager UIManager::instance()

#endif // UIMANAGER_H
