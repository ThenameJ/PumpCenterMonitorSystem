/**
* @FileName             patientinfowin.cpp
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-09-25 14:47:29
* @Author               zhoumingjie
* @email
* @Create Date          2021-09-25 14:47:29
* @
*/
#include "patientinfowin.h"
#include "uimanager.h"
#include "dbmanager.h"
#include <QDebug>


PatientInfoWin::PatientInfoWin(QWidget *parent) : BaseMenuPage(parent)
{
    QPalette pe;
    pe.setColor(QPalette::Background, QColor(40,40,40));
    setAutoFillBackground(true);
    setPalette(pe);

    connect(uimanager,SIGNAL(checkPatientInfo(int)),this,SLOT(onSlotCheckPatientInfo(int)));
    connect(uimanager,SIGNAL(clearLineEdit()),this,SLOT(onSlotClearLineEdit()));


    initInfo();

}

PatientInfoWin::~PatientInfoWin()
{

}

void PatientInfoWin::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QPen pen;
    pen.setColor(QColor(200,200,200));
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawRect(rect());
}

void PatientInfoWin::onSlotCheckPatientInfo(int deviceId)
{
    databuf patientInfo;
    patientInfo = dbmanager->getData(deviceId);
    m_symptomsEdit->setText(patientInfo.symptoms);
    m_patientNameEdit->setText(patientInfo.patientName);
    m_sexEdit->setText(patientInfo.sex);
    m_statureEdit->setText(patientInfo.height);
    m_weightEdit->setText(patientInfo.weight);
    m_ageEdit->setText(patientInfo.age);
}

void PatientInfoWin::onSlotClearLineEdit()
{
    m_symptomsEdit->setText("");
    m_patientNameEdit->setText("");
    m_sexEdit->setText("");
    m_statureEdit->setText("");
    m_weightEdit->setText("");
    m_ageEdit->setText("");
}

void PatientInfoWin::initInfo()
{
    QWidget *mainWidget = new QWidget();
    mainWidget->setFixedHeight(rect().height()-38);

    QHBoxLayout *symptomsLayout = new QHBoxLayout();
    QHBoxLayout *nameLayout = new QHBoxLayout();
    QHBoxLayout *sexLayout = new QHBoxLayout();
    QHBoxLayout *statureLayout = new QHBoxLayout();
    QHBoxLayout *weightLayout = new QHBoxLayout();
    QHBoxLayout *ageLayout = new QHBoxLayout();
    QVBoxLayout *vLayout = new QVBoxLayout();

    QLabel *symptomsLabel = new QLabel(tr("症状："));
    QLabel *patientNameLabel = new QLabel(tr("姓名："));
    QLabel *sexLabel = new QLabel(tr("性别："));
    QLabel *statureLabel = new QLabel(tr("身高："));
    QLabel *weightLabel = new QLabel(tr("体重："));
    QLabel *ageLabel = new QLabel(tr("年龄："));

    symptomsLabel->setStyleSheet("color:white");
    patientNameLabel->setStyleSheet("color:white");
    sexLabel->setStyleSheet("color:white");
    statureLabel->setStyleSheet("color:white");
    weightLabel->setStyleSheet("color:white");
    ageLabel->setStyleSheet("color:white");

    m_symptomsEdit = new QLineEdit();
    m_patientNameEdit = new QLineEdit();
    m_sexEdit = new QLineEdit();
    m_statureEdit = new QLineEdit();
    m_weightEdit = new QLineEdit();
    m_ageEdit = new QLineEdit();

    m_symptomsEdit->setStyleSheet("QLineEdit{background-color:rgb(40,40,40);border-width:0;border-style:outset;color:white}");
    m_patientNameEdit->setStyleSheet("QLineEdit{background-color:rgb(40,40,40);border-width:0;border-style:outset;color:white}");
    m_sexEdit->setStyleSheet("QLineEdit{background-color:rgb(40,40,40);border-width:0;border-style:outset;color:white}");
    m_statureEdit->setStyleSheet("QLineEdit{background-color:rgb(40,40,40);border-width:0;border-style:outset;color:white}");
    m_weightEdit->setStyleSheet("QLineEdit{background-color:rgb(40,40,40);border-width:0;border-style:outset;color:white}");
    m_ageEdit->setStyleSheet("QLineEdit{background-color:rgb(40,40,40);border-width:0;border-style:outset;color:white}");

//    m_symptomsEdit->setText(tr("流行感冒"));
//    m_patientNameEdit->setText(tr("张三"));
//    m_sexEdit->setText(tr("男"));
//    m_statureEdit->setText(tr("180 cm"));
//    m_weightEdit->setText(tr("65 kg"));
//    m_ageEdit->setText(tr("28 岁"));

    m_symptomsEdit->setFocusPolicy(Qt::NoFocus);
    m_patientNameEdit->setFocusPolicy(Qt::NoFocus);
    m_sexEdit->setFocusPolicy(Qt::NoFocus);
    m_statureEdit->setFocusPolicy(Qt::NoFocus);
    m_weightEdit->setFocusPolicy(Qt::NoFocus);
    m_ageEdit->setFocusPolicy(Qt::NoFocus);

    symptomsLayout->addWidget(symptomsLabel);
    symptomsLayout->addWidget(m_symptomsEdit);
    nameLayout->addWidget(patientNameLabel);
    nameLayout->addWidget(m_patientNameEdit);
    sexLayout->addWidget(sexLabel);
    sexLayout->addWidget(m_sexEdit);
    statureLayout->addWidget(statureLabel);
    statureLayout->addWidget(m_statureEdit);
    weightLayout->addWidget(weightLabel);
    weightLayout->addWidget(m_weightEdit);
    ageLayout->addWidget(ageLabel);
    ageLayout->addWidget(m_ageEdit);

    vLayout->setSpacing(40);
    vLayout->setMargin(20);
    vLayout->addLayout(symptomsLayout);
    vLayout->addLayout(nameLayout);
    vLayout->addLayout(sexLayout);
    vLayout->addLayout(statureLayout);
    vLayout->addLayout(weightLayout);
    vLayout->addLayout(ageLayout);
    vLayout->addStretch();
    mainWidget->setLayout(vLayout);
//    mainLayout->addWidget(mainWidget);
//    mainLayout->setSpacing(1);
//    mainLayout->setMargin(1);

//    if(layout())
//        delete layout();
//    setLayout(mainLayout);
    this->m_newTitleBar->setTitleText("患者信息");

    this->addWidget(mainWidget);

}





