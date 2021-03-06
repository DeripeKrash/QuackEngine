#include "Scene/System/CameraSystem.hpp"
#include "Scene/Core/World.hpp"

#include "Engine.hpp"
#include "Scene/Component/Transform.hpp"

using namespace Maths;
using namespace Component;
CameraSystem::CameraSystem(): _engine{Engine::Instance()}
{}

Component::Camera& CameraSystem::GetActiveCamera()
{
    World& world = _engine.GetCurrentWorld();
    for (Entity entity: _entities) {
        auto &cam = world.GetComponent<Component::Camera>(entity);

        if (cam.isActive)
        {
            _activeCamera = entity;
            // todo : en vrai ref ce serait bien mais on doit inverser la scale du z
            Transform trs = world.GetComponent<Transform>(entity);
            trs.scale.z *=-1;// -fabsf(trs.scale.z); // revert Z axis of the camera
            cam.SetView(trs.GetMatrix().GetInvert());
            return cam;
        }
    }

//    Assert_Fatal_Error(true, "No Camera Active");
//    exit(-1);
//
    {
        Entity newCamera = world.CreateEntity("Camera");
        Component::Transform transform(Vector3f::Zero(), Vector3f::One(), Quaternion::Identity());
        Vector2i size = Engine::Instance().GetWindowSize();
        Component::Camera cameraComponent(size.x, size.y, 100.f, 0.1f, 45.f * DegToRad<float>());
        world.AddComponent(newCamera, transform);
        world.AddComponent(newCamera, cameraComponent);
        return world.GetComponent<Component::Camera>(newCamera);
    }
}

void CameraSystem::Clear()
{
    World &world = _engine.GetCurrentWorld();
    for (Entity entity: _entities)
    {
        auto &t = world.GetComponent<Camera>(entity);
        t.GetFramebuffer().Delete();
    }
}