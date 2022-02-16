/**
* @FileName             pumpconfigpage.h
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-09-26 15:59:35
* @Author               zhoumingjie
* @email
* @Create Date          2021-09-26 15:59:35
* @
*/
#ifndef PUMPCONFIGPAGE_H
#define PUMPCONFIGPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QLabel>
#include <QPaintEvent>
#include <QTabWidget>
#include <QPainter>
#include "baseclosemenupage.h"

class PumpConfigPage : public BaseCloseMenuPage
{
    Q_OBJECT
public:
    explicit PumpConfigPage(QWidget *parent = nullptr);
    virtual ~PumpConfigPage();

    static PumpConfigPage *instance();

    void PumpConfigPageInit();

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:

private:
    static PumpConfigPage *m_pInstance;

    QTabWidget *m_tabWidget;
};

#define PumpConfig PumpConfigPage::instance()

#endif // PUMPCONFIGPAGE_H
