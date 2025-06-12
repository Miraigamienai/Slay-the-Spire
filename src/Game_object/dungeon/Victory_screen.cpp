#include "Game_object/dungeon/Victory_screen.hpp"
#include "Game_object/effect/Fade_wide.hpp"
#include "Game_object/character/Player.hpp"
#include "RUtil/Text_Vector_Reader.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/card/Cards.hpp"
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
        current_gold=dungeon_shared.player->GetGold();
        current_floor=dungeon_shared.current_node->y+1;
        current_HP=dungeon_shared.player->GetCurrentHP();
        for(auto&it:card_amount){
            it=0;
        }
        for(const auto&it:dungeon_shared.card_group_handler.GetCardsGroup<Card::GroupType::master_deck>()){
            card_amount[static_cast<int>(it->rarity)]++;
        }
    }

    void Victory_screen::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetColor(RUtil::WHITE);
        r2->draw(IMG,0.0F,0.0F,Setting::WINDOW_WIDTH, Setting::WINDOW_HEIGHT, 0.0F, 0.0F, 0.0F);
        return_button.render(r2);


        TEXT_VEC()[1]->SetFontColor(RUtil::WHITE);
        TEXT_VEC()[1]->render_center(r2, Setting::WINDOW_WIDTH/2.0F-35*Setting::SCALE,Setting::WINDOW_HEIGHT/2.0F+200*Setting::SCALE, 0.0F, 0.0F, 0.0F, Setting::SCALE);
        r2->SetColor(RUtil::GOLD_COLOR, 1.0F);
        m_font.render_center(r2, std::to_string(current_floor), Setting::WINDOW_WIDTH/2.0F+150*Setting::SCALE , Setting::WINDOW_HEIGHT/2.0F+200*Setting::SCALE,Setting::SCALE);
    
        //gold
        TEXT_VEC()[10]->SetFontColor(RUtil::WHITE);
        TEXT_VEC()[10]->render_center(r2, Setting::WINDOW_WIDTH/2.0F-35*Setting::SCALE,Setting::WINDOW_HEIGHT/2.0F+120*Setting::SCALE, 0.0F, 0.0F, 0.0F, Setting::SCALE);
        r2->SetColor(RUtil::GOLD_COLOR, 1.0F);
        m_font.render_center(r2, std::to_string(current_gold), Setting::WINDOW_WIDTH/2.0F+150*Setting::SCALE , Setting::WINDOW_HEIGHT/2.0F+120*Setting::SCALE,Setting::SCALE);

        //HP
        TEXT_VEC()[13]->SetFontColor(RUtil::WHITE);
        TEXT_VEC()[13]->render_center(r2, Setting::WINDOW_WIDTH/2.0F-35*Setting::SCALE,Setting::WINDOW_HEIGHT/2.0F+40*Setting::SCALE, 0.0F, 0.0F, 0.0F, Setting::SCALE);
        r2->SetColor(RUtil::GOLD_COLOR, 1.0F);
        m_font.render_center(r2, std::to_string(current_HP), Setting::WINDOW_WIDTH/2.0F+150*Setting::SCALE , Setting::WINDOW_HEIGHT/2.0F+40*Setting::SCALE,Setting::SCALE);

        //cards
        TEXT_VEC()[14]->SetFontColor(RUtil::WHITE);
        TEXT_VEC()[14]->render_center(r2, Setting::WINDOW_WIDTH/2.0F-35*Setting::SCALE,Setting::WINDOW_HEIGHT/2.0F-40*Setting::SCALE, 0.0F, 0.0F, 0.0F, Setting::SCALE);
        r2->SetColor(RUtil::GOLD_COLOR, 1.0F);
        m_font.render_center(r2, std::to_string(card_amount[2]), Setting::WINDOW_WIDTH/2.0F+150*Setting::SCALE , Setting::WINDOW_HEIGHT/2.0F-40*Setting::SCALE,Setting::SCALE);
        
        TEXT_VEC()[15]->SetFontColor(RUtil::WHITE);
        TEXT_VEC()[15]->render_center(r2, Setting::WINDOW_WIDTH/2.0F-35*Setting::SCALE,Setting::WINDOW_HEIGHT/2.0F-120*Setting::SCALE, 0.0F, 0.0F, 0.0F, Setting::SCALE);
        r2->SetColor(RUtil::GOLD_COLOR, 1.0F);
        m_font.render_center(r2, std::to_string(card_amount[3]), Setting::WINDOW_WIDTH/2.0F+150*Setting::SCALE , Setting::WINDOW_HEIGHT/2.0F-120*Setting::SCALE,Setting::SCALE);
        
        TEXT_VEC()[16]->SetFontColor(RUtil::WHITE);
        TEXT_VEC()[16]->render_center(r2, Setting::WINDOW_WIDTH/2.0F-35*Setting::SCALE,Setting::WINDOW_HEIGHT/2.0F-200*Setting::SCALE, 0.0F, 0.0F, 0.0F, Setting::SCALE);
        r2->SetColor(RUtil::GOLD_COLOR, 1.0F);
        m_font.render_center(r2, std::to_string(card_amount[4]), Setting::WINDOW_WIDTH/2.0F+150*Setting::SCALE , Setting::WINDOW_HEIGHT/2.0F-200*Setting::SCALE,Setting::SCALE);

    }

    void Victory_screen::open(const std::shared_ptr<Character::Player> &player, const Monster::Monster_group &monsters){}
    const std::shared_ptr<Draw::ReTexture>  &Victory_screen::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/victory/background.jpg");
}