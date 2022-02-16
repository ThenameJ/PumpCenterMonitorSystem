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
#ifndef IMAGERESOURCE_H
#define IMAGERESOURCE_H

#include <QObject>
#include <QMap>
#include "imagesourceid.h"

class QPixmap;
class ImageResource : public QObject
{
    Q_OBJECT
public:
    explicit ImageResource(QObject *parent = nullptr);
    virtual ~ImageResource();

    /**
     * @brief pixmap 获取图片
     * @param id 图片ID
     * @return
     */
    QPixmap pixmap(Cms::Res::ImageID id);
private:

    /**
     * @brief initImagePath
     */
    void initImagePath();

    /**
     * @brief loadImage 加载图片资源
     * @param id
     * @param ok
     * @return
     */
    QPixmap loadImage(Cms::Res::ImageID id, bool *ok = Q_NULLPTR);

private:
    QMap<Cms::Res::ImageID, QPixmap> m_imageTable;
    QMap<Cms::Res::ImageID, QString> m_imagePathTable;
};

#endif // IMAGERESOURCE_H
