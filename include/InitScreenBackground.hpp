#pragma once

#include <array>
#include <memory>
#include <utility>

#include "RUtil/All_Image.hpp"

//fwd decl
namespace Draw{
    class Draw_2D;
}

static constexpr auto top_cloud_id=std::array{RUtil::AtlasRegionID::_topCloud1, RUtil::AtlasRegionID::_topCloud2, RUtil::AtlasRegionID::_topCloud3, RUtil::AtlasRegionID::_topCloud4, RUtil::AtlasRegionID::_topCloud5, RUtil::AtlasRegionID::_topCloud6, RUtil::AtlasRegionID::_topCloud7};
static constexpr auto mid_cloud_id=std::array{RUtil::AtlasRegionID::_midCloud1, RUtil::AtlasRegionID::_midCloud2, RUtil::AtlasRegionID::_midCloud3, RUtil::AtlasRegionID::_midCloud4, RUtil::AtlasRegionID::_midCloud5, RUtil::AtlasRegionID::_midCloud6, RUtil::AtlasRegionID::_midCloud7, RUtil::AtlasRegionID::_midCloud8, RUtil::AtlasRegionID::_midCloud9, RUtil::AtlasRegionID::_midCloud10, RUtil::AtlasRegionID::_midCloud11, RUtil::AtlasRegionID::_midCloud12, RUtil::AtlasRegionID::_midCloud13};

class InitScreenBackground
{
public:
    InitScreenBackground();
    ~InitScreenBackground()=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2) const;
    void update(bool darken);
private:
    class Cloud{
    public:
        Cloud(RUtil::AtlasRegionID region_id, bool move_right);
        void render(const std::shared_ptr<Draw::Draw_2D> &r2) const{
            InitScreenBackground::render_format(r2, region_id, x, y);
        }
        void update();
        const RUtil::AtlasRegionID region_id;
        const bool move_right;
    private:
        float x, y;
        float speed_x, speed_y;
    };

    std::array<Cloud, top_cloud_id.size()> top_cloud;
    std::array<Cloud, mid_cloud_id.size()> mid_cloud;
    float glow_timer;
    float logo_a;
    
    template <size_t...Is>
    static auto CloudCreater(bool move_right, const std::array<RUtil::AtlasRegionID, sizeof...(Is)>&id_arr, std::index_sequence<Is...>){
        return std::array{Cloud{id_arr[Is], move_right}...};
    }

    template <size_t N>
    static auto CloudCreater(bool move_right, const std::array<RUtil::AtlasRegionID, N>&id_arr){
        return CloudCreater(move_right, id_arr, std::make_index_sequence<N>{});
    }

    static void render_format(const std::shared_ptr<Draw::Draw_2D> &r2, RUtil::AtlasRegionID id, float x, float y);
};