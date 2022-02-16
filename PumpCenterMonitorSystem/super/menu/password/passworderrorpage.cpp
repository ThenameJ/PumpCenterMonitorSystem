#include "passworderrorpage.h"

PasswordErrorPage::PasswordErrorPage(QWidget *parent) : BaseMenuPage(parent)
{
    setAttribute(Qt::WA_DeleteOnClose,true);
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    resize(300,150);
    move(810,465);
    QWidget *demo = new QWidget;

    QVBoxLayout *vlayout = new QVBoxLayout;
    QPushButton *button = new QPushButton(tr("确认"));
    button->setShortcut(Qt::Key_Enter);

    connect(button,&QPushButton::clicked,[&](){
        close();
        delete this;
    });

    QHBoxLayout *hlayout = new QHBoxLayout;
    QLabel *label = new QLabel(tr("密码错误！"));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(button);

    hlayout->addStretch();
    hlayout->addWidget(label);
    hlayout->addStretch();

    vlayout->addStretch();
    vlayout->addLayout(hlayout);
    vlayout->addStretch();
    vlayout->addLayout(buttonLayout);

    demo->setLayout(vlayout);
    m_newTitleBar->setTitleText("警告");
    addWidget(demo);
}
