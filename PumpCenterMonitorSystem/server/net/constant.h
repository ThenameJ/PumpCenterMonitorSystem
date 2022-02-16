#ifndef CONSTANT_H
#define CONSTANT_H
#include <QByteArray>
#include <QDataStream>

struct databuf
{
    int         deviceId = 0;
    QString     drugName = Q_NULLPTR;
    int         pumpTime = 0;
    QString     symptoms = Q_NULLPTR;
    QString     patientName = Q_NULLPTR;
    QString     sex = Q_NULLPTR;
    QString     height = Q_NULLPTR;
    QString     weight = Q_NULLPTR;
    QString     age = Q_NULLPTR;
};

Q_DECLARE_METATYPE(databuf)

inline QDataStream& operator>>(QDataStream& in,  databuf &pumpData)
{
    int         deviceId;
    QString     drugName;
    int         pumpTime;
    QString     symptoms;
    QString     patientName;
    QString     sex;
    QString     height;
    QString     weight;
    QString     age;
    in >> deviceId >> drugName >> pumpTime >> symptoms >> patientName >> sex >> height >> weight >> age;
    pumpData.deviceId = deviceId;
    pumpData.drugName = drugName;
    pumpData.pumpTime =pumpTime;
    pumpData.symptoms = symptoms;
    pumpData.patientName = patientName;
    pumpData.sex = sex;
    pumpData.height = height;
    pumpData.weight = weight;
    pumpData.age = age;
    return in;
}

#endif // CONSTANT_H
