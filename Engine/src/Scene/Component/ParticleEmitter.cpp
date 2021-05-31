#include "Scene/Component/ParticleEmitter.hpp"

#include "Engine.hpp"
#include "Scene/Core/World.hpp"

#include "Renderer/Texture.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Framebuffer.hpp"

#include "Scene/System/CameraSystem.hpp"

using namespace Component;
using namespace Renderer;


ParticleEmitter::ParticleEmitter(unsigned int size, float duration, const Shader& shader, const Texture& texture) :
        _duration(duration), _shader(shader), _texture(texture)
{
    _listParticle.resize(size);

    for (unsigned int i = 0; i < _listParticle.size(); i++)
    {
        _listParticle[i].life = (float)i / (float)size;
    }
}

void ParticleEmitter::Process(const Renderer::Framebuffer &buffer, const Renderer::Mesh &screenMesh)
{
    float deltaTime = (float)Engine::Instance().GetTimeManager().GetDeltaTime();
    float minus = deltaTime / _duration;

    buffer.Bind();
    _shader.Use();
    _texture.Bind();

    Component::Camera &camera = Engine::Instance().GetCurrentWorld().GetSystem<CameraSystem>()->GetActiveCamera();

    _shader.SetMatrix4("projection", camera.GetProjection());
    _shader.SetMatrix4("view", camera.GetView());

    for (unsigned int i = 0; i < _listParticle.size(); i++)
    {
        _listParticle[i].life -= minus;
        if (_listParticle[i].life < 0.0f)
        {
            ResetParticle(_listParticle[i]);
        }

        DrawParticle(_listParticle[i], screenMesh);
    }
}

void ParticleEmitter::ResetParticle(Particle &particle)
{
    particle.life = 0;
    auto trs = Engine::Instance().GetCurrentWorld().GetComponent<Component::Transform>(_entity);

    particle.position = trs.position;
}

void ParticleEmitter::DrawParticle(const Particle &particle, const Renderer::Mesh &screenMesh)
{
    _shader.SetVector4f("color", particle.color);
    _shader.SetMatrix4("model", Maths::Matrix4::Translate(particle.position));

    screenMesh.Draw();
}
