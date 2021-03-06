#ifndef QUACKENGINE_ENGINE_HPP
#define QUACKENGINE_ENGINE_HPP

#include <vector>
#include <map>
#include <memory>
#include <string>

#include <reactphysics3d/engine/PhysicsCommon.h>

#include "Resources/ResourcesManager.hpp"
#include "Renderer/RendererInterface.hpp"
#include "Renderer/PostProcessManager.hpp"
#include "Audio/SoundManager.hpp"
#include "reactphysics3d/engine/PhysicsCommon.h"
#include "Time/TimeManager.hpp"

#include "Physics/PhysicsCollisionCallback.hpp"

#include "Input/InputManager.hpp"
#include "Input/PlatformInput.hpp"
#include "Input/PlatformInputGLFW.hpp"

#include "Physics/PhysicsEventManager.hpp"

#include <filesystem>

namespace cereal
{
    class JSONOutputArchive;
};

enum class WINDOW_MODE
{
    WINDOWED,
    FULLSCREEN,
    WINDOWED_FULLSCREEN,
};

enum class INPUT_MODE
{
    GLFW,
};

struct EngineSettings
{
    bool debug{};
    std::string windowTitle{};
    int windowSize[2]{};
    WINDOW_MODE mode{};
    int monitor = 0;
    INPUT_MODE inputMode;
};

class Engine
{
private:
    class GLFWwindow *_window = nullptr;

    std::unique_ptr<Input::PlatformInput> _platformInput;

    Renderer::RendererInterface _rendererInterface; //init after world loading
    Resources::ResourcesManager _resourcesManager;
    Audio::SoundManager _soundManager;
    PhysicsEventManager _physicsEventManager;
    PhysicsCollisionCallback _physicsCollisionCallback;
    reactphysics3d::PhysicsCommon _physicsManager;
    Input::InputManager _inputManager;
    Time::TimeManager _timeManager;
    Renderer::PostProcessManager _postProcessManager;

    uint_fast16_t _currentWorld = 0;
    std::map<std::string, uint_fast16_t> _worldLut;
    std::vector<class World> _worlds;

    double _timeAcc{0.};
    unsigned int _frames{0};
    float _fps{0.};
    void FillTexture(Renderer::Texture &T);
    bool _gamePlaying{false};

public:
    static Engine &Instance() noexcept;
    static void SetInstance(Engine &engine);

    explicit Engine(const EngineSettings &settings) noexcept;
    ~Engine();

    GLFWwindow *GetWindow();
    void SetWindowTitle(const std::string &title);
    void SetWindowSize(int width, int height);
    Maths::Vector2i GetWindowSize();
    void UpdateTime();
    double GetDeltaTime();

    bool WindowShouldClose();
    void TestWindowShouldClose();
    void CloseWindows();
    void SwapBuffers();

    float GetFps() const;
    bool IsGamePlaying() const;
    void SetGamePlaying(bool gamePlaying);

    class World &GetCurrentWorld();
    void SetCurrentWorld(const std::string& name);
    class World &CreateWorld(std::string name);
    void LoadWorld(class World &world);
    void SaveWorld(const std::string &worldName);
    void ClearWorld(const std::string &worldName);
    void RemoveWorld(const std::string &name);
    std::vector<std::string> GetWorldList() const;

    Input::InputManager &GetInputManager();
    Renderer::RendererInterface &GetRendererInterface();
    Resources::ResourcesManager &GetResourcesManager();
    Audio::SoundManager &GetSoundManager();
    PhysicsEventManager &GetPhysicsEventManager();
    PhysicsCollisionCallback &GetPhysicsCollisionCallback();
    reactphysics3d::PhysicsCommon &GetPhysicsManager();
    Time::TimeManager &GetTimeManager();
    Renderer::PostProcessManager &GetPostProcessManager();


};

#endif //QUACKENGINE_ENGINE_HPP
