#include "Game_object/room/rest_room_options/Rest_option.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/character/Player.hpp"
#include "Game_object/effect/Sleep_cover_eff.hpp"
#include "Game_object/effect/Rest_option_black_screen.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Text_Vector_Reader.hpp"
#include "Draw/ReTexture.hpp"
#include "Draw/Text_layout.hpp"
namespace Room{
namespace Option{
    static inline auto &TEXT_VEC()noexcept(noexcept(RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::Rest_Option))){
        return RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::Rest_Option);
    }

    Rest_option::Rest_option(int player_max_hp,Uint32 dungeon_fade_color):Options(RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/options/sleep.png")),dungeon_fade_color(dungeon_fade_color){
        TEXT_VEC()[0]->SetFontSize(TEXT_SIZE);//label
        TEXT_VEC()[3]->SetFontSize(TEXT_SIZE);//30% hp text
        
        heal_amount=static_cast<int>(static_cast<float>(player_max_hp)*0.3F);
        TEXT_VEC()[3]->set_num_info(Draw::number_info{0,0,heal_amount});
    }
    
    void Rest_option::child_label_render(const std::shared_ptr<Draw::Draw_2D> &r2,Uint32 font_color)const{
        TEXT_VEC()[0]->SetFontColor(font_color);
        TEXT_VEC()[0]->render_center(r2, hb.CenterX(), hb.CenterY() - 60.0F*Setting::SCALE - 50.0F*this->scale, 0.0F, 0.0F, 0.0F, Setting::SCALE);
    }

    void Rest_option::child_description_render(const std::shared_ptr<Draw::Draw_2D> &r2,float font_color_a)const{
        TEXT_VEC()[3]->SetFontColor(RUtil::CREAM_COLOR);
        TEXT_VEC()[3]->SetFontAlpha(font_color_a);
        TEXT_VEC()[3]->render_center(r2, DESCRIPTION_X, DESCRIPTION_Y, 0.0F, 0.0F, 0.0F, Setting::SCALE); 
    }

    void Rest_option::take_reward(Dungeon::Dungeon_shared &dungeon_shared){
        dungeon_shared.player->heal(heal_amount, dungeon_shared);
        dungeon_shared.top_effs.AddTop(std::make_shared<Effect::Rest_option_black_screen>(dungeon_fade_color));
        for(int i=0;i<30;i++)
            dungeon_shared.top_effs.AddTop(std::make_shared<Effect::Sleep_cover_eff>());
        this->is_cancelled=false;
        this->is_done=true;
    }
}
}    