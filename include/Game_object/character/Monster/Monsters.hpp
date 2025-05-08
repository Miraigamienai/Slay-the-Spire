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
class Monsters:public Character::Characters, public std::enable_shared_from_this<Monsters>
{
public:
    Monsters(float x, float y, float width, float height,float HPBarWidth);
    virtual ~Monsters()=default;
    virtual void Action(Dungeon::Dungeon_shared &dungeon_shared)=0; 
    // virtual void apply(const std::shared_ptr<Action::Action_group> &action_group)const=0;
    void damage(const Damage_info& damage_info)override;
    void setHP(int min,int max);
    void setBlock(int num);
protected:
    int m_damage;
    static constexpr int FLOOR_Y=Setting::WINDOW_HEIGHT*0.5F-200.0F*Setting::SCALE;
};
}
#endif