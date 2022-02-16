/**
* @FileName             mainmenu.h
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-09-25 14:48:38
* @Author               zhoumingjie
* @email
* @Create Date          2021-09-25 14:48:38
* @
*/

#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QPushButton>
#include <QWidgetAction>
#include <QPixmap>
#include <QPaintEvent>
#include <QPainter>


class MainMenu : public QWidget
{
    Q_OBJECT
public:
    MainMenu(QWidget *parent = nullptr);
    virtual ~MainMenu();

private:
    /**
     * @brief initMenu
     */
    void initMenu();

private:
    QPushButton     *m_pStatusButton = Q_NULLPTR;
    QMenu           *m_pmainMenu;
    QAction         *m_pSetting = Q_NULLPTR;
    QAction         *m_pExit = Q_NULLPTR;

};


class MenuItemWidget : public QWidget
{
    Q_OBJECT

public:
    MenuItemWidget(QWidget *parent = nullptr);
    ~MenuItemWidget();
    /**
     * @brief setPixmap
     * @param pix
     */
    void setPixmap(const QPixmap &pix);
    /**
     * @brief setText
     * @param text
     */
    void setText(const QString &text);

protected:
    virtual void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    virtual void enterEvent(QEvent *event) Q_DECL_OVERRIDE;

    virtual void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;

    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);


signals:
    void clicked();

private:
    bool    m_bEnter = false;
    bool    m_bEnable = true;
    QPixmap m_pixmap;
    QString m_text = "NULL";
    bool    m_mousePressed = false;

};



#endif // MAINMENU_H
