#ifndef _ANIMATOR_HPP
#define _ANIMATOR_HPP

#include "Scene/Component/ComponentBase.hpp"

#include "Maths/Matrix4.hpp"

#include "Renderer/Animation.hpp"
#include "Renderer/Shader.hpp"
#include "Scene/Component/Model.hpp"

#include <vector>
#include <unordered_map>

namespace Component
{
    class Animator : public ComponentBase
    {
        std::vector<Maths::Matrix4> _bonesOffset;
        Renderer::Animation _currentAnimation;

        float _currentTime {0.f};

        const std::vector<Maths::Matrix4>& GetBonesOffsets() const;

        void CalculateBoneTransform(const Renderer::NodeData& node, Maths::Matrix4 parentMatrixWorld);

    public:

        Animator() = default;
        explicit Animator(Renderer::Animation& animation);
        void SetAnimation(Renderer::Animation& animation);

        void Update(float deltaTime);
        void SetShader(Renderer::Shader& shader);

        void PlayAnimation(Renderer::Animation& animation);

        const Renderer::Animation& GetAnimation() const;

    };
}

#endif //_ANIMATOR_HPP
