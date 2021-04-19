#ifndef __INPUTMANAGER_HPP__
#define __INPUTMANAGER_HPP__


#include <map>
#include <memory>
#include <iostream>
#include <functional>
#include <vector>
#include "PlatformInput.hpp"

namespace Input
{
    class InputManager
    {
    private:
        PlatformInput *_platformInput = nullptr;

        std::unordered_map<std::string, std::vector<std::pair<std::function<void()>, Action>>> _eventFuncs;
        std::unordered_map<std::string, std::vector<std::function<void(float)>>> _eventFuncsAxis;

        std::unordered_map<std::string, std::vector<Key>> _eventKeys;
        std::unordered_map<std::string, std::vector<std::pair<Key, float>>> _eventKeysAxis;
        std::unordered_map<std::string, std::vector<MouseButton>> _eventMouseButtons;

        void OnKeyEvent(Action action, Key key);
        void OnMouseButtonEvent(Action action, MouseButton button);
        void OnUpdateMousePositionEvent(double xPos, double yPos);
        void InitInput();// todo: Remove this function by serialisation of BindEvent

    public:
        InputManager() = default;

        void Init(PlatformInput *platformInput);
        void BindEvent(const std::string &event, Key key);
        void BindEvent(const std::string &event, MouseButton key);
        void BindEventAxis(const std::string &event, Key key, float scale);

        template<typename C, typename F>
        void RegisterEvent(const std::string &event, Action action, C *classObject, F &&function);

        template<typename C, typename F>
        void RegisterEventAxis(const std::string &event, C *classObject, F &&function);
        void Update();

        MousePosition mousePosition;
    };

    template<typename C, typename F>
    inline void InputManager::RegisterEvent(const std::string &event, Action action, C *classObject, F &&function)
    {
        _eventFuncs[event].push_back(
                std::pair<std::function<void()>, Action>(std::bind(function, classObject), action));
    }

    template<typename C, typename F>
    inline void InputManager::RegisterEventAxis(const std::string &event, C *classObject, F &&function)
    {
        _eventFuncsAxis[event].push_back(std::bind(function, classObject, std::placeholders::_1));
    }
}

#endif