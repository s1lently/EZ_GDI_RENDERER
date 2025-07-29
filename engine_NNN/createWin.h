#pragma once

#include <windows.h>
#include <stdio.h>

extern int width, height;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        EndPaint(hwnd, &ps);
        return 0;
    }
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

void buf_init(int* width, int* height) {
    printf("Width：");
    scanf("%d", width);
    printf("Height：");
    scanf("%d", height);
}

HWND createWin() {
    HINSTANCE hins = GetModuleHandle(NULL);
    int nCmdShow = SW_SHOW;

    SetConsoleOutputCP(CP_UTF8);
    buf_init(&width, &height);
    WNDCLASS wc = { 0, WndProc, 0, 0, hins, 0, 0, 0, 0, "GW" };
    RegisterClass(&wc);
    HWND hwnd = CreateWindow("GW", "GWW", WS_OVERLAPPEDWINDOW, 100, 100, width, height, 0, 0, hins, 0);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    if (!hwnd) {
        MessageBox(0, "WinCreateFailed", "Error", MB_ICONERROR);
        return NULL;
    }
    return hwnd;
}
