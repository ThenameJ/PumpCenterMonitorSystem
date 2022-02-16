/**
* @FileName             gpsresource.h
* @Brief                摘要
* @Version              1.0.0
* @Current Maintainter  修改者
* @Update Date          2019-04-16
* @Author               luteng
* @email                luteng1230@163.com
* @Create Date          2019-04-16
* @
*/
#include "cmsresourcemanager.h"
#include <QMutex>
#include <QMutexLocker>
#include <QPixmap>
#include <QFont>
#include <QFontMetrics>

Q_GLOBAL_STATIC(QMutex, createlock)
CMSResourceManager *CMSResourceManager::m_pInstance = Q_NULLPTR;

CMSResourceManager *CMSResourceManager::instance()
{
    if (m_pInstance == Q_NULLPTR)
    {
        QMutexLocker locker(createlock());
        if (m_pInstance == Q_NULLPTR)
        {
            m_pInstance = new CMSResourceManager(NULL);
        }
    }
    return m_pInstance;
}

CMSResourceManager::CMSResourceManager(QObject *parent) : QObject(parent)
{
    m_pImageRes = new ImageResource(parent);
    m_languageRes = new LanguageManager(parent);
    refreshUnit();
}

CMSResourceManager::~CMSResourceManager()
{
    if (m_pImageRes)
        delete m_pImageRes;
    m_pImageRes = Q_NULLPTR;
}


QPixmap CMSResourceManager::pixmap(Cms::Res::ImageID id)
{
    return m_pImageRes->pixmap(id);
}

bool CMSResourceManager::getMaxFont(QRect inrect, int characterSize, QFont &font)
{
    return m_languageRes->getMaxFont(inrect, characterSize, font);
//    if (characterSize <= 0 || inrect.width() < 5 || inrect.height() < 5)
//        return false;

//    QString text;
//    for (int i = 0; i < characterSize; i++)
//        text.append("8");

//    return getMaxFont(inrect, text, font);
}

bool CMSResourceManager::getMaxFont(QRect inrect, QString text, QFont &font, int maxPixelSize)
{
    return m_languageRes->getMaxFont(inrect, text, font, maxPixelSize);
//   if (text.isEmpty() || inrect.width() < 5 || inrect.height() < 5)
//        return false;

//    int min = 1;
//    int max = qMax(inrect.height(), inrect.width());
//    if (maxPixelSize > 0)
//        max = qMin(max, maxPixelSize);
//    int cur = (min + max) / 2;
//    font.setPixelSize(cur);

//    QFontMetrics fm(font);
//    QRect rect = fm.boundingRect(text);
//    while (1)
//    {
//        if ((int)(inrect.width() * 0.99) > rect.width() && (int)(inrect.height() * 0.99) > rect.height())
//        {
//            min = cur;
//        }
//        else
//        {
//            max = cur;
//        }

//        cur = (min + max ) / 2;

//        font.setPixelSize(cur);
//        if (cur == min)
//            break;

//        QFontMetrics fm(font);
//        rect = fm.boundingRect(text);
//    }

//    return true;
}

void CMSResourceManager::setBitmapFont(QRect inrect, QString text, QFont &font, bool autosize)
{
    m_languageRes->setBitmapFont(inrect, text, font, autosize);
}

QFont CMSResourceManager::getFont(Cms::Res::FontID fontid)
{
    return m_languageRes->getFont(fontid);
}

void CMSResourceManager::refreshUnit()
{
}
