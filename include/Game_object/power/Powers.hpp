#pragma once

#include <memory>

#include "Draw/NumberDrawer.hpp"

//fwd decl
namespace RUtil{
    enum class Powers_Text_ID:int;
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
    Powers(RUtil::Powers_Text_ID power_id, RUtil::AtlasRegionID region_48_id, RUtil::AtlasRegionID region_128_id)
        :power_id(power_id),
        region_48_id(region_48_id),
        region_128_id(region_128_id),
        amount(0){}
    virtual ~Powers()=default;
    void render_img(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y, float color_a)const;
    void render_amount(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y, float color_a)const;
    void render_tip(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y, float color_a)const;
    void update();

    const RUtil::Powers_Text_ID power_id;
    const RUtil::AtlasRegionID region_48_id;
    const RUtil::AtlasRegionID region_128_id;
private:
    int amount;
    static Draw::NumberDrawer amount_drawer;
    static constexpr int FONTSIZE=20;
};
} // namespace Power
