#ifndef GAME_OBJECT_DUNGEON_DUNGEONS
#define GAME_OBJECT_DUNGEON_DUNGEONS
#include <vector>
#include <memory>

#include "Game_object/dungeon/Dungeon_manager.hpp"//member

//fwd decl
namespace Dungeon{
    class Dungeon_shared;
}
namespace Scene{
    class Scenes;
}

namespace Dungeon{
class Dungeons
{
public:
    Dungeons(Dungeon_shared &dungeon_shared,unsigned long long int random_seed);
    virtual ~Dungeons()=default;
    void update();
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    bool is_game_over()const{return game_over;}
protected:
    Uint32 fade_color=0x1e0f0aff;
private:
    Dungeon_shared &dungeon_shared;

    Dungeon_manager m_dungeon_manager;
    std::shared_ptr<Scene::Scenes> scene;
    std::vector<std::vector<std::shared_ptr<Map::Map_node>>> m_map;
    std::shared_ptr<Map::Map_node> m_current_node,m_next_node=nullptr;
    float fade_timer,fade_color_a;
    bool next_node_is_making_circle,is_fade_in,is_fade_out,game_over;
    const unsigned long long int random_seed;

    void set_next_node_oscillate_and_edge(const bool value)const;
    bool check_and_set_next_node_making_circle();
    void change_current_node_to_next();
    void fade_in();
    void fade_out();
    void update_fading();
    void entering_next_room();
};
}
#endif