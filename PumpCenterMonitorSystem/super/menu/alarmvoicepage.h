/**
* @FileName             alarmvoicepage.h
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-11-09 10:13:44
* @Author               zhoumingjie
* @email
* @Create Date          2021-11-09 10:13:44
* @
*/

#ifndef ALARMVOICEPAGE_H
#define ALARMVOICEPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QTimer>
#include <QEvent>
#include <QDebug>
#include <QMouseEvent>

class hospitalInfo;
class SwitchButton;
class AlarmVoicePage : public QWidget
{
    Q_OBJECT
public:
    explicit AlarmVoicePage(QWidget *parent = nullptr);
    virtual ~AlarmVoicePage();

    void windowInit();


signals:

public slots:


private:
    QLabel *voiceLabel = Q_NULLPTR;
    QLabel *titleLabel = Q_NULLPTR;

    QVBoxLayout *vlayout = Q_NULLPTR;
    QHBoxLayout *hlayout = Q_NULLPTR;
    QHBoxLayout *titleLayout = Q_NULLPTR;

    SwitchButton *button;
};


//class hospitalInfo : public QWidget
//{
//    Q_OBJECT
//public:
//    explicit hospitalInfo(QWidget *parent = nullptr);
//    virtual ~hospitalInfo();

//private:

//};




class SwitchButton : public QWidget
{
    Q_OBJECT
    Q_ENUMS(ButtonStyle)

    Q_PROPERTY(int space READ getSpace WRITE setSpace)
    Q_PROPERTY(int rectRadius READ getRectRadius WRITE setRectRadius)
    Q_PROPERTY(bool checked READ getChecked WRITE setChecked)
    Q_PROPERTY(bool showText READ getShowText WRITE setShowText)
    Q_PROPERTY(bool animation READ getAnimation WRITE setAnimation)
    Q_PROPERTY(ButtonStyle buttonStyle READ getButtonStyle WRITE setButtonStyle)

    Q_PROPERTY(QColor bgColorOff READ getBgColorOff WRITE setBgColorOff)
    Q_PROPERTY(QColor bgColorOn READ getBgColorOn WRITE setBgColorOn)
    Q_PROPERTY(QColor sliderColorOff READ getSliderColorOff WRITE setSliderColorOff)
    Q_PROPERTY(QColor sliderColorOn READ getSliderColorOn WRITE setSliderColorOn)
    Q_PROPERTY(QColor textColorOff READ getTextColorOff WRITE setTextColorOff)
    Q_PROPERTY(QColor textColorOn READ getTextColorOn WRITE setTextColorOn)

    Q_PROPERTY(QString textOff READ getTextOff WRITE setTextOff)
    Q_PROPERTY(QString textOn READ getTextOn WRITE setTextOn)

public:
    enum ButtonStyle {
        ButtonStyle_Rect = 0,       //圆角矩形
        ButtonStyle_CircleIn = 1,   //内圆形
        ButtonStyle_CircleOut = 2   //外圆形
    };

    SwitchButton(QWidget *parent = 0);
    virtual ~SwitchButton();

protected:
    void mousePressEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter);
    void drawSlider(QPainter *painter);

private:
    int space;                      //滑块离背景间隔
    int rectRadius;                 //圆角角度
    bool checked;                   //是否选中
    bool showText;                  //显示文字
    bool animation;                 //动画过渡

    ButtonStyle buttonStyle;        //开关按钮样式

    QColor bgColorOff;              //关闭时背景颜色
    QColor bgColorOn;               //打开时背景颜色
    QColor sliderColorOff;          //关闭时滑块颜色
    QColor sliderColorOn;           //打开时滑块颜色
    QColor textColorOff;            //关闭时文字颜色
    QColor textColorOn;             //打开时文字颜色

    QString textOff;                //关闭时显示的文字
    QString textOn;                 //打开时显示的文字

    int step;                       //每次移动的步长
    int startX;                     //滑块开始X轴坐标
    int endX;                       //滑块结束X轴坐标
    QTimer *timer;                  //定时器绘制

private slots:
    void change();
    void updateValue();

public:
    int getSpace()                  const;
    int getRectRadius()             const;
    bool getChecked()               const;
    bool getShowText()              const;
    bool getAnimation()             const;

    ButtonStyle getButtonStyle()    const;

    QColor getBgColorOff()          const;
    QColor getBgColorOn()           const;
    QColor getSliderColorOff()      const;
    QColor getSliderColorOn()       const;
    QColor getTextColorOff()        const;
    QColor getTextColorOn()         const;

    QString getTextOff()            const;
    QString getTextOn()             const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
    //设置间隔
    void setSpace(int space);
    //设置圆角角度
    void setRectRadius(int rectRadius);
    //设置是否选中
    void setChecked(bool checked);
    //设置是否显示文字
    void setShowText(bool showText);
    //设置是否动画过渡
    void setAnimation(bool animation);

    //设置风格样式
    void setButtonStyle(const ButtonStyle &buttonStyle);

    //设置背景颜色
    void setBgColorOff(const QColor &bgColorOff);
    void setBgColorOn(const QColor &bgColorOn);

    //设置滑块颜色
    void setSliderColorOff(const QColor &sliderColorOff);
    void setSliderColorOn(const QColor &sliderColorOn);

    //设置文字颜色
    void setTextColorOff(const QColor &textColorOff);
    void setTextColorOn(const QColor &textColorOn);

    //设置文字
    void setTextOff(const QString &textOff);
    void setTextOn(const QString &textOn);

Q_SIGNALS:
    void checkedChanged(bool checked);
};

#endif // ALARMVOICEPAGE_H
