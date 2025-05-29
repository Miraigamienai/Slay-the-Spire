#pragma once

#include <memory>

#include "RUtil/Powers_Text_Reader.hpp"
#include "Draw/NumberDrawer.hpp"
#include "Draw/Text_box.hpp"
#include "Draw/Text_layout.hpp"
#include "WindowSize.hpp"

//fwd decl
namespace RUtil{
    enum class AtlasRegionID:int;
}
namespace Draw{
    class Draw_2D;
}
namespace Character{
    class Characters;
}
namespace Dungeon{
    class Dungeon_shared;
}

namespace Power
{
enum class PowerType{
    buff,
    debuff,
    neutral
};
class Powers : public std::enable_shared_from_this<Powers>
{
public:
    Powers(RUtil::Powers_Text_ID power_id, RUtil::AtlasRegionID region_48_id, RUtil::AtlasRegionID region_128_id, PowerType power_type, bool reduce_each_turn, bool can_negative=false);
    virtual ~Powers()=default;
    void render_img(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y, float color_a)const;
    void render_amount(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y, float color_a)const;
    void render_tip(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y)const;
    void render_flash(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y)const;
    void update();
    void reduce_amount(int value)noexcept{font_scale=8.0F*Setting::SCALE;amount-=value;}
    void add_amount(int value)noexcept{
        if(can_negative || amount!=NO_DISPLAY_AMOUNT){
            font_scale=8.0F*Setting::SCALE;
            amount+=value;
        }
    }
    void flash()noexcept{flash_a=0.5F; flash_scale=3.0F*Setting::SCALE; flash_timer=2.0F;}
    auto &get_name()const noexcept(noexcept(tip_box.get_title())){return tip_box.get_title();}
    auto &get_desc()const noexcept(noexcept(tip_box.get_body())){return tip_box.get_body();}
    auto get_amount()const noexcept{return amount;}
    const RUtil::Powers_Text_ID power_id;
    const RUtil::AtlasRegionID region_48_id;
    const RUtil::AtlasRegionID region_128_id;
    const PowerType power_type;
    const bool reduce_each_turn;
    const bool can_negative;

    //virtual functions
    virtual void desc_update(){tip_box.change_body(get_amount_based_desc());}
    virtual float calculate_damage_dealt(float damage)const{return damage;}
    virtual float calculate_final_damage_dealt(float damage)const{return damage;}
    virtual float calculate_damage_receive(float damage)const{return damage;}
    virtual float calculate_final_damage_receive(float damage)const{return damage;}
    virtual float calculate_block_modify(float block)const{return block;}
    virtual float calculate_final_block_modify(float block)const{return block;}
    virtual void at_turn_end(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Character::Characters> &target);
protected:
    Draw::Text_box tip_box;
    int amount;
    const std::shared_ptr<Draw::Text_layout> &get_amount_based_desc()const{
        auto &arr=RUtil::Powers_Text_Reader::GetDescriptions(power_id);
        return amount!=1 && arr[1]!=nullptr ? arr[1] : arr[0];
    }
    static constexpr int NO_DISPLAY_AMOUNT = -1;
private:
    float font_scale;
    float color_a;
    float flash_timer, flash_scale, flash_a;
    static Draw::NumberDrawer amount_drawer;
    static constexpr int FONTSIZE=22;
public:
    static constexpr float POWER_ICON_OFFSET_X=40.0F*Setting::SCALE,
                           POWER_ICON_OFFSET_Y=-6.0F*Setting::SCALE;
};
} // namespace Power
