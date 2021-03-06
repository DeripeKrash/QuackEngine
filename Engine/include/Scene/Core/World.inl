#include "Scene/Component/RigidBody.hpp"

template<typename T>
void World::RegisterComponent() const
{
    if (std::is_base_of<Component::ComponentBase, T>())
        _componentManager->RegisterComponent<T>();
    else
        Log_Error("The class you're trying to register isn't a child of Component: {}", demangle(typeid(T).name()));

}

template<typename T>
inline void World::AddComponent(Entity id, T component) const
{
    Component::ComponentBase::LinkEntityToComponent(id, &component);
    Log_Info("Adding component: {}", demangle(typeid(T).name()));
    _componentManager->AddComponent<T>(id, component);

    auto signature = _entityManager->GetSignature(id);
    signature.set(_componentManager->GetComponentType<T>(), true);
    _entityManager->SetSignature(id, signature);

    _systemManager->EntitySignatureChanged(id, signature);
}

template<typename T>
inline void World::RemoveComponent(Entity id)
{
    Log_Info("Remove component: {} from {}", demangle(typeid(T).name()), id);

    _componentManager->RemoveComponent<T>(id);

    auto signature = _entityManager->GetSignature(id);
    signature.set(_componentManager->GetComponentType<T>(), false);

    _entityManager->SetSignature(id, signature);
    _systemManager->EntitySignatureChanged(id, signature);
}

template<>
inline void World::RemoveComponent<Component::RigidBody>(Entity id)
{
    fmt::print(fg(fmt::color::forest_green), "[ECS] Remove component: {} from {}\n",
               demangle(typeid(Component::RigidBody).name()), id);

    _physicsWorld->destroyRigidBody(GetComponent<Component::RigidBody>(id).rb);
    _componentManager->RemoveComponent<Component::RigidBody>(id);

    auto signature = _entityManager->GetSignature(id);
    signature.set(_componentManager->GetComponentType<Component::RigidBody>(), false);

    _entityManager->SetSignature(id, signature);
    _systemManager->EntitySignatureChanged(id, signature);
}

template<typename T>
T &World::GetComponent(Entity id) const
{
    return _componentManager->GetComponent<T>(id);
}

template<typename T>
bool World::HasComponent(Entity id) const
{
    return _componentManager->HasComponent<T>(id);
}

template<typename T>
ComponentType World::GetComponentType()
{
    return _componentManager->GetComponentType<T>();
}

template<typename T>
T *World::RegisterSystem() const
{
    return _systemManager->RegisterSystem<T>();
}

template<typename T>
void World::SetSystemSignature(Signature signature)
{
    _systemManager->SetSignature<T>(signature);
}

inline const std::string &World::GetName() const
{
    return _name;
}

inline const std::unique_ptr<EntityManager> &World::GetEntityManager() const
{
    return _entityManager;
}

//inline const std::unique_ptr<SystemManager> &World::GetSystemManager() const
//{
//    return _systemManager;
//}

template<class T>
T *World::GetSystem()
{
    return _systemManager->GetSystem<T>();
}