/**
* @FileName             languagemanager.h
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2019-11-04
* @Author               luteng
* @email                luteng1230@163.com
* @Create Date          2019-11-04
* @
*/
#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H

#include "languageid.h"

#include <QObject>
#include <QMap>

class LanguageManager : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(LanguageManager)
public:
    explicit LanguageManager(QObject *parent = nullptr);

    virtual ~LanguageManager();

public:

    bool getMaxFont(QRect inrect, int characterSize, QFont &font);

    bool getMaxFont(QRect inrect, QString text, QFont &font, int maxPixelSize = 0);

    void setBitmapFont(QRect inrect, QString text, QFont &font, bool autosize = true);

    QFont getFont(Cms::Res::FontID fontid);

protected:
    QMap<Cms::Res::FontID, QString> mFontFamilys;
};

#endif // LANGUAGEMANAGER_H
