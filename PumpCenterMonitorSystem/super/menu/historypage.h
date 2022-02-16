/**
* @FileName             historypage.h
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-11-09 10:12:57
* @Author               zhoumingjie
* @email
* @Create Date          2021-11-09 10:12:57
* @
*/
#ifndef HISTORYPAGE_H
#define HISTORYPAGE_H

#include <QWidget>
#include <QTableView>
#include <QSqlQueryModel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

class HistoryTable;
class HistoryPage : public QWidget
{
    Q_OBJECT
public:
    explicit HistoryPage(QWidget *parent = nullptr);

signals:
    void sendText(QString,QString);

public slots:
};


class CustomSqlQueryModel;
class HistoryTable : public QTableView
{
    Q_OBJECT
public:
    explicit HistoryTable(QWidget *parent = nullptr);
    virtual ~HistoryTable();

    void initTable();

    void list();

signals:

public slots:
    void onSlotChangeTable(QString text ,QString type);

    void onSlotUpdate();

private:
    CustomSqlQueryModel *model;

};


class CustomSqlQueryModel : public QSqlQueryModel
{
public:
    CustomSqlQueryModel(QObject *parent = 0);
    virtual ~CustomSqlQueryModel();
    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &index, int role) const override;
};


#endif // HISTORYPAGE_H
