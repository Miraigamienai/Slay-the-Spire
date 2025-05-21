#include <string>

#include "Game_object/power/Powers.hpp"
#include "Game_object/action/Reduce_power_action.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Game_Input.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/Text_layout.hpp"

namespace Power
{
    Powers::Powers(RUtil::Powers_Text_ID power_id, RUtil::AtlasRegionID region_48_id, RUtil::AtlasRegionID region_128_id, PowerType power_type, bool reduce_each_turn, bool can_negative)
    :power_id(power_id),
    region_48_id(region_48_id),
    region_128_id(region_128_id),
    power_type(power_type),
    reduce_each_turn(reduce_each_turn),
    can_negative(can_negative),
    tip_box(RUtil::Powers_Text_Reader::GetName(power_id)),
    amount(0),
    font_scale(Setting::SCALE),
    color_a(1.0F),
    flash_timer(0.0F),
    flash_scale(0.0F),
    flash_a(0.0F)
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
    
    void Powers::render_flash(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y)const{
        if(flash_timer!=0.0F){
            r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
            r2->SetColor(RUtil::WHITE, flash_a);
            auto &img=RUtil::All_Image::GetAtlasRegion(this->region_48_id);
            r2->draw(img, x - static_cast<float>(img->GetRegionWidth())/2.0F, y - static_cast<float>(img->GetRegionHeight())/2.0F, static_cast<float>(img->GetRegionWidth()), static_cast<float>(img->GetRegionHeight()), 0.0F, static_cast<float>(img->GetRegionWidth())/2.0F, static_cast<float>(img->GetRegionHeight())/2.0F, this->flash_scale, this->flash_scale);
        }
    }
    
    void Powers::update(){
        //font scale
        if(font_scale!=Setting::SCALE)
            font_scale = RUtil::Math::varlerp(font_scale, Setting::SCALE, 10.0F, 0.05F);
        if(color_a!=1.0F)
            color_a = RUtil::Math::fadelerp(color_a, 1.0F);
        //flash update
        if(flash_timer!=0.0F){
            if(flash_timer>0.5F) flash_scale=RUtil::Math::interpolation_exp5out(3.0F, 1.0F, (2.0F-flash_timer)/1.5F)*Setting::SCALE;
            else flash_a=RUtil::Math::interpolation_fade(0.5F, 0.0F, 1.0F-flash_timer);
            flash_timer-=RUtil::Game_Input::delta_time();
            if(flash_timer<0.0F) flash_timer=0.0F;
        }
    }

    void Powers::at_turn_end(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Character::Characters> &target){
        if(reduce_each_turn){
            dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Reduce_power_action>(shared_from_this(), target));
        }
    }

    Draw::NumberDrawer Powers::amount_drawer(FONTSIZE, FontWeight::bold);
} // namespace Power
