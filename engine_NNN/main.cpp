#include <windows.h>
#include <stdio.h>
#include <thread>
#include "createWin.h"
#include "renderer.h"
#include "renderThread.h"

int width, height;

int main() {
    HWND hwnd = createWin();
    if (!hwnd) return -1;

    // 创建渲染器和渲染线程
    Renderer* renderer = new Renderer(hwnd);
    std::thread renderThread(RenderThreadFunc, renderer);

    MSG msg;
    while (GetMessage(&msg, 0, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // 清理
    delete renderer;
    renderer = nullptr;
    if (renderThread.joinable()) renderThread.join();
    return 0;
}