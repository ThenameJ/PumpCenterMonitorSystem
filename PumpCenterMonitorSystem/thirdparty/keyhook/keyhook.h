/**
* @FileName             keyhook.h
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2020-10-05
* @Author               fuliping
* @email
* @Create Date          2020-10-05
* @
*/
#ifndef KEYHOOK_H
#define KEYHOOK_H

class KeyHook
{
public:
    KeyHook();
    virtual ~KeyHook();

public:
    bool initKeyHook();

    void exitKeyHook();

    static KeyHook *instance();

private:
    static KeyHook  *m_pInstance;
};
#define keyhook KeyHook::instance()

#endif // KEYHOOK_H
