#pragma once
#include <windows.h>

struct OverlayConfig {
    bool  enabled   = true;
    float color[4]  = {1.0f, 0.0f, 0.0f, 1.0f};
    float lineWidth = 2.0f;
};

extern OverlayConfig g_config;

void OnSwapBuffers(HDC hdc);
void DrawOverlay();
void SaveGLState();
void RestoreGLState();