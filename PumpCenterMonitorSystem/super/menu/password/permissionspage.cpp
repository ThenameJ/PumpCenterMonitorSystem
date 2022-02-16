#include "permissionspage.h"
#include "passworderrorpage.h"
#include "keyhook.h"
PermissionsPage::PermissionsPage(QWidget *parent) : BaseCloseMenuPage(parent)
{
    QPalette pe;
    pe.setColor(QPalette::Background, QColor(200,200,200));
    setAutoFillBackground(true);
    setPalette(pe);

    initWindow();
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

}

void PermissionsPage::initWindow()
{
    this->m_newTitleBar->setTitleText("密码权限");
    resize(400,200);
    this->move(760,440);
    QWidget *demo = new QWidget;
    demo->resize(400,200);
    QVBoxLayout *vlayout = new QVBoxLayout;

    QPushButton *button = new QPushButton(tr("确认"));
    button->setShortcut(Qt::Key_Enter);
    connect(button,SIGNAL(clicked(bool)),this,SLOT(onSlotJudgePassword()));

    QHBoxLayout *hlayout = new QHBoxLayout;
    QLabel *label = new QLabel(tr("密码："));
    lineEdit = new QLineEdit;
    lineEdit->setEchoMode(QLineEdit::Password);
    lineEdit->setClearButtonEnabled(true);
    hlayout->addWidget(label);
    hlayout->addWidget(lineEdit);

    vlayout->addStretch();
    vlayout->addLayout(hlayout);
    vlayout->addStretch();
    vlayout->addWidget(button);

    demo->setLayout(vlayout);
    addWidget(demo);
}


void PermissionsPage::onSlotJudgePassword()
{
    if(lineEdit->text() == "123456")
    {
        this->close();
        emit changePermissionSig(true);
        keyhook->exitKeyHook();
    }
    else
    {
        PasswordErrorPage *demo = new PasswordErrorPage(this);
        demo->show();
    }
}
