#include "Widgets/ViewportWidget.hpp"
#include "Renderer/Framebuffer.hpp"
#include "Renderer/RendererInterface.hpp"
#include "Scene/System/CameraSystem.hpp"
#include "Engine.hpp"

#include "GLFW/glfw3.h"

using namespace Renderer;

ViewportWidget::ViewportWidget()
{
    _title = "Viewport";

}

void ViewportWidget::UpdateVisible()
{
//    ImGuiIO& io = ImGui::GetIO();

//    if(ImGui::IsMouseReleased(0) && ImGui::IsItemHovered())
//    {
//        io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
//        ImGui::SetMouseCursor(ImGuiMouseCursor_None);
//        std::cout << "Click!\n";
//    }

    ImGui::BeginChild("ViewportRender");
    // Get the size of the child (i.e. the whole draw size of the windows).
    const ImVec2 wsize = ImGui::GetWindowSize();

    RendererInterface &rendererInterface = Engine::Instance().GetRendererInterface();

    Engine::Instance().GetCurrentWorld().GetSystemManager()->GetSystem<CameraSystem>()->GetActiveCamera().Resize(wsize.x, wsize.y);
    Framebuffer f = rendererInterface.GetSceneUpdatedFramebuffer();

    ImGui::Image((ImTextureID) (size_t) f.GetTexture(), wsize, ImVec2(0, 1), ImVec2(1, 0));

    ViewportWidget::LockCursor();

    ImGui::EndChild();
}

void ViewportWidget::LockCursor()
{
    ImGuiIO &io = ImGui::GetIO();
//    if(ImGui::IsMouseDoubleClicked(0) && ImGui::IsItemHovered(0))
//    {
//        io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
//        ImGui::SetMouseCursor(ImGuiMouseCursor_None);
//        std::cout << "Oui\n";
//    }

    GLFWwindow *window = Engine::Instance().GetWindow();
    auto cameraSystem = Engine::Instance().GetCurrentWorld().GetSystemManager()->GetSystem<CameraSystem>();
    if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS && !_isInGame)
    {
        io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        _isInGame = true;
        cameraSystem->_isFreeFlyCam = true;
    }
    if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS && _isInGame)
    {
        io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        _isInGame = false;
        cameraSystem->_isFreeFlyCam = false;
    }
}
