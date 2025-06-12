#include "Game_object/dungeon/Victory_screen.hpp"
#include "Game_object/effect/Fade_wide.hpp"
#include "Game_object/character/Player.hpp"
#include "RUtil/Text_Vector_Reader.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Dungeon{
    static inline auto &TEXT_VEC()noexcept(noexcept(RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::VictoryScreen))){
        return RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::VictoryScreen);
    }

    Victory_screen::Victory_screen()
        :Is_screen(Abstraction::ScreenType::victory)
    {
        return_button.move(static_cast<float>(Setting::WINDOW_WIDTH)/2.0F, static_cast<float>(Setting::WINDOW_HEIGHT)*0.15F);
        return_button.set_text(TEXT_VEC()[12]);
    }

    void Victory_screen::update(Dungeon::Dungeon_shared &dungeon_shared){
        return_button.update(); 
    }

    void Victory_screen::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetColor(RUtil::WHITE);
        r2->draw(IMG,0.0F,0.0F,Setting::WINDOW_WIDTH, Setting::WINDOW_HEIGHT, 0.0F, 0.0F, 0.0F);
        return_button.render(r2);
        
    }
    const std::shared_ptr<Draw::ReTexture>  &Victory_screen::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/victory/background.jpg");
}