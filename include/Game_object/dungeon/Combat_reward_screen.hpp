#pragma once

#include "Game_object/interface/Is_screen.hpp"

class Combat_reward_screen final:public Interface::Is_screen
{
public:
    Combat_reward_screen();
    ~Combat_reward_screen()override=default;
};
