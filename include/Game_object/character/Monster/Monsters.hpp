#ifndef GAME_OBJECT_CHARACTER_MONSTER_MONSTERS
#define GAME_OBJECT_CHARACTER_MONSTER_MONSTERS
#include <memory>

#include "Game_object/action/Action_group_handler.hpp"
#include "Game_object/character/Characters.hpp"

// //fwd decl
// namespace Dungeon{
//     struct Dungeon_shared;
// }

namespace Monster{
enum class MonsterID{
    None,
    TempMonster,
    AcidSlimeL,AcidSlimeM,AcidSlimeS,
    Cultist,
    FungiBeast,
    GremlinNob,FatGremlin,MadGremlin,ShieldGremlin,SneakyGremlin,
    GremlinWizard,
    Hexaghost,
    Lagavulin,
    RedLouse,
    GreenLouse,
    Sentry,
    BlueSlaver,RedSlaver,
    SpikeSlimeL,SpikeSlimeM,SpikeSlimeS,
    JawWorm,
    Looter,
    Mugger
};
class Monsters:public Character::Characters
{
public:
    Monsters(float x, float y, float width, float height,float HPBarWidth,const std::shared_ptr<Draw::ReTexture> &img);
    virtual ~Monsters()=default;
    virtual void Action(Dungeon::Dungeon_shared &dungeon_shared)=0; 
    virtual void damage(const Damage_info& damage_info)override;
    void setHP(int min,int max);
    void render(const std::shared_ptr<Draw::Draw_2D> &r2) const override;
protected:

    static constexpr int FLOOR_Y=Setting::WINDOW_HEIGHT*0.5F-200.0F*Setting::SCALE;
private:
    const std::shared_ptr<Draw::ReTexture> &img;
};
}
#endif