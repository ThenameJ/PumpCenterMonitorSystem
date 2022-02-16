/**
* @FileName             departmentconfig.cpp
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-09-26 14:16:58
* @Author               zhoumingjie
* @email
* @Create Date          2021-09-26 14:16:58
* @
*/

#include "departmentconfig.h"
#include "uimanager.h"
#include "servermanager.h"
#include "event.h"
#include <QIntValidator>
#include <QDebug>

DepartmentConfig::DepartmentConfig(QWidget *parent) : QWidget(parent)
{
    windowInit();

    connect(this,SIGNAL(sendNumSignal(int)),uimanager,SIGNAL(sendSetWorkerNum(int)));

    connect(this,SIGNAL(sendSelfNumSignal(int,int)),uimanager,SIGNAL(sendSelfRowSignal(int,int)));

    connect(this,SIGNAL(sendRowNum(int)),uimanager,SIGNAL(sendRowNum(int)));

}

DepartmentConfig::~DepartmentConfig()
{

}

void DepartmentConfig::windowInit()
{
    m_vlayout = new QVBoxLayout();
    m_okButton = new QPushButton(tr("确认"));
    m_okButton->setShortcut(Qt::Key_Enter);
    connect(m_okButton,&QPushButton::clicked,[=](){
        if(!isChange)
        {
            if(m_numEdit->text() != Q_NULLPTR)
            {
                emit sendNumSignal(m_numEdit->text().toInt());
                emit sendRowNum(5);
            }
        }
        else
        {
            emit sendSelfNumSignal(m_rowEdit->text().toInt(),m_lineEdit->text().toInt());
            emit sendRowNum(m_rowEdit->text().toInt());
        }
        emit sendCloseSignal();

//        VariantEv *fvar = new VariantEv(QEvent::Type(EV_Quit));
//        cmsnetserver->publish(EV_Quit,fvar);
        cmsnetserver->exitOperate();
    });
    QVBoxLayout *PCIvlayout = new QVBoxLayout();
    QGroupBox *pumpInfoConfig = new QGroupBox(tr("房间配置"));
    m_numlayout = new QHBoxLayout();
    QLabel *numLabel = new QLabel(tr("设置个数："));
    QPushButton *selfButton = new QPushButton(tr("自定义行列"));
    selfButton->setMinimumWidth(140);
    m_numEdit = new QLineEdit();
    m_numEdit->setClearButtonEnabled(true);

    QRegExp regx("^([1-9]|[1-9][0-9]|100)$");
    QValidator *validator = new QRegExpValidator(regx,m_numEdit);
    m_numEdit->setValidator(validator);
    m_numEdit->setPlaceholderText(tr("请输入1~100以内的数字"));
    m_numlayout->addWidget(numLabel);
    m_numlayout->addWidget(m_numEdit);
    m_numlayout->addWidget(selfButton);

    connect(selfButton,&QPushButton::clicked,[=](){
        if(!isChange)
        {
            selfButton->setText(tr("关闭自定义行列"));
            disableButton();
        }
        else
        {
            selfButton->setText(tr("自定义行列"));
            ableButton();
        }
        isChange = !isChange;
    });

    m_selfNumlayout = new QHBoxLayout();
    QLabel *selfLineLabel = new QLabel(tr("自定义行："));
    QLabel *selfRowLabel = new QLabel(tr("自定义列："));
    m_rowEdit = new QLineEdit();
    m_lineEdit = new QLineEdit();
    m_rowEdit->setClearButtonEnabled(true);
    m_rowEdit->setValidator(new QIntValidator(1, 10, this));
    m_rowEdit->setPlaceholderText(tr("范围：1~10"));
    m_lineEdit->setClearButtonEnabled(true);
    m_lineEdit->setValidator(new QIntValidator(1, 10, this));
    m_lineEdit->setPlaceholderText(tr("范围：1~10"));
    m_rowEdit->setEnabled(false);
    m_lineEdit->setEnabled(false);
    m_selfNumlayout->addWidget(selfRowLabel);
    m_selfNumlayout->addWidget(m_rowEdit);
    m_selfNumlayout->addWidget(selfLineLabel);
    m_selfNumlayout->addWidget(m_lineEdit);

    PCIvlayout->addLayout(m_numlayout);
    PCIvlayout->addLayout(m_selfNumlayout);
    PCIvlayout->addStretch();
    PCIvlayout->addWidget(m_okButton);
    pumpInfoConfig->setLayout(PCIvlayout);


    m_vlayout->addWidget(pumpInfoConfig);
    if(layout())
        delete layout();
    setLayout(m_vlayout);

}

void DepartmentConfig::disableButton()
{

    m_numEdit->clear();
    m_rowEdit->setEnabled(true);
    m_lineEdit->setEnabled(true);
    m_numEdit->setEnabled(false);
}

void DepartmentConfig::ableButton()
{
    m_rowEdit->clear();
    m_lineEdit->clear();
    m_rowEdit->setEnabled(false);
    m_lineEdit->setEnabled(false);
    m_numEdit->setEnabled(true);
}
