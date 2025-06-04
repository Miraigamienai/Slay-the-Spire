#include "Game_object/dungeon/Death_screen.hpp"
#include "Game_object/effect/Fade_wide.hpp"
#include "Game_object/character/Player.hpp"
#include "RUtil/Text_Vector_Reader.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Dungeon{
    static inline auto &TEXT_VEC()noexcept(noexcept(RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::DeathScreen))){
        return RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::DeathScreen);
    }

    Death_screen::Death_screen()
        :Is_screen(Abstraction::ScreenType::death)
    {
        return_button.move(static_cast<float>(Setting::WINDOW_WIDTH)/2.0F, static_cast<float>(Setting::WINDOW_HEIGHT)*0.15F);
        return_button.set_text(TEXT_VEC()[34]);
    }

    void Death_screen::update(Dungeon::Dungeon_shared &dungeon_shared){
        return_button.update();
    }

    void Death_screen::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetColor(RUtil::BLACK, 0.75F);
        r2->draw(Effect::Fade_wide::white_square, 0.0F, 0.0F, static_cast<float>(Setting::WINDOW_WIDTH), static_cast<float>(Setting::WINDOW_HEIGHT));
        player->render(r2);
        monsters.render(r2);
        return_button.render(r2);
    }

    void Death_screen::open(const std::shared_ptr<Character::Player> &player, const Monster::Monster_group &monsters){
        this->player=player;
        this->monsters=monsters;
    }
}