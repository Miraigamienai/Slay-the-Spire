#ifndef GAME_OBJECT_CHARACTER_MONSTER_FATGREMLIN
#define GAME_OBJECT_CHARACTER_MONSTER_FATGREMLIN
#include "Game_object/character/Monster/Monsters.hpp"

namespace Monster{
enum class FatGremlinAction
{
    Smash
};
class FatGremlin final:public Monsters
{
public:
    FatGremlin(float offsetX,float offsetY);
    ~FatGremlin()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared)override;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2) const override;

    // void apply(const std::shared_ptr<Action::Action_group> &action_group)const override;
private:
    static const std::shared_ptr<Draw::ReTexture> &img;
    static constexpr float WIDTH=110.0F*Setting::SCALE,
                        HIGHT=220.0F*Setting::SCALE;
    static constexpr int MAX_HP=44,
                        MIN_HP=40,
                        SMASH_DAMAGE=12;
    static constexpr float HPBarWidth=WIDTH*0.8F;
};
}
#endif