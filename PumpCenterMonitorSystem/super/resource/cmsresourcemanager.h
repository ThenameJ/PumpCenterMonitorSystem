/**
* @FileName             uimanager->getResource().h
* @Brief                摘要
* @Version              1.0.0
* @Current Maintainter  修改者
* @Update Date          2019-04-16
* @Author               luteng
* @email                luteng1230@163.com
* @Create Date          2019-04-16
* @
*/
#ifndef CMSRESOURCEMANAGER_H
#define CMSRESOURCEMANAGER_H

#include <QObject>
#include "imageresource.h"
#include "languagemanager.h"

/*!
 * \brief The CMSResourceManager class
 * 界面使用到的一些资源,例如图片,字符串.
 * 同时,也包括公共的字符串拼接方式,例如报警信息拼接/单位转换等
 * 一般地,资源在UI线程使用,如果要用到多线程里面,则需要使用Mutex,暂时只允许在UI线程内使用
 */
class CMSResourceManager : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(CMSResourceManager)
public:
    static CMSResourceManager* instance();
    virtual ~CMSResourceManager();

    QPixmap pixmap(Cms::Res::ImageID id);

    //language
    bool getMaxFont(QRect inrect, int characterSize, QFont &font);

    bool getMaxFont(QRect inrect, QString text, QFont &font, int maxPixelSize = 0);

    void setBitmapFont(QRect inrect, QString text, QFont &font, bool autosize = true);

    QFont getFont(Cms::Res::FontID fontid);

    void refreshUnit();

    /**热键字符
     * @brief hotKeyString
     * @param id
     * @return
     */

protected:
    explicit CMSResourceManager(QObject *parent = nullptr);

private:
    static CMSResourceManager   *m_pInstance;
    ImageResource               *m_pImageRes = Q_NULLPTR;
    LanguageManager             *m_languageRes = Q_NULLPTR;
};
#endif // CMSRESOURCEMANAGER_H
