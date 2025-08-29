#pragma once
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_win32.h"
#include "../ImGui/imgui_impl_dx11.h"
#include "../Utils/Globals/Globals.h"
#include "SDK/CPed/CPed.h"
#include <vector>
#include <cmath>

// Render.cpp : レンダリングを行う処理を記述
// Features.cpp : レンダリングを行わない処理を記述

class Cheat
{
public:
    void RenderInfo();
    void RenderMenu();
    void RenderESP();
    void TriggerBot();
    void AimBot();
    void Misc();
    void UpdateList();

    

private:
    CPed local;
    uintptr_t GWorld;
    uintptr_t ViewPort;
    std::vector<CPed> EntityList;
    CPed FindBestTarget();


    


    ImColor FOV_User = { 1.f, 1.f, 1.f, 1.f };
    ImColor ESP_NPC = { 1.f, 1.f, 1.f, 1.f };
    ImColor ESP_Player = { 1.f, 1.f, 0.f, 1.f };
    ImColor ESP_Skeleton = { 1.f, 1.f, 1.f, 0.9f };
    ImColor TargetLineColor = { 1.0f, 0.0f, 0.0f, 1.0f };
    void DrawLine(ImVec2 a, ImVec2 b, ImColor color, float width)
    {
        ImGui::GetBackgroundDrawList()->AddLine(a, b, color, width);
    }
    void Circle(float x, float y, float fov_size, ImColor color, float size)
    {
        ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(x / 2.f, y / 2.f), fov_size, color, 100, size);
    }
    void String(ImVec2 pos, ImColor color, const char* text)
    {
        ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), pos, color, text, text + strlen(text), 128, 0);
    }
    void RectFilled(float x0, float y0, float x1, float y1, ImColor color, float rounding, int rounding_corners_flags)
    {
        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x0, y0), ImVec2(x1, y1), color, rounding, rounding_corners_flags);
    }
    void HealthBar(float x, float y, float w, float h, int value, int v_max)
    {
        RectFilled(x, y, x + w, y + h, ImColor(0.f, 0.f, 0.f, 0.725f), 0.f, 0);
        RectFilled(x, y, x + w, y + ((h / float(v_max)) * (float)value), ImColor(min(510 * (v_max - value) / 100, 255), min(510 * value / 100, 255), 25, 255), 0.0f, 0);
    }
    void ArmorBar(float x, float y, float w, float h, int value, int v_max)
    {
        RectFilled(x, y, x + w, y + h, ImColor(0.f, 0.f, 0.f, 0.725f), 0.f, 0);
        RectFilled(x, y, x + w, y + ((h / float(v_max)) * (float)value), ImColor(0.f, 0.65f, 1.f, 1.f), 0.0f, 0);
    }


    Vector3 LerpWithLogarithmicAcceleration(Vector3 start, Vector3 end, float t);
    uintptr_t TriggerAddress = 0;
    Vector3 currentTargetPos;
    bool hasValidTarget = false;
    Vector3 FindBestBone(CPed& ped);
};

