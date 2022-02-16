#ifndef PERMISSIONSPAGE_H
#define PERMISSIONSPAGE_H

#include <QWidget>
#include "baseclosemenupage.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class PermissionsPage : public BaseCloseMenuPage
{
    Q_OBJECT
public:
    explicit PermissionsPage(QWidget *parent = nullptr);

    void initWindow();

signals:
    void changePermissionSig(bool);

public slots:
    void onSlotJudgePassword();

private:
    QLineEdit *lineEdit;
};

#endif // PERMISSIONSPAGE_H
