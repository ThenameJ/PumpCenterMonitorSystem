/**
* @FileName             patientinfowin.h
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-09-25 14:48:23
* @Author               zhoumingjie
* @email
* @Create Date          2021-09-25 14:48:23
* @
*/
#ifndef PATIENTINFOWIN_H
#define PATIENTINFOWIN_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QLabel>
#include <QPainter>
#include "basemenupage.h"

class PatientInfoWin : public BaseMenuPage
{
    Q_OBJECT
public:
    explicit PatientInfoWin(QWidget *parent = nullptr);
    virtual ~PatientInfoWin();

signals:


protected:
    void paintEvent(QPaintEvent *event);

public slots:
    void onSlotCheckPatientInfo(int deviceId);

    void onSlotClearLineEdit();
private:
    /**
     * @brief initInfo
     */
    void initInfo();


private:
    QLineEdit       *m_symptomsEdit;
    QLineEdit       *m_patientNameEdit;
    QLineEdit       *m_sexEdit;
    QLineEdit       *m_statureEdit;
    QLineEdit       *m_weightEdit;
    QLineEdit       *m_ageEdit;

};

#endif // PATIENTINFOWIN_H
