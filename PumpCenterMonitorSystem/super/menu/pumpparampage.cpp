
/**
* @FileName             pumpparampage.cpp
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-09-28 14:55:05
* @Author               zhoumingjie
* @email
* @Create Date          2021-09-28 14:55:05
* @
*/
#include "pumpparampage.h"
#include "uimanager.h"

pumpParamPage::pumpParamPage(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    pageInit();
    connect(m_okButton,&QPushButton::clicked,[=](){
        if(m_pumpTimeEdit->text() != Q_NULLPTR || m_drugNameEdit->text() != Q_NULLPTR)
        {
           setParamConfig();
        }
    });
    connect(this,SIGNAL(sendParamConfig(ConfigInfo)),uimanager,SIGNAL(sendMenuParamSetting(ConfigInfo)));

}

pumpParamPage::~pumpParamPage()
{

}

void pumpParamPage::pageInit()
{
    QHBoxLayout *pumpModelLayout = new QHBoxLayout();
    QHBoxLayout *drugNameLayout = new QHBoxLayout();
    QHBoxLayout *pumpFlowLayout = new QHBoxLayout();
    QHBoxLayout *pumpTimeLayout = new QHBoxLayout();
    QHBoxLayout *presetValueLayout = new QHBoxLayout();
    QHBoxLayout *currentPressureLayout = new QHBoxLayout();
    QHBoxLayout *cumulantLayout = new QHBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QVBoxLayout *vLayout = new QVBoxLayout();


    m_okButton = new QPushButton(tr("确定"),this);
    m_okButton->setShortcut(Qt::Key_Enter);
//    connect(m_okButton,&QPushButton::clicked,[=](){

//    });

    QLabel *pumpModelLabel = new QLabel(tr("输注模式："));
    QLabel *drugNameLabel = new QLabel(tr("药物名称："));
    QLabel *pumpFlowLabel = new QLabel(tr("输注流速："));
    QLabel *pumpTimeLabel = new QLabel(tr("输注时间："));
    QLabel *presetValueLabel = new QLabel(tr("预置量："));
    QLabel *currentPressureLabel = new QLabel(tr("当前压力："));
    QLabel *cumulantLabel = new QLabel(tr("累积量："));

    m_pumpModelEdit = new QLineEdit(this);
    m_drugNameEdit = new QLineEdit(this);
    m_pumpFlowEdit = new QLineEdit(this);
    m_pumpTimeEdit = new QLineEdit(this);
    //  限制字符输入长度
    m_drugNameEdit->setMaxLength(13);
    //    QRegExp regx("^([1-9]\\d|\\d)$");//输入范围为【0-123】
    QRegExp regx("^([1-9]|[1-9][0-9])$");
    QValidator *validator = new QRegExpValidator(regx,m_pumpTimeEdit);
    m_pumpTimeEdit->setValidator(validator);
    m_presetValueEdit = new QLineEdit(this);
    m_currentPressureEdit = new QLineEdit(this);
    m_cumulantEdit = new QLineEdit(this);

    pumpModelLayout->addWidget(pumpModelLabel,1);
    pumpModelLayout->addWidget(m_pumpModelEdit,6);
    drugNameLayout->addWidget(drugNameLabel,1);
    drugNameLayout->addWidget(m_drugNameEdit,6);
    pumpFlowLayout->addWidget(pumpFlowLabel,1);
    pumpFlowLayout->addWidget(m_pumpFlowEdit,6);
    pumpTimeLayout->addWidget(pumpTimeLabel,1);
    pumpTimeLayout->addWidget(m_pumpTimeEdit,6);
    presetValueLayout->addWidget(presetValueLabel,1);
    presetValueLayout->addWidget(m_presetValueEdit,6);
    currentPressureLayout->addWidget(currentPressureLabel,1);
    currentPressureLayout->addWidget(m_currentPressureEdit,6);
    cumulantLayout->addWidget(cumulantLabel,1);
    cumulantLayout->addWidget(m_cumulantEdit,6);

    buttonLayout->addStretch();
    buttonLayout->addWidget(m_okButton);

    vLayout->addLayout(pumpModelLayout);
    vLayout->addLayout(drugNameLayout);
    vLayout->addLayout(pumpFlowLayout);
    vLayout->addLayout(pumpTimeLayout);
    vLayout->addLayout(presetValueLayout);
    vLayout->addLayout(currentPressureLayout);
    vLayout->addLayout(cumulantLayout);
    vLayout->addLayout(buttonLayout);

    if(layout())
        delete layout();

    setLayout(vLayout);

}

void pumpParamPage::setParamConfig()
{
    ConfigInfo info;
    info.pumpTime = m_pumpTimeEdit->text().toInt();
    info.drugName = m_drugNameEdit->text();
    emit sendParamConfig(info);
}


