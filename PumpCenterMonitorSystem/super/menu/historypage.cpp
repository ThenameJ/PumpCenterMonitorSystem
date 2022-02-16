/**
* @FileName             historypage.cpp
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-11-09 10:12:45
* @Author               zhoumingjie
* @email
* @Create Date          2021-11-09 10:12:45
* @
*/

#include "historypage.h"
#include <QHeaderView>
#include <QDebug>


HistoryPage::HistoryPage(QWidget *parent) : QWidget(parent)
{
    QStringList strList;
    strList<<"姓名"<<"病历号"<<"设备号"<<"性别"<<"病症";


    QVBoxLayout *vlayout = new QVBoxLayout;
    HistoryTable *table = new HistoryTable;

    QHBoxLayout *hlayout = new QHBoxLayout;
    QLabel *label = new QLabel(tr("查询"));
    QLineEdit *lineEdit = new QLineEdit;
    QComboBox *comboBox = new QComboBox;
    QPushButton *button = new QPushButton(tr("更新"));
    QHBoxLayout *boottomLayout = new QHBoxLayout;

    boottomLayout->addStretch();
    boottomLayout->addWidget(button);

    comboBox->addItems(strList);

    connect(button,SIGNAL(clicked(bool)),table,SLOT(onSlotUpdate()));
    connect(this,SIGNAL(sendText(QString,QString)),table,SLOT(onSlotChangeTable(QString,QString)));

    connect(lineEdit,&QLineEdit::textChanged,[=](){
        emit sendText(lineEdit->text(),comboBox->currentText());
    });
    connect(this,SIGNAL(sendText(QString,QString)),table,SLOT(onSlotChangeTable(QString,QString)));
    hlayout->addWidget(label);
    hlayout->addWidget(comboBox);
    hlayout->addWidget(lineEdit);

    vlayout->addLayout(hlayout);
    vlayout->addWidget(table);
    vlayout->addLayout(boottomLayout);
    setLayout(vlayout);
}



HistoryTable::HistoryTable(QWidget *parent) : QTableView(parent)
{
    initTable();
    this->verticalHeader()->setVisible(false);
}

HistoryTable::~HistoryTable()
{

}

void HistoryTable::initTable()
{
    model = new CustomSqlQueryModel();
    model->setQuery("select record,deviceId,symptoms,patientName,sex,height,weight,age from patientinfo");
    list();
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    this->setModel(model);

}

void HistoryTable::list()
{
    model->setHeaderData(0, Qt::Horizontal, tr("病例号"));
    model->setHeaderData(1, Qt::Horizontal, tr("设备号"));
    model->setHeaderData(2, Qt::Horizontal, tr("病症"));
    model->setHeaderData(3, Qt::Horizontal, tr("姓名"));
    model->setHeaderData(4, Qt::Horizontal, tr("性别"));
    model->setHeaderData(5, Qt::Horizontal, tr("身高"));
    model->setHeaderData(6, Qt::Horizontal, tr("体重"));
    model->setHeaderData(7, Qt::Horizontal, tr("年龄"));
}

void HistoryTable::onSlotChangeTable(QString text, QString type)
{
//    int m = text.toInt()%1000000;
//    qDebug() << m;
    if(type == "姓名")
    {
        QString insert = QString("select record,deviceId,symptoms,patientName,sex,height,weight,age from patientinfo where patientName ='%1'")
                .arg(text);
        model->setQuery(insert);
        list();
    }
    else if(type == "病历号")
    {
        QString insert = QString("select patientinfo.record,patientinfo.deviceId,patientinfo.symptoms,patientinfo.patientName,patientinfo.sex,"
                                 "patientinfo.age,deviceinfo.pumptime,deviceinfo.drugName from patientinfo,deviceinfo "
                                 "where record ='%1' and patientinfo.deviceId = deviceinfo.deviceId")
                .arg(text);
        model->setQuery(insert);
        model->setHeaderData(6, Qt::Horizontal, tr("注液时长"));
        model->setHeaderData(7, Qt::Horizontal, tr("用药"));

    }
    else if(type == "设备号")
    {
        QString insert = QString("select record,deviceId,symptoms,patientName,sex,height,weight,age from patientinfo where deviceId ='%1'")
                .arg(text);
        model->setQuery(insert);
        list();
    }
    else if(type == "性别")
    {
        QString insert = QString("select record,deviceId,symptoms,patientName,sex,height,weight,age from patientinfo where sex ='%1'")
                .arg(text);
        model->setQuery(insert);
        list();
    }
    else if(type == "病症")
    {
        QString insert = QString("select record,deviceId,symptoms,patientName,sex,height,weight,age from patientinfo where symptoms ='%1'")
                .arg(text);
        model->setQuery(insert);
        list();
    }

    if(text == Q_NULLPTR)
    {
        model->setQuery("select record,deviceId,symptoms,patientName,sex,height,weight,age from patientinfo");
        list();
    }
}

void HistoryTable::onSlotUpdate()
{
    model->setQuery("select record,deviceId,symptoms,patientName,sex,height,weight,age from patientinfo");
    list();
}


CustomSqlQueryModel::CustomSqlQueryModel(QObject *parent)
{
    Q_UNUSED(parent)
}

CustomSqlQueryModel::~CustomSqlQueryModel()
{

}

QVariant CustomSqlQueryModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    /**
      * 单元格内容居中
      */
    if (Qt::TextAlignmentRole == role)
    {
        value = Qt::AlignCenter;
    }
    return value;
}
