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

namespace Power
{
class Powers
{
public:
    Powers(RUtil::Powers_Text_ID power_id, RUtil::AtlasRegionID region_48_id, RUtil::AtlasRegionID region_128_id, bool reduce_each_turn, bool can_negative=false);
    virtual ~Powers()=default;
    void render_img(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y, float color_a)const;
    void render_amount(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y, float color_a)const;
    void render_tip(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y)const;
    void update();
    auto &get_name()const noexcept(noexcept(tip_box.get_title())){return tip_box.get_title();}
    auto &get_desc()const noexcept(noexcept(tip_box.get_body())){return tip_box.get_body();}
    auto get_amount()const noexcept{return amount;}
    void reduce_amount(int value)noexcept{font_scale=8.0F*Setting::SCALE;amount-=value;if(amount<0&&!can_negative)amount=0;}
    const RUtil::Powers_Text_ID power_id;
    const RUtil::AtlasRegionID region_48_id;
    const RUtil::AtlasRegionID region_128_id;
    const bool can_negative;
    const bool reduce_each_turn;
    
    //virtual functions
    virtual void desc_update(){tip_box.change_body(get_amount_based_desc());}
    virtual float calculate_damage_dealt(float damage)const{return damage;}
    virtual float calculate_final_damage_dealt(float damage)const{return damage;}
    virtual float calculate_block_dealt(float block)const{return block;}
    virtual float calculate_final_block_dealt(float block)const{return block;}
protected:
    Draw::Text_box tip_box;
    int amount;
    const std::shared_ptr<Draw::Text_layout> &get_amount_based_desc()const{
        auto &arr=RUtil::Powers_Text_Reader::GetDescriptions(power_id);
        return amount==1?arr[0]:(arr[1]==nullptr?arr[0]:arr[1]);
    }
private:
    float font_scale;
    float color_a;
    static Draw::NumberDrawer amount_drawer;
    static constexpr int FONTSIZE=20;
    static constexpr float POWER_ICON_OFFSET=40.0F*Setting::SCALE;
};
} // namespace Power
