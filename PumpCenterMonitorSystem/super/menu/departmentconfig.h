/**
* @FileName             departmentconfig.h
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-09-26 15:58:55
* @Author               zhoumingjie
* @email
* @Create Date          2021-09-26 15:58:55
* @
*/
#ifndef DEPARTMENTCONFIG_H
#define DEPARTMENTCONFIG_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QLabel>

class DepartmentConfig : public QWidget
{
    Q_OBJECT
public:
    explicit DepartmentConfig(QWidget *parent = nullptr);
    virtual ~DepartmentConfig();

    void windowInit();

signals:
    void sendNumSignal(int);

    void sendRowNum(int);

    void sendSelfNumSignal(int, int);

    void sendCloseSignal();

public slots:
    void disableButton();

    void ableButton();

private:
    QPushButton *m_okButton;
    QHBoxLayout *m_hlayout;
    QHBoxLayout *m_numlayout;
    QHBoxLayout *m_selfNumlayout;
    QVBoxLayout *m_vlayout;
    bool        isChange = false;

public:
    QLineEdit *m_numEdit;
    QLineEdit *m_rowEdit;
    QLineEdit *m_lineEdit;

};

#endif // DEPARTMENTCONFIG_H
