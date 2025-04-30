#include "Game_object/character/Player.hpp"
#include "RUtil/Random.hpp"
#include "Game_object/Damage_info.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace Character{
    Player::Player():Characters(Setting::WINDOW_WIDTH*0.5F+WIDTH_OFFSET, Setting::WINDOW_HEIGHT*0.5F, WIDTH, HIGHT,HPBarWidth),player_type(PlayerType::Ironclad) 
    {
        max_energy=3;
        current_energy=3;
        max_HP=80;
        current_HP=80;
        current_Block=0;
        setPosition(glm::vec2(Setting::WINDOW_WIDTH*0.5F+WIDTH_OFFSET,Setting::WINDOW_HEIGHT*0.5F+HEIGHT_OFFSET));
        KindOfCharacter=KindOfCharacter::PLAYER;
    }

    void Player::render(const std::shared_ptr<Draw::Draw_2D> &r2) const 
    {
        r2->SetColor(-1);
        r2->draw(img,getPosition().x,getPosition().y,WIDTH,HIGHT); 
        render_HP(r2);
    }

    void Player::damage(const Damage_info& damage_info){
        if(current_Block>damage_info.dmg){
            current_Block-=damage_info.dmg;
            return;
        }
        else if (current_Block)
        {
            current_Block=0;
            current_HP-=damage_info.dmg-current_Block;
        }
        else
        {
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

}

