#pragma once

#include <array>

#include "Game_object/map/Legend.hpp"
#include "Game_object/room/Rooms.hpp"
#include "WindowSize.hpp"

//fwd decl
namespace Effect{
    class Effect_group;
}
namespace Map{
    class Map_edge;
}

namespace Map{
enum class Direction{
    left,
    middle,
    right
};
class Map_node
{
public:
    Map_node(int x,int y);
    ~Map_node()=default;
    bool HasEdge(Direction dir)const noexcept{return edges[static_cast<int>(dir)]!=nullptr;}
    bool IsToBoss()const noexcept{return to_boss;}
    void SetToBoss()noexcept{to_boss=true;}
    void add_edge(Direction dir, const std::shared_ptr<Map_edge> &edge)noexcept{edges[static_cast<int>(dir)]=edge;}
    float GetOffsetX()const{return offset_x;}
    float GetOffsetY()const{return offset_y;}
    bool IsMakingCircle()const{return making_circle;}
    void MarkTaken(){taken=true;}
    const std::shared_ptr<Room::Rooms> &GetRoom()const {return m_room;}
    std::shared_ptr<Map_edge>GetConnectedEdge(const std::shared_ptr<Map_node> &node);
    void MarkAllEdge(const bool is_taken)const;
    void SetRoom(const std::shared_ptr<Room::Rooms> &room)noexcept{this->m_room=room;};
    void BindLegend(const Legend &legend){legend_hovered=&legend.get_hovered_hb_ref(m_room->room_type);}
    void SetReadyToConnect(const bool value){is_ready_to_connect=value;}
    void render(const std::shared_ptr<Draw::Draw_2D> &r2,const float screen_offset,const float map_a)const;
    void update(const float screen_offset,const bool is_dungeon_now_room_complete,const bool on_top,Effect::Effect_group &top_effs);
    const int x,y;
private:
    RUtil::Hitbox hb;
    float offset_x,offset_y,m_scale,m_angle,anim_wait_timer,color_a,oscillate_timer;
    bool to_boss,taken,is_ready_to_connect,highlight,making_circle,made_circle;
    const bool *legend_hovered=nullptr;
    void oscillate();
    Uint32 color;
    //the edges only point to future.
    std::array<std::shared_ptr<Map_edge>, 3> edges;
    std::shared_ptr<Room::Rooms> m_room;
    static constexpr int IMG_WIDTH = (int)(Setting::SCALE * 64.0F);
    static constexpr float JITTER_X=27.0F * Setting::SCALE,
                           JITTER_Y=37.0F * Setting::SCALE,
                           OFFSET_Y = 180.0F * Setting::SCALE,
                           SPACING_X =(float)IMG_WIDTH * 2.0F;
    static constexpr Uint32 OUTLINE_COLOR=0x8c8c80ff;
    static const std::shared_ptr<Draw::ReTexture> &s_circle;

public:
    static constexpr float OFFSET_X= 560.0F * Setting::SCALE,
                           MAP_DST_Y = 150.0F * Setting::SCALE;
    static constexpr Uint32 AVAILABLE_COLOR = 371272703U,
                            NOT_TAKEN_COLOR = 1448498943U;
};
}