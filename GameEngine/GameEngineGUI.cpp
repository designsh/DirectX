#include "PreCompile.h"
#include "GameEngineGUI.h"

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "GameEngineWindow.h"
#include "GameEngineDevice.h"

GameEngineGUI* GameEngineGUI::Inst = new GameEngineGUI();

GameEngineGUI::GameEngineGUI()
{
}

GameEngineGUI::~GameEngineGUI()
{
    for (auto& Window : Windows_)
    {
        delete Window.second;
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void GameEngineGUI::Initialize()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplWin32_Init(GameEngineWindow::GetInst().GetWindowHWND());
    ImGui_ImplDX11_Init(GameEngineDevice::GetDevice(), GameEngineDevice::GetContext());

    GameEngineWindow::SetMessageCallBack(ImGui_ImplWin32_WndProcHandler);
}

void GameEngineGUI::GUIRenderStart()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    for (auto& Window : Windows_)
    {
        if (false == Window.second->IsUpdate())
        {
            continue;
        }

        Window.second->Begin();
        Window.second->OnGUI();
        Window.second->End();
    }
}

void GameEngineGUI::GUIRenderEnd()
{
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImGui::Render();

    // GameEngineDevice::window

    // const float clear_color_with_alpha[4] = { 0.5f * 1.0f, 0.5f * 1.0f, 0.5f * 1.0f, 1.0f };
    // g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
    // g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    // Update and Render additional Platform Windows
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}
