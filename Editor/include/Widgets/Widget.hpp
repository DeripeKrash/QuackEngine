//
// Created by g.nisi on 2/26/21.
//

#ifndef QUACKENGINE_WIDGET_HPP
#define QUACKENGINE_WIDGET_HPP


#include <string>
#include <imgui.h>
#include <imgui_internal.h>
#include "Scene/Core/Types.hpp"

#define PROPERTIES_SHOW_ENTITY true
#define PROPERTIES_SHOW_ASSET false


class Widget
{
protected:
    std::string _title;
    bool _visible{true};
    float _position[2]{0.f, 0.f};
    float _size[2]{0.f, 0.f};

    ImGuiWindowFlags _windowFlags = 0;

    Widget() = default;

    static bool _propertiesSwitch;
    static Entity _entity;
    static std::string _assetName;

public:
    virtual ~Widget() = default;

    void Draw();

    virtual void UpdateBefore()
    {};

    virtual void UpdateVisible() = 0;

    //todo
//    virtual void OnShow()
//    {};
//
//    virtual void OnHide()
//    {};

    bool IsVisible() const;

    void SetVisible(bool visible);

};

inline bool Widget::IsVisible() const
{
    return _visible;
}

inline void Widget::SetVisible(bool visible)
{
    _visible = visible;
}

inline void Widget::Draw()
{
    UpdateBefore();

    if (!_visible)
        return;

    if (ImGui::Begin(_title.c_str(), &_visible, _windowFlags))
    {
        UpdateVisible();
    }

    ImGui::End();

}
inline bool Widget::_propertiesSwitch = true;
inline Entity Widget::_entity = 0;
inline std::string Widget::_assetName = std::string();

#endif //QUACKENGINE_WIDGET_HPP
