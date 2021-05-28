#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include "Scene/Core/System.hpp"
#include "Scene/Component/ComponentBase.hpp"
#include "PlayerSound.hpp"

class PlayerSystem : public System
{
public:

    PlayerSystem();

    void Up();
    void Down();
    void Right();
    void Left();
};

class PlayerComponent : public Component::ComponentBase
{
    PlayerSound _playerSound;

public:
    PlayerComponent();

    PlayerSound& GetPlayerSound();

};

#endif //_PLAYER_HPP