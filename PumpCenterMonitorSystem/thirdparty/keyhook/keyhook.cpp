/**
* @FileName             keyhook.cpp
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2020-10-05
* @Author               fuliping
* @email
* @Create Date          2020-10-05
* @
*/
#include <QDebug>
#include <QMutexLocker>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

#include "keyhook.h"

Q_GLOBAL_STATIC(QMutex, lock)
KeyHook*  KeyHook::m_pInstance = Q_NULLPTR;

#define WIN_KEY 0x8000

#ifdef Q_OS_WIN
static HHOOK keyhookfun = nullptr;
LRESULT CALLBACK keyProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *pkbh = (KBDLLHOOKSTRUCT*)lParam;
    if (nCode == HC_ACTION)
    {
        if (pkbh->vkCode == VK_ESCAPE && GetAsyncKeyState(VK_CONTROL) & WIN_KEY && GetAsyncKeyState(VK_SHIFT) & WIN_KEY)
            return 1;
        else if (pkbh->vkCode == VK_TAB && pkbh->flags & LLKHF_ALTDOWN)     //ALT+Tab
            return 1;
        else if (pkbh->vkCode == VK_ESCAPE && GetAsyncKeyState(VK_CONTROL) & WIN_KEY)   //Ctrl+Esc
            return 1;
        else if (pkbh->vkCode == VK_LWIN || pkbh->vkCode == VK_RWIN)        //LWIN/RWIN
            return 1;
        else if (pkbh->vkCode == VK_F4 && pkbh->flags & LLKHF_ALTDOWN)      //ALT+F4
            return 1;
        else if (pkbh->vkCode == VK_SPACE && pkbh->flags & LLKHF_ALTDOWN)   //ALT+Space
            return 1;
//        else if (pkbh->vkCode == VK_TAB)     //Tab
//            return 1;
        else if (pkbh->vkCode == VK_ESCAPE && pkbh->flags & LLKHF_ALTDOWN)   //ALT+ESC
            return 1;
        else
            return 0;
    }

    return CallNextHookEx(keyhookfun, nCode, wParam, lParam);
}
#endif

KeyHook* KeyHook::instance()
{
    if (m_pInstance == Q_NULLPTR)
    {
        QMutexLocker locker(lock);
        if (m_pInstance == Q_NULLPTR)
        {
            m_pInstance = new KeyHook;
        }
    }
    return m_pInstance;
}

KeyHook::KeyHook()
{
}

KeyHook::~KeyHook()
{
    exitKeyHook();
}

bool KeyHook::initKeyHook()
{
#ifdef Q_OS_WIN
    keyhookfun = SetWindowsHookEx(WH_KEYBOARD_LL, keyProc, nullptr, 0);
#endif
    return true;
}

void KeyHook::exitKeyHook()
{
#ifdef Q_OS_WIN
    if (keyhookfun != nullptr)
        UnhookWindowsHookEx(keyhookfun);
#endif
    keyhookfun = nullptr;
}
