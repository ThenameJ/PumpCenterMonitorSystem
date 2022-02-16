/**
* @FileName             basemenupage.h
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-09-28 14:53:52
* @Author               zhoumingjie
* @email
* @Create Date          2021-09-28 14:53:52
* @
*/
#ifndef BASEMENUPGE_H
#define BASEMENUPGE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QLabel>
#include <QPainter>
#include <QToolButton>

class BaseTitleBar;
class BaseMenuPage : public QWidget
{
    Q_OBJECT
public:
    explicit BaseMenuPage(QWidget *parent = nullptr);

    virtual ~BaseMenuPage();

    QVBoxLayout *mainLayout;

    BaseTitleBar *m_newTitleBar;

    virtual void addWidget(QWidget *widget);
signals:

public slots:

};





class BaseTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit BaseTitleBar(QWidget *parent = nullptr);

    virtual ~BaseTitleBar();

    void setTitleText(const QString &text);

protected:
    void resizeEvent(QResizeEvent *event);

signals:

public slots:


public:
    QString m_titleInfo = Q_NULLPTR;
    QLabel *m_topInfoLabel;

};


#endif // BASEMENUPGE_H
