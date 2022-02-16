#ifndef PASSWORDERRORPAGE_H
#define PASSWORDERRORPAGE_H

#include <QWidget>
#include "basemenupage.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
class PasswordErrorPage : public BaseMenuPage
{
    Q_OBJECT
public:
    explicit PasswordErrorPage(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // PASSWORDERRORPAGE_H
