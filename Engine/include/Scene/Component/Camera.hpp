#ifndef QUACKENGINE_CAMERA_HPP
#define QUACKENGINE_CAMERA_HPP

#include "Maths/Matrix4.hpp"
#include "Maths/Vector3.hpp"
#include "Maths/Quaternion.hpp"

#include "Renderer/Framebuffer.hpp"

namespace Input
{
    class InputManager;
};
class CameraSystem;

namespace Component
{
    class Camera
    {

    private:
        unsigned int _width;
        unsigned int _height;

        float _far;
        float _near;

        float _scaleAxisX = 0;
        float _scaleAxisY = 0;
        float _scaleAxisZ = 0;

        float _yaw = 0;
        float _pitch = 0;

        float _speedTranslation = 0.1f;
        float _speedRotation = 0.1f;

        Renderer::Framebuffer _framebuffer;

        Maths::Matrix4 _projection;
        Maths::Matrix4 _view;

    public:

        bool isActive {true};

        friend ::CameraSystem;
        float _fov;
        bool _isPerspective{true};


        Camera(unsigned int width, unsigned int height, float far, float near, float fov);
        Camera(unsigned int width, unsigned int height, float far, float near);


        void Resize(unsigned int width, unsigned int height);

        Renderer::Framebuffer GetFramebuffer() const;

        const Maths::Matrix4& GetProjection() const;
        const Maths::Matrix4& GetView() const;

        void SetProjection(unsigned int width, unsigned int height, float far, float near,
                           float fov);
        void SetProjection(unsigned int width, unsigned int height, float far, float near);
        void CreateProjection();
        void SetView(const Maths::Matrix4& view);

        template<class Archive>
        void serialize(Archive &archive)
        {
            //archive(isActive,ambient,diffuse,specular,constant,linear,quadratic,spotAngle,outerSpotAngle);
        }

    };
}
#endif // QUACKENGINE_CAMERA_HPP
