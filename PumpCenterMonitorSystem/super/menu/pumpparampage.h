/**
* @FileName             pumpparampage.h
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-09-28 14:54:35
* @Author               zhoumingjie
* @email
* @Create Date          2021-09-28 14:54:35
* @
*/
#ifndef PUMPPARAMPAGE_H
#define PUMPPARAMPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QLabel>
#include <QRegExpValidator>


typedef struct ConfigInfo
{
    QString pumpModel = Q_NULLPTR;
    QString drugName = Q_NULLPTR;
    int pumpFlow = 0;
    int pumpTime = 0;
    int presetValue = 0;
    int currentPressure = 0;
    int cumulant = 0;
}ConfigInfo;

Q_DECLARE_METATYPE(ConfigInfo)


class pumpParamPage : public QWidget
{
    Q_OBJECT
public:
    explicit pumpParamPage(QWidget *parent = nullptr);
    virtual ~pumpParamPage();

    void pageInit();

    void setParamConfig();
signals:
    void sendParamConfig(ConfigInfo);


public slots:

private:
    QLineEdit       *m_pumpModelEdit;
    QLineEdit       *m_drugNameEdit;
    QLineEdit       *m_pumpFlowEdit;
    QLineEdit       *m_pumpTimeEdit;
    QLineEdit       *m_presetValueEdit;
    QLineEdit       *m_currentPressureEdit;
    QLineEdit       *m_cumulantEdit;
    QPushButton     *m_okButton;


};

#endif // PUMPPARAMPAGE_H
