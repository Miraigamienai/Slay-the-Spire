#include "Game_object/dungeon/Complete_screen.hpp"
#include "Game_object/effect/Fade_wide.hpp"
#include "Game_object/character/Player.hpp"
#include "RUtil/Text_Vector_Reader.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"
#include "WindowSize.hpp"

namespace Dungeon{
    static inline auto &TEXT_VEC()noexcept(noexcept(RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::DeathScreen))){
        return RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::DeathScreen);
    }

    Complete_screen::Complete_screen()
        :Is_screen(Abstraction::ScreenType::complete)
    {
        return_button.move(static_cast<float>(Setting::WINDOW_WIDTH)/2.0F, static_cast<float>(Setting::WINDOW_HEIGHT)*0.15F);
        return_button.set_text(TEXT_VEC()[34]);
    }

    void Complete_screen::update(Dungeon::Dungeon_shared &dungeon_shared){
        return_button.update();
    }

    void Complete_screen::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetColor(RUtil::WHITE,0.8F);
        r2->draw(IMG,0.0F,0.0F,Setting::WINDOW_WIDTH, Setting::WINDOW_HEIGHT, 0.0F, 0.0F, 0.0F);
        player->render(r2);
        return_button.render(r2);
        
    }

    void Complete_screen::open(const std::shared_ptr<Character::Player> &player, const Monster::Monster_group &monsters){
        this->player=player;
    }
    const std::shared_ptr<Draw::ReTexture>  &Complete_screen::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/complete/ascenders_bane.png");
}