#pragma once
#include "renderer.h"

void RenderThreadFunc(Renderer* renderer) {
    int frame = 0;
    while (renderer != nullptr) {
        renderer->FrameBegin();
        
        // renderTest
        renderer->DrawDot(50, 50, 255, 0, 0);  // red
        renderer->DrawLine(10, 10, 1000, 100, 0, 255, 0);  // green
        renderer->DrawTriangle(150, 50, 200, 150, 100, 150, 0, 0, 255);  // triangle
        
        // dynamic point
        int x = (frame % 200) + 50;
        renderer->DrawDot(x, 200, 255, 255, 0);  // yellow moving point
        
        frame++;
        renderer->FrameEnd();
        Sleep(16);
    }
}
