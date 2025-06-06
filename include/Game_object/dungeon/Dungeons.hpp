#ifndef GAME_OBJECT_DUNGEON_DUNGEONS
#define GAME_OBJECT_DUNGEON_DUNGEONS
#include <vector>
#include <memory>
#include <SDL_stdinc.h>

//fwd decl
enum class State:int;
namespace Dungeon{
    struct Dungeon_shared;
}
namespace Scene{
    class Scenes;
}
namespace Draw{
    class Draw_2D;
}
namespace Map{
    class Map_node;
}
namespace Room{
    class Monster_room;
}

namespace Dungeon{
class Dungeons
{
public:
    Dungeons(Dungeon_shared &dungeon_shared, unsigned long long int random_seed, State&state);
    virtual ~Dungeons()=default;
    void update();
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const;
protected:
    Uint32 fade_color=0x1e0f0aff;
private:
    Dungeon_shared &dungeon_shared;
    State &state;
    const unsigned long long int random_seed;

    std::shared_ptr<Scene::Scenes> scene;
    std::vector<std::vector<std::shared_ptr<Map::Map_node>>> m_map;
    float fade_timer,fade_color_a;
    bool next_node_is_making_circle,is_fade_in,is_fade_out;
    std::shared_ptr<Room::Monster_room> boss_room;
    bool fighting_boss;
    float boss_timer;

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