#include "Scene/System/LightSystem.hpp"
#include "Scene/Core/World.hpp"
#include "Scene/Component/Transform.hpp"
#include "Engine.hpp"

using namespace Component;

void LightSystem::Update()
{
    _lastEntitiesSize = _entities.size();

    unsigned int pointNb{0}, directionalNb{0}, spotNb{0};
    World& world = Engine::Instance().GetCurrentWorld();
    for (Entity entity: _entities)
    {
        auto &t = world.GetComponent<Transform>(entity);
        auto &l = world.GetComponent<Component::Light>(entity);

        l.position = t.position;
        Maths::Vector4f direction = t.GetMatrix() * Maths::Vector4f{0,0,1,0};
        l.direction = direction.xyz;

        for (unsigned int i = 0; i < _listShaderToUpdate.size(); i++)
        {
            _listShaderToUpdate[i].Use();
            switch (l.type)
            {
                case LightType::L_POINT        : _listShaderToUpdate[i].SetPointLight(l, pointNb); break;
                case LightType::L_DIRECTIONAL  : _listShaderToUpdate[i].SetDirectionalLight(l, directionalNb); break;
                case LightType::L_SPOT         : _listShaderToUpdate[i].SetSpotLight(l, spotNb); break;
            }
        }

        switch (l.type)
        {
            case LightType::L_POINT        : pointNb++; break;
            case LightType::L_DIRECTIONAL  : directionalNb++; break;
            case LightType::L_SPOT         : spotNb++; break;
        }
    }

    for (unsigned int i = 0; i < _listShaderToUpdate.size(); i++)
    {
        _listShaderToUpdate[i].Use();
        _listShaderToUpdate[i].SetUint("nbPointLights", pointNb);
        _listShaderToUpdate[i].SetUint("nbDirectionalLights", directionalNb);
        _listShaderToUpdate[i].SetUint("nbSpotLights", spotNb);
    }
}

void LightSystem::AddShaderToUpdate(const Renderer::Shader& shader)
{
    for (unsigned int i = 0; i < _listShaderToUpdate.size(); i++)
    {
        if (shader.GetID() == _listShaderToUpdate[i].GetID())
            return;
    }

    _listShaderToUpdate.push_back(shader);
}

void LightSystem::RemoveShaderFromUpdate(const Renderer::Shader& shader)
{
    for (unsigned int i = 0; i < _listShaderToUpdate.size(); i++)
    {
        if (_listShaderToUpdate[i].GetID() == shader.GetID())
        {
            _listShaderToUpdate.erase(_listShaderToUpdate.cbegin() + i);
            return;
        }
    }
}