#include "aio_pch.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/Renderer.h"
#include "Alexio/Random.h"

#include "Alexio/Timer.h"

namespace Alexio
{
    void ImGUI::OnAttach()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGuiStyle& style = ImGui::GetStyle();
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        Renderer::GetBackend()->ImGuiBackendInit();
    }

    void ImGUI::Begin()
    {
        Renderer::GetBackend()->ImGuiBackendBegin();
    }

    void ImGUI::End()
    {
        Renderer::GetBackend()->ImGuiBackendUpdate();
    }

    void ImGUI::OnDetach()
    {
        Renderer::GetBackend()->ImGuiBackendShutDown();
        ImGui::DestroyContext();
    }

    void ImGUI::OnImGuiRender()
    {
        
    }
}