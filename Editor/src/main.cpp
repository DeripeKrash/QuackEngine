#include "GLFW/glfw3.h"

#include "Engine.hpp"
#include "Editor.hpp"

#include "Renderer/RendererPlatform.hpp"

#include "Scene/System/AnimatorSystem.hpp"
#include "Scene/System/CharacterControllerSystem.hpp"
#include "Scene/System/PhysicsSystem.hpp"
#include "Scene/System/LightSystem.hpp"

#include "Scene/System/CameraGameplaySystem.hpp"

#include "Enemy/EnemySpawnSystem.hpp"
#include "Enemy/EnemySystem.hpp"

#include "Player/PlayerSystem.hpp"

#include "game.hpp"

using namespace Component;
using namespace Resources;


int main()
{
    EngineSettings settings{
            true,
            "QuackEditor",
            {1280, 720},
            WINDOW_MODE::WINDOWED,
            0,
            INPUT_MODE::GLFW
    };

    Engine engine(settings);
    Engine::SetInstance(engine);

    Game::Init(engine);
    engine.GetResourcesManager().LoadFolder("./Asset/");

    Editor editor{};

    while (!engine.WindowShouldClose())
    {

        /** Time Update **/
        engine.UpdateTime();
        const auto deltaTime = (float) engine.GetDeltaTime();

        /** POLL INPUT **/
        engine.GetInputManager().Update();
//        engine.TestWindowShouldClose();

        /** Editor draw **/
        editor.Draw();

        engine.GetCurrentWorld().GetSystem<LightSystem>()->Update();

        /** When editor is in play mode **/
        if (engine.IsGamePlaying())
        {
            /** UPDATE **/
            engine.GetCurrentWorld().GetSystem<PhysicsSystem>()->FixedUpdate(deltaTime);
            engine.GetCurrentWorld().GetSystem<CharacterControllerSystem>()->Update();
            engine.GetCurrentWorld().GetSystem<CameraGameplaySystem>()->Update();
            engine.GetCurrentWorld().GetSystem<Renderer::AnimatorSystem>()->Update();
            engine.GetCurrentWorld().GetSystem<PlayerSystem>()->Update();

            engine.GetCurrentWorld().GetSystem<EnemySpawnSystem>()->Update();
            engine.GetCurrentWorld().GetSystem<EnemySystem>()->Update();

        }
        engine.SwapBuffers();
        Renderer::RendererPlatform::Clear();
    }

    return 0;
}