#include "Game_object/character/Player.hpp"
#include "RUtil/Random.hpp"
#include "Game_object/Damage_info.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/effect/Fade_wide.hpp"
namespace Character{
    Player::Player()
        :Characters(Setting::WINDOW_WIDTH*0.5F+WIDTH_OFFSET, Setting::WINDOW_HEIGHT*0.5F, WIDTH, HIGHT,HPBarWidth),
        player_type(PlayerType::Ironclad)
    {
        max_energy=3;
        current_energy=3;
        gold=100;
        max_HP=80;
        current_HP=80;
        current_Block=0;
        setPosition(Setting::WINDOW_WIDTH*0.5F+WIDTH_OFFSET,Setting::WINDOW_HEIGHT*0.5F+HEIGHT_OFFSET);
        KindOfCharacter=KindOfCharacter::PLAYER;
        fadeTimer=2.5F;
        fadeTime=2.5F;
    }

    void Player::render(const std::shared_ptr<Draw::Draw_2D> &r2) const 
    {
        if(IsFadeOut){
            r2->SetColor(fadeColor,FadeColorA);
            r2->draw(Effect::Fade_wide::white_square, 0.0F, 0.0F, Setting::WINDOW_WIDTH, Setting::WINDOW_HEIGHT);
            r2->SetColor(-1,1);
            r2->draw(img_died,getPosition().x,getPosition().y,WIDTH,HIGHT); 
        }
        else{
            r2->SetColor(-1);
            r2->draw(img,getPosition().x,getPosition().y,WIDTH,HIGHT); 
            render_HP(r2);
        }
    }

    void Player::damage(const Damage_info& damage_info){
        if(current_Block>damage_info.dmg){
            current_Block-=damage_info.dmg;
            return;
        }
        else if (current_Block){
            current_Block=0;
            current_HP-=damage_info.dmg-current_Block;
        }
        else if(current_HP-damage_info.dmg<=0){
            current_HP=0;
        }
        else{
            current_HP-=damage_info.dmg;
        }
    }
    

    void Player::ReduceEnergy(int value, Dungeon::Dungeon_shared &dungeon_shared){
        dungeon_shared.overlay.on_use_energy();
        this->current_energy-=value;
    }
    
    void Player::AddEnergy(int value, Dungeon::Dungeon_shared &dungeon_shared){
        dungeon_shared.overlay.on_add_energy(dungeon_shared.effs);
        this->current_energy+=value;
    }

    const std::shared_ptr<Draw::ReTexture> &Player::img=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/character/Ironclad.png");
    const std::shared_ptr<Draw::ReTexture> &Player::img_died=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/character/corpse.png");
}

