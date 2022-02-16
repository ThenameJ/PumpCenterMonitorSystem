/**
* @FileName             cmsresourcemanager.h
* @Brief                摘要
* @Version              1.0.0
* @Current Maintainter  修改者
* @Update Date          2019-04-16
* @Author               luteng
* @email                luteng1230@163.com
* @Create Date          2019-04-16
* @
*/
#include "imageresource.h"
#include <QDebug>
#include <QPixmap>

ImageResource::ImageResource(QObject *parent) : QObject(parent)
{
    initImagePath();
}

ImageResource::~ImageResource()
{

}

QPixmap ImageResource::pixmap(Cms::Res::ImageID id)
{
    if (m_imageTable.contains(id))
        return m_imageTable.value(id);

    bool ok = false;
    QPixmap tmp = loadImage(id, &ok);
    if (ok)
        m_imageTable.insert(id, tmp);

    return tmp;
}

void ImageResource::initImagePath()
{
    m_imagePathTable.insert(Cms::Res::IMAGE_Patient0,               ":/resource/image/patient/patient0.png");
    m_imagePathTable.insert(Cms::Res::IMAGE_Patient1,               ":/resource/image/patient/patient1.png");
    m_imagePathTable.insert(Cms::Res::IMAGE_PatientPlus,            ":/resource/image/patient/patientplus.png");

    m_imagePathTable.insert(Cms::Res::IMAGE_Setting,                ":/resource/image/system/settingConfig.png");
    m_imagePathTable.insert(Cms::Res::IMAGE_Settings,               ":/resource/image/system/Config.png");
    m_imagePathTable.insert(Cms::Res::IMAGE_PowerOff,               ":/resource/image/system/Power.png");
    m_imagePathTable.insert(Cms::Res::IMAGE_EmptyBed,               ":/resource/image/common/emptybed.png");
    m_imagePathTable.insert(Cms::Res::IMAGE_DoubleLeft,             ":/resource/image/others/doubleLeft.png");
    m_imagePathTable.insert(Cms::Res::IMAGE_DoubleRight,            ":/resource/image/others/doubleRight.png");
    m_imagePathTable.insert(Cms::Res::IMAGE_Close,                  ":/resource/image/common/closeOne.png");


}

QPixmap ImageResource::loadImage(Cms::Res::ImageID id, bool *ok)
{
    QString path = m_imagePathTable.value(id);
    QPixmap tmp(path);
    if (ok)
        *ok = !tmp.isNull();

    if (tmp.isNull())
        qDebug() << QString("Load image id = %1, path = %2 failed.").arg(id).arg(path);

    return tmp;
}
