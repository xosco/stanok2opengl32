#ifndef GL_PROXY_H
#define GL_PROXY_H

#include <windows.h>

extern "C" {
    bool InitRealGL();
    void ShutdownRealGL();
    void* GetRealGLProc(const char* name);
    void Log(const char* fmt, ...);
    void OnSwapBuffers(HDC hdc); // Для отрисовки меню/оверлея
}

#endif