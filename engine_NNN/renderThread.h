#pragma once
#include "renderer.h"

void RenderThreadFunc(Renderer* renderer) {
    int frame = 0;
    while (renderer != nullptr) {
        renderer->FrameBegin();
        
        // 测试绘制
        renderer->DrawDot(50, 50, 255, 0, 0);  // 红点
        renderer->DrawLine(10, 10, 1000, 100, 0, 255, 0);  // 绿线
        renderer->DrawTriangle(150, 50, 200, 150, 100, 150, 0, 0, 255);  // 蓝三角形
        
        // 动态效果：移动的点
        int x = (frame % 200) + 50;
        renderer->DrawDot(x, 200, 255, 255, 0);  // 黄色移动点
        
        frame++;
        renderer->FrameEnd();
        Sleep(16);
    }
}