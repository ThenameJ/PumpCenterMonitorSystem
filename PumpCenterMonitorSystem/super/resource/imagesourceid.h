/**
* @FileName             stringresource.cpp
* @Brief                摘要
* @Version              1.0.0
* @Current Maintainter  修改者
* @Update Date          2019-04-16
* @Author               luteng
* @email                luteng1230@163.com
* @Create Date          2019-04-16
* @
*/
#ifndef IMAGESOURCEID_H
#define IMAGESOURCEID_H
namespace Cms
{
    namespace Res
    {
        enum ImageID
        {
            IMAGE_Null,
            IMAGE_Patient0,
            IMAGE_Patient1,
            IMAGE_PatientPlus,


            IMAGE_Setting,
            IMAGE_Settings,
            IMAGE_PowerOff,
            IMAGE_EmptyBed,

            IMAGE_DoubleLeft,
            IMAGE_DoubleRight,

            IMAGE_Close,

            IMAGE_Max
        };
    }


    typedef enum       //系统语言
    {
        Language_English,       // 英语
        Language_SimChinese,    // 简体中文
        Language_Spanish,       // 西班牙语
        Language_French,        // 法语
        Language_German,        // 德语
        Language_Italian,       // 意大利语
        Language_Polish,        // 波兰语
        Language_Portuguese,    // 葡萄牙语
        Language_Russian,       // 俄语
        Language_Czech,         // 捷克语
        Language_Turkish,       // 土耳其语
        Language_Danish,        // 丹麦语
        Language_Dutch,         // 荷兰语
        Language_Finnish,       // 芬兰语
        Language_Hungarian,     // 匈牙利语
        Language_Norwegian,     // 挪威语
        Language_Swedish,       // 瑞典语
        Language_Romanian,      // 罗马尼亚语
        Language_Serbian,       // 塞尔威亚语
        Language_Bulgarian,     // 保加利亚语
        Language_Greek,         // 希腊语
        Language_TraChinese,    // 繁体中文语
        Language_Max
    }SysLanguage;


    typedef enum
    {
        Protocol_Unknown,               //未知
        Protocol_pump,
        Protocol_Max
    }ProtocolType;


}

#endif // IMAGESOURCEID_H
