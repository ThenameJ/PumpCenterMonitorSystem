/**
* @FileName             monitortimeleftlist.h
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-08-20
* @Author               luteng
* @email
* @Create Date          2021-08-20
* @
*/
#ifndef MONITORTIMELEFTLIST_H
#define MONITORTIMELEFTLIST_H

#include <QWidget>
#include <QVBoxLayout>

class MonitorTimeLeftList : public QWidget
{
    Q_OBJECT
public:
    explicit MonitorTimeLeftList(QWidget *parent = nullptr);
    virtual ~MonitorTimeLeftList();

private:
    /**
     * @brief initSpace
     */
    void initSpace();

signals:
    void sendShowHideSignal(bool);

private slots:
    void onSlotShowHideRightWindow();

    void onSlotShowRightWindow();

private:
    bool isChange = true;

};

#endif // MONITORTIMELEFTLIST_H
