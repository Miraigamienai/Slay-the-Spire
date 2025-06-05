#include "Game_object/room/rest_room_options/Smith_option.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/dungeon/Grid_screen_action/Grid_screen_upgrade_action.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Text_Vector_Reader.hpp"
#include "Draw/ReTexture.hpp"
#include "Draw/Text_layout.hpp"

namespace Room{
namespace Option{
    static inline auto &TEXT_VEC()noexcept(noexcept(RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::Smith_Option))){
        return RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::Smith_Option);
    }

    Smith_option::Smith_option(bool any_card_can_upgrade)
        :Options(RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/options/smith.png"),any_card_can_upgrade),
        skip_one_frame(false)
    {
        TEXT_VEC()[0]->SetFontSize(TEXT_SIZE);//label
        TEXT_VEC()[1]->SetFontSize(TEXT_SIZE);//activate message
        TEXT_VEC()[2]->SetFontSize(TEXT_SIZE);//not activate message
    }
    
    void Smith_option::child_label_render(const std::shared_ptr<Draw::Draw_2D> &r2,Uint32 font_color)const{
        TEXT_VEC()[0]->SetFontColor(font_color);
        TEXT_VEC()[0]->render_center(r2, hb.CenterX(), hb.CenterY() - 60.0F*Setting::SCALE - 50.0F*this->scale, 0.0F, 0.0F, 0.0F, Setting::SCALE);
    }

    void Smith_option::child_description_render(const std::shared_ptr<Draw::Draw_2D> &r2,float font_color_a)const{
        const int pos=is_activating?1:2;
        TEXT_VEC()[pos]->SetFontColor(RUtil::CREAM_COLOR);
        TEXT_VEC()[pos]->SetFontAlpha(font_color_a);
        TEXT_VEC()[pos]->render_center(r2, DESCRIPTION_X, DESCRIPTION_Y, 0.0F, 0.0F, 0.0F, Setting::SCALE);
    }

    void Smith_option::take_reward(Dungeon::Dungeon_shared &dungeon_shared){
        if(!dungeon_shared.manager.current_screen_equals(Abstraction::ScreenType::grid_cards)){
            if(skip_one_frame){
                skip_one_frame=false;
            }else{
                skip_one_frame=true;
                is_cancelled=false;
                is_done=false;
                //open grid_cards screen
                dungeon_shared.manager.open<Abstraction::ScreenType::grid_cards>(dungeon_shared.card_group_handler.get_upgradeable_card_group(), std::make_shared<Dungeon::GridScreenAction::Grid_screen_upgrade_action>(), is_done, is_cancelled);
            }
        }
    }
}
}    