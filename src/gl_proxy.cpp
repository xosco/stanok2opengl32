#include "gl_proxy.h"
#include <GL/gl.h>
#include <cstdio>
#include <cstdarg>
#include <string>
#include <set>
#include <iostream>

extern "C" {

typedef void (WINAPI* PFN_glEnable)(GLenum cap);
typedef void (WINAPI* PFN_glDisable)(GLenum cap);
typedef void (WINAPI* PFN_glDrawElements)(GLenum mode, GLsizei count, GLenum type, const void* indices);
typedef void (WINAPI* PFN_glDrawRangeElements)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices);
typedef void (WINAPI* PFN_glDrawArrays)(GLenum mode, GLint first, GLsizei count);
typedef PROC (WINAPI* PFN_wglGetProcAddress)(LPCSTR name);

HMODULE g_realGL = nullptr;
static PFN_glEnable real_glEnable = nullptr;
static PFN_glDisable real_glDisable = nullptr;
static PFN_glDrawElements real_glDrawElements = nullptr;
static PFN_glDrawRangeElements real_glDrawRangeElements = nullptr;
static PFN_glDrawArrays real_glDrawArrays = nullptr;
static PFN_wglGetProcAddress real_wglGetProcAddress = nullptr;

std::set<int> seen_counts;

void CreateDebugConsole() {
    if (AllocConsole()) {
        freopen("CONOUT$", "w", stdout);
        std::cout << "=== STANDOFF 2 SURGICAL WH ===" << std::endl;
        std::cout << "F3 - Clear ID Log | F2 - Toggle Search Mode" << std::endl;
    }
}

bool InitRealGL() {
    if (g_realGL) return true;
    CreateDebugConsole();
    char sysPath[MAX_PATH]; GetSystemDirectoryA(sysPath, MAX_PATH);
    std::string dllPath = std::string(sysPath) + "\\opengl32.dll";
    g_realGL = LoadLibraryA(dllPath.c_str());
    if (g_realGL) {
        real_wglGetProcAddress = (PFN_wglGetProcAddress)GetProcAddress(g_realGL, "wglGetProcAddress");
        real_glEnable = (PFN_glEnable)GetProcAddress(g_realGL, "glEnable");
        real_glDisable = (PFN_glDisable)GetProcAddress(g_realGL, "glDisable");
        real_glDrawElements = (PFN_glDrawElements)GetProcAddress(g_realGL, "glDrawElements");
        real_glDrawRangeElements = (PFN_glDrawRangeElements)GetProcAddress(g_realGL, "glDrawRangeElements");
        real_glDrawArrays = (PFN_glDrawArrays)GetProcAddress(g_realGL, "glDrawArrays");
    }
    return (g_realGL != nullptr);
}

void* GetRealGLProc(const char* name) {
    if (!g_realGL) InitRealGL();
    return (void*)GetProcAddress(g_realGL, name);
}

// ГЛАВНЫЙ ФИЛЬТР (Что мы хотим видеть сквозь стены)
bool IsPlayer(int count) {
    // В Стандофф персонажи обычно в этом диапазоне
    // Если мы нашли правильное число - WH заработает
    if (count == 4932 || count == 1242 || (count > 2000 && count < 6000)) {
        return true;
    }
    return false;
}

void Log(const char* fmt, ...) {
    // Оставляем пустым чтобы не тормозило
}

// Оптимизированная отрисовка
void WINAPI my_glDrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices) {
    if (!real_glDrawElements) real_glDrawElements = (PFN_glDrawElements)GetRealGLProc("glDrawElements");

    if (IsPlayer(count)) {
        real_glDisable(GL_DEPTH_TEST); // ВХ только для цели
        real_glDrawElements(mode, count, type, indices);
        real_glEnable(GL_DEPTH_TEST);
    } else {
        real_glDrawElements(mode, count, type, indices);
    }
}

void WINAPI my_glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices) {
    if (!real_glDrawRangeElements) real_glDrawRangeElements = (PFN_glDrawRangeElements)GetRealGLProc("glDrawRangeElements");

    if (IsPlayer(count)) {
        real_glDisable(GL_DEPTH_TEST);
        real_glDrawRangeElements(mode, start, end, count, type, indices);
        real_glEnable(GL_DEPTH_TEST);
    } else {
        real_glDrawRangeElements(mode, start, end, count, type, indices);
    }
}

void WINAPI my_glDrawArrays(GLenum mode, GLint first, GLsizei count) {
    if (!real_glDrawArrays) real_glDrawArrays = (PFN_glDrawArrays)GetRealGLProc("glDrawArrays");
    // Игроки редко рисуются через Arrays, поэтому тут просто оригинал
    real_glDrawArrays(mode, first, count);
}

PROC WINAPI my_wglGetProcAddress(LPCSTR name) {
    if (!real_wglGetProcAddress) InitRealGL();
    std::string n(name);
    if (n == "glDrawElements") return (PROC)my_glDrawElements;
    if (n == "glDrawRangeElements") return (PROC)my_glDrawRangeElements;
    if (n == "glDrawArrays") return (PROC)my_glDrawArrays;
    return real_wglGetProcAddress(name);
}

void ShutdownRealGL() { if (g_realGL) FreeLibrary(g_realGL); }

} // extern "C"