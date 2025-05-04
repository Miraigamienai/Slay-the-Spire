#ifndef GAME_OBJECT_CHARACTER_MONSTER_RED_SLAVER_HPP
#define GAME_OBJECT_CHARACTER_MONSTER_RED_SLAVER_HPP
#include "Game_object/character/Monster/Monsters.hpp"

namespace Monster{
enum class RedSlaverAction
{
    Stab,
    Scrape,
    Entangle
};
class RedSlaver final:public Monsters
{
public:
    RedSlaver(float offsetX,float offsetY);
    ~RedSlaver()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2) const override;
    // void apply(const std::shared_ptr<Action::Action_group> &action_group)const override;
private:
    
    static const std::shared_ptr<Draw::ReTexture> &img;
    static constexpr int WIDTH=170.0F*Setting::SCALE,
                         HIGHT=230.0F*Setting::SCALE;
    static constexpr int MAX_HP=50,
                         MIN_HP=46,
                         DAMAGE=13;
    static constexpr int HPBarWidth=WIDTH*0.8F;
};
}
#endif