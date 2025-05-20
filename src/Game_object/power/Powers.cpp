#include <string>

#include "Game_object/power/Powers.hpp"
#include "Game_object/action/Reduce_power_action.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/Text_layout.hpp"

namespace Power
{
    Powers::Powers(RUtil::Powers_Text_ID power_id, RUtil::AtlasRegionID region_48_id, RUtil::AtlasRegionID region_128_id, bool reduce_each_turn, bool can_negative)
    :power_id(power_id),
    region_48_id(region_48_id),
    region_128_id(region_128_id),
    can_negative(can_negative),
    reduce_each_turn(reduce_each_turn),
    amount(0),
    font_scale(Setting::SCALE),
    color_a(1.0F)
    {}

    void Powers::render_img(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y, float color_a)const{
        auto &img=RUtil::All_Image::GetAtlasRegion(region_48_id);
        r2->SetColor(RUtil::WHITE, color_a);
        r2->draw(img, x - (float)img->GetRegionWidth()/2.0F, y - (float)img->GetRegionHeight()/2.0F, (float)img->GetRegionWidth(), (float)img->GetRegionHeight(), 0.0F, (float)img->GetRegionWidth()/2.0F, (float)img->GetRegionHeight()/2.0F, Setting::SCALE, Setting::SCALE);   
    }

    void Powers::render_amount(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y, float color_a)const{
        if(amount>0){
            if(!reduce_each_turn) r2->SetColor(RUtil::ToRGBA(RUtil::Colors::GREEN), color_a);
            else r2->SetColor(RUtil::WHITE, color_a);
            amount_drawer.render_bot_right(r2, std::to_string(amount), x, y, font_scale);
        }else if(amount<0&&can_negative){
            r2->SetColor(RUtil::ToRGBA(RUtil::Colors::RED), color_a);
            amount_drawer.render_bot_right(r2, std::to_string(amount), x, y, font_scale);
        }
    }
    
    void Powers::render_tip(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y)const{
        using namespace RUtil;
        tip_box.render(r2, x, y);
        r2->SetColor(RUtil::WHITE);
        auto&img=All_Image::GetAtlasRegion(region_48_id);
        r2->draw(img, x + tip_box.get_title()->GetWidth() + POWER_ICON_OFFSET - (float)img->GetRegionWidth()/2.0F, y+5.0F*Setting::SCALE-(float)img->GetRegionHeight()/2.0F, (float)img->GetRegionWidth(), (float)img->GetRegionHeight(), 0.0F, (float)img->GetRegionWidth()/2.0F, (float)img->GetRegionHeight()/2.0F, Setting::SCALE*0.75F, Setting::SCALE*0.75F);
    }
    
    void Powers::update(){
        //font scale
        if(font_scale!=Setting::SCALE)
            font_scale = RUtil::Math::varlerp(font_scale, Setting::SCALE, 10.0F, 0.05F);
        if(color_a!=1.0F)
            color_a = RUtil::Math::fadelerp(color_a, 1.0F);
    }

    void Powers::at_turn_end(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Character::Characters> &target){
        if(reduce_each_turn){
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Reduce_power_action>(shared_from_this(), target));
        }
    }

    Draw::NumberDrawer Powers::amount_drawer(FONTSIZE);
} // namespace Power
