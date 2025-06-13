#pragma once

#include "Game_object/room/Rooms.hpp"
#include "Game_object/button/Proceed_button.hpp"
#include <random>
//fwd decl
namespace Room{
    class Treasure_item;
}
namespace Treasure{
    enum class Treasure_type{
        SMALL,
        MEDIUM,
        LARGE
    };
    
}
namespace Room{

class Treasure_room final:public Rooms
{
public:
    Treasure_room()noexcept:Rooms(Room_type::Treasure),treasure_item(nullptr),proceed_pop_timer(POP_TIME){}
    ~Treasure_room()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    const std::shared_ptr<Draw::ReTexture> &GetTexture()const override{return IMG;}
    const std::shared_ptr<Draw::ReTexture> &GetOutlineTexture()const override{return IMG_O;}
    void update(Dungeon::Dungeon_shared &dungeon_shared) override;
    void init_room(Dungeon::Dungeon_shared& dungeon_shared,Uint32 dungeon_fade_color) override;
private:
    std::shared_ptr<Treasure_item> treasure_item;
    Button::Proceed_button proceed;
    float proceed_pop_timer;
    static constexpr float Probability[3]={50.0F,33.0F,17.0F};
    static std::discrete_distribution<int> dist;
    static const std::shared_ptr<Draw::ReTexture> &IMG,
                                                &IMG_O;
};
}
