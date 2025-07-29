#pragma once
#include <windows.h>
#include <vector>

class Renderer {
public:
    std::vector<BYTE> canvas;
    int cW, cH;
    HWND hwnd;
    
    Renderer(HWND window) : hwnd(window), cW(0), cH(0) {
        canvas.resize(100);
    }
    
    void Present() {
        if (canvas.empty() || cW <= 0 || cH <= 0) return;
        BITMAPINFO bmi = {sizeof(BITMAPINFOHEADER), cW, -cH, 1, 32, 0};
        HDC hdc = GetDC(hwnd);
        SetDIBitsToDevice(hdc, 0, 0, cW, cH, 0, 0, 0, cH, canvas.data(), &bmi, 0);
        ReleaseDC(hwnd, hdc);
    }
    
    void FrameBegin() {
        RECT rect;
        GetClientRect(hwnd, &rect);
        cW = rect.right;
        cH = rect.bottom;
        canvas.resize(cW * cH * 4);
    }
    
    void FrameEnd() {
        Present();
        canvas.clear();
    }
    
    int TD1P2OD1C(int x, int y) {
        return (y * cW + x) * 4;
    }
    
    void DrawDot(int x, int y, BYTE r, BYTE g, BYTE b) {
        if (x >= 0 && x < cW && y >= 0 && y < cH) {
            int idx = TD1P2OD1C(x, y);
            canvas[idx] = b;          // B
            canvas[idx + 1] = g;      // G  
            canvas[idx + 2] = r;      // R
            canvas[idx + 3] = 255;    // A
        }
    }
    
    void DrawLine(int x1, int y1, int x2, int y2, BYTE r, BYTE g, BYTE b) {
        int dx = abs(x2 - x1), dy = abs(y2 - y1);
        int sx = x1 < x2 ? 1 : -1, sy = y1 < y2 ? 1 : -1;
        int err = dx - dy, e2;
        
        while (true) {
            DrawDot(x1, y1, r, g, b);
            if (x1 == x2 && y1 == y2) break;
            e2 = 2 * err;
            if (e2 > -dy) { err -= dy; x1 += sx; }
            if (e2 < dx) { err += dx; y1 += sy; }
        }
    }
    
    void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, BYTE r, BYTE g, BYTE b) {
        DrawLine(x1, y1, x2, y2, r, g, b);
        DrawLine(x2, y2, x3, y3, r, g, b);
        DrawLine(x3, y3, x1, y1, r, g, b);
    }
};