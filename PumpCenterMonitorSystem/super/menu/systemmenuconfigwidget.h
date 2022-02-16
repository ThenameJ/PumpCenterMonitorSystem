/**
* @FileName             systemmenuconfigwidget.h
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-09-28 14:54:45
* @Author               zhoumingjie
* @email
* @Create Date          2021-09-28 14:54:45
* @
*/
#ifndef SYSTEMMENUCONFIGWIDGET_H
#define SYSTEMMENUCONFIGWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include "baseclosemenupage.h"
#include "permissionspage.h"

class SystemMenuConfigWidget : public BaseCloseMenuPage
{
    Q_OBJECT
public:
    explicit SystemMenuConfigWidget(QWidget *parent = nullptr);

    virtual ~SystemMenuConfigWidget();

    static SystemMenuConfigWidget *instance();

    void setInitItem();

protected:

signals:

public slots:
    void onSlotReinstated();

    void onSlotChangePermission(bool Reinstat);

private:
    static SystemMenuConfigWidget *m_pInstance;
    QListWidget* configList;
    int m_index;
    QStackedWidget *m_demo = Q_NULLPTR;
    PermissionsPage *password;
    bool            isReinstated = false;

};

#define systemConfigMenu SystemMenuConfigWidget::instance()

#endif // SYSTEMMENUCONFIGWIDGET_H
