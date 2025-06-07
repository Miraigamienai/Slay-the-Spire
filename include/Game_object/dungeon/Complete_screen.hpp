#pragma once

#include "Game_object/abstraction/Is_screen.hpp"
#include "Game_object/button/Return_to_start_button.hpp"
#include "Game_object/character/Monster_group.hpp"

//fwd decl
namespace Character{
    class Player;
}

namespace Dungeon{
class Complete_screen final:public Abstraction::Is_screen
{
public:
    Complete_screen();
    ~Complete_screen()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    bool BackToInitScreen()noexcept(noexcept(return_button.Clicked())){return return_button.Clicked();}
    void open(const std::shared_ptr<Character::Player> &player, const Monster::Monster_group &monsters);
private:
    Button::Return_to_start_button return_button;
    Monster::Monster_group monsters;
    std::shared_ptr<Character::Player> player;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
};
}