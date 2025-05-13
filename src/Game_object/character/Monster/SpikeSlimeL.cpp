#include "Game_object/character/Monster/SpikeSlimeL.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "RUtil/Random.hpp"
namespace Monster{
    SpikeSlimeL::SpikeSlimeL(float offsetX, float offsetY):Monsters(Setting::WINDOW_WIDTH*0.75F+offsetX, FLOOR_Y+offsetY, WIDTH, HIGHT,HPBarWidth)
    {
        setHP(MIN_HP,MAX_HP);
        setBlock(0);

    }
    void SpikeSlimeL::Action(Dungeon::Dungeon_shared &dungeon_shared){
        if(ActionCount>=2) {
            if(lastAction==Monster::SpikeSlimeLAction::FlameTackle)
                currentAction=Monster::SpikeSlimeLAction::Lick;
            else
                currentAction=Monster::SpikeSlimeLAction::FlameTackle;
        }
        else if(current_HP<MAX_HP*0.5F)
            currentAction=Monster::SpikeSlimeLAction::Split;
        else
            currentAction=static_cast<Monster::SpikeSlimeLAction>(dist(dungeon_shared.random_package.monster_ai_rng));
        switch (currentAction){
            case Monster::SpikeSlimeLAction::FlameTackle:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                Damage_info{FLAME_TACKLE_DAMAGE, shared_from_this(), AttackType::blunt_light},
                dungeon_shared.player));


                //shuffles 2 Slimed into the discard pile.
                break;
            case Monster::SpikeSlimeLAction::Lick:
                //	Inflicts 2  Frail.
                break;
            case Monster::SpikeSlimeLAction::Split:
                // spawn 2 Spike Slime M.
                break;
            default:
                break;
        }
        if(currentAction!=lastAction){
            ActionCount=1;
            lastAction=currentAction;
        }
        else
            ActionCount++;
    }
    void SpikeSlimeL::render(const std::shared_ptr<Draw::Draw_2D> &r2) const 
    {
        if(IsFadeOut){
            r2->SetColor(-1,FadeColorA);
            r2->draw(img,getPosition().x,getPosition().y,WIDTH,HIGHT); 
        }
        else{
            r2->SetColor(-1);
            r2->draw(img,getPosition().x,getPosition().y,WIDTH,HIGHT); 
            render_HP(r2);
        }
    }
    const std::shared_ptr<Draw::ReTexture> &SpikeSlimeL::img=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Spike Slime/Spike-slime-l-pretty.png");
    std::discrete_distribution<int> SpikeSlimeL::dist{ActionProbability,ActionProbability+2};
}

