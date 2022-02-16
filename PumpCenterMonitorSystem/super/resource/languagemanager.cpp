/**
* @FileName             languagemanager.cpp
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2019-11-04
* @Author               luteng
* @email                luteng1230@163.com
* @Create Date          2019-11-04
* @
*/
#include "languagemanager.h"
#include <QMutex>
#include <QFont>
#include <QFontMetrics>
#include <QElapsedTimer>
#include <QFontDatabase>
#include <QFont>

LanguageManager::LanguageManager(QObject *parent) : QObject(parent)
{
//    QFontDatabase font;
//    qDebug()<<font.families();
    QFontDatabase::addApplicationFont(":/resource/font/zero.ttf");  //zero
    //
    int loadedFontID = QFontDatabase::addApplicationFont(":/resource/font/Helvetica.ttf");

    QStringList loadedFontFamilies = QFontDatabase::applicationFontFamilies(loadedFontID);
    if (!loadedFontFamilies.empty())
        mFontFamilys.insert(Cms::Res::Font_Helvetica, loadedFontFamilies.at(0));
    //
    loadedFontFamilies.clear();
    loadedFontID = QFontDatabase::addApplicationFont(":/resource/font/FontAwesome.otf");
    loadedFontFamilies = QFontDatabase::applicationFontFamilies(loadedFontID);
    if (!loadedFontFamilies.empty())
        mFontFamilys.insert(Cms::Res::Font_Awesome, loadedFontFamilies.at(0));

//    //SourceHanSans-Medium
//    loadedFontFamilies.clear();
//    loadedFontID = QFontDatabase::addApplicationFont(":/res/font/SourceHanSans-Medium.otf");
//    loadedFontFamilies = QFontDatabase::applicationFontFamilies(loadedFontID);
//    if (!loadedFontFamilies.empty())
//        mFontFamilys.insert(Cms::Res::Font_HanSansSC_Medium, loadedFontFamilies.at(0));

    //SourceHanSans-Normal
//    loadedFontFamilies.clear();
//    loadedFontID = QFontDatabase::addApplicationFont(":/res/font/SourceHanSans-Normal.otf");
//    loadedFontFamilies = QFontDatabase::applicationFontFamilies(loadedFontID);
//    if (!loadedFontFamilies.empty())
//        mFontFamilys.insert(Cms::Res::Font_HanSansSC_Normal, loadedFontFamilies.at(0));

//    //SourceHanSans-Medium
//    loadedFontFamilies.clear();
//    loadedFontID = QFontDatabase::addApplicationFont(":/res/font/SourceHanSans-Regular.otf");
//    loadedFontFamilies = QFontDatabase::applicationFontFamilies(loadedFontID);
//    if (!loadedFontFamilies.empty())
//        mFontFamilys.insert(Cms::Res::Font_HanSansSC_Regular, loadedFontFamilies.at(0));

    //WenQuanyi
//    loadedFontFamilies.clear();
//    loadedFontID = QFontDatabase::addApplicationFont(":/res/font/wqyzh.ttf");
//    loadedFontFamilies = QFontDatabase::applicationFontFamilies(loadedFontID);
//    if (!loadedFontFamilies.empty())
//        mFontFamilys.insert(Cms::Res::Font_WenQuanYi, loadedFontFamilies.at(0));

    loadedFontFamilies.clear();
    loadedFontID = QFontDatabase::addApplicationFont(":/resource/font/HarmonyOS_Sans_SC_Regular.ttf");
    loadedFontFamilies = QFontDatabase::applicationFontFamilies(loadedFontID);
    if (!loadedFontFamilies.empty())
        mFontFamilys.insert(Cms::Res::Font_HarmonyOS_Sans_SC, loadedFontFamilies.at(0));

//    loadedFontFamilies.clear();
//    loadedFontID = QFontDatabase::addApplicationFont(":/res/font/HarmonyOS_Sans_Regular.ttf");
//    loadedFontFamilies = QFontDatabase::applicationFontFamilies(loadedFontID);
//    if (!loadedFontFamilies.empty())
//        mFontFamilys.insert(Cms::Res::Font_HarmonyOS_Sans, loadedFontFamilies.at(0));


//    QFontDatabase dataBase;
//    QStringList familiesFont = dataBase.families();
//    qDebug()<<familiesFont;Times New Roman
    mFontFamilys.insert(Cms::Res::Font_Arial, "arial");
    mFontFamilys.insert(Cms::Res::Font_Segoe_UI, "segoe UI");
    mFontFamilys.insert(Cms::Res::Font_MicrosoftYaHei, "Microsoft YaHei");
    mFontFamilys.insert(Cms::Res::Font_SimSun, "宋体");
    mFontFamilys.insert(Cms::Res::Font_Zero, "Untitled1");
    mFontFamilys.insert(Cms::Res::Font_Bitmap, "WenQuanYi Bitmap Song");
}

LanguageManager::~LanguageManager()
{
}

bool LanguageManager::getMaxFont(QRect inrect, int characterSize, QFont &font)
{
    if (characterSize <= 0 || inrect.width() < 5 || inrect.height() < 5)
        return false;

    QString text;
    for (int i = 0; i < characterSize; i++)
        text.append("8");

    return getMaxFont(inrect, text, font);
}

bool LanguageManager::getMaxFont(QRect inrect, QString text, QFont &font, int maxPixelSize)
{
    if (text.isEmpty() || inrect.width() < 5 || inrect.height() < 5)
        return false;

    int min = 1;
    int max = qMax(inrect.height(), inrect.width());
    if (maxPixelSize > 0)
        max = qMin(max, maxPixelSize);
    int cur = (min + max) / 2;
    font.setPixelSize(cur);

    QFontMetrics fm(font);
    QRect rect = fm.boundingRect(text);
    while (1)
    {
        if (inrect.width() * 0.9 > rect.width() && inrect.height() * 0.9 > rect.height())
        {
            min = cur;
        }
        else
        {
            max = cur;
        }

        cur = (min + max ) / 2;

        font.setPixelSize(cur);
        if (cur == min)
            break;

        QFontMetrics fm(font);
        rect = fm.boundingRect(text);
    }

    return true;
}

void LanguageManager::setBitmapFont(QRect inrect, QString text, QFont &font, bool autosize)
{
    if (text.isEmpty() || inrect.width() < 5 || inrect.height() < 5)
        return;

    font.setFamily(getFont(Cms::Res::Font_Bitmap).family());
    font.setBold(false);
    font.setItalic(false);
    font.setStyleStrategy(QFont::NoAntialias);

    if (!autosize)
        return;

    int min = 1;
    int max = qMax(inrect.height(), inrect.width());
    int cur = (min + max) / 2;

    while (1)
    {
        font.setPixelSize(cur);
        QFontMetrics fm(font);
        QRect rect = fm.boundingRect(text);

        if (inrect.width() * 0.9 > rect.width() && inrect.height() * 0.9 > rect.height())
        {
            min = cur;
        }
        else
        {
            max = cur;
        }

        cur = (min + max ) / 2;

        if (cur == min)
            break;
    }
}

QFont LanguageManager::getFont(Cms::Res::FontID fontid)
{
    QFont font;
    QString family = mFontFamilys.value(fontid);
    if (!family.isEmpty())
        font.setFamily(family);

    return font;
}
