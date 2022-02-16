/**
* @FileName             interfacetopbar.h
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-08-20
* @Author               luteng
* @email
* @Create Date          2021-08-20
* @
*/
#ifndef INTERFACETOPBAR_H
#define INTERFACETOPBAR_H

#include <QWidget>

class InterfaceTopBar : public QWidget
{
    Q_OBJECT
public:
    explicit InterfaceTopBar(QWidget *parent = nullptr);
    virtual ~InterfaceTopBar();

public:
    /**
     * @brief updateSysTime
     */
    void updateSysTime();


protected:
    /**
     * @brief paintEvent
     * @param event
     */
    virtual void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    /**
     * @brief resizeEvent
     * @param event
     */
    void resizeEvent(QResizeEvent *event);

private:
    /**
     * @brief paintTime
     * @param painter
     * @param rect
     */
    void paintTime(QPainter* painter, const QRect &rect);

    /**
     * @brief paintHospitalInfo
     * @param painter
     * @param rect
     */
    void paintHospitalInfo(QPainter* painter, const QRect &rect);

    void paintDeviceNum(QPainter* painter, const QRect &rect);

    /**
     * @brief createBoundary
     */
    void createBoundary();

private slots:
    void onSlotSetConnectNum(int connectNum);


private:
    int m_connectNum = 0;

};

#endif // INTERFACETOPBAR_H
