#include "Game_object/character/Monster/AcidSlimeM.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "RUtil/Random.hpp"
namespace Monster{
    AcidSlimeM::AcidSlimeM(float offsetX, float offsetY):Monsters(Setting::WINDOW_WIDTH*0.75F+offsetX, FLOOR_Y+offsetY, WIDTH, HIGHT,HPBarWidth)
    {
        setHP(MIN_HP,MAX_HP);
        setBlock(0);

    }
    void AcidSlimeM::Action(Dungeon::Dungeon_shared &dungeon_shared){
        currentAction=static_cast<Monster::AcidSlimeMAction>(dist(dungeon_shared.random_package.monster_ai_rng));
        switch (currentAction){
            case Monster::AcidSlimeMAction::CorrosiveSpit:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                Damage_info{CORROSIVE_SPIT_DAMAGE, shared_from_this(), AttackType::blunt_light},
                dungeon_shared.player));

                // shuffles 1 Slimed into the discard pile.
                break;
            case Monster::AcidSlimeMAction::Lick:
                // Inflict 1  Weak.
                break;
            case Monster::AcidSlimeMAction::Tackle:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(
                    Damage_info{TACKLE_DAMAGE, shared_from_this(), AttackType::blunt_light},
                    dungeon_shared.player));
                break;
            
            default:
                break;
        }
    }
    void AcidSlimeM::render(const std::shared_ptr<Draw::Draw_2D> &r2) const 
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
    const std::shared_ptr<Draw::ReTexture> &AcidSlimeM::img=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Acid Slime/Acid-slime-m-pretty.png");
    std::discrete_distribution<int> AcidSlimeM::dist{ActionProbability,ActionProbability+3};
}