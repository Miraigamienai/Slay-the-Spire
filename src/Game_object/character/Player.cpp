#include "Game_object/character/Player.hpp"
#include "Game_object/Damage_info.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "RUtil/Image_book.hpp"

namespace Character{
    Player::Player()
        :Characters(CharacterType::PLAYER, Setting::WINDOW_WIDTH*0.5F+WIDTH_OFFSET, Setting::WINDOW_HEIGHT*0.5F+HEIGHT_OFFSET, WIDTH, HEIGHT, 0.0F, 0.0F, 80),
        player_type(PlayerType::Ironclad),
        max_energy(3),
        current_energy(max_energy),
        gold(100){}

    void Player::render(const std::shared_ptr<Draw::Draw_2D> &r2) const 
    {
        r2->SetColor(RUtil::WHITE, 1.0F);
        if(IsDie()){
            r2->draw(img_died, getAnimX()+orgX, getAnimY()+orgY, WIDTH, HEIGHT); 
        }else{
            r2->draw(img, getAnimX()+orgX, getAnimY()+orgY, WIDTH, HEIGHT); 
            render_HP_and_power(r2);
        }
    }

    void Player::damage(const Damage_info& damage_info, Dungeon::Dungeon_shared &dungeon_shared){
        if(IsDie()) return;

        int dmg = damage_info.dmg;
        const bool had_block = GetCurrentBlock() > 0;
        if(had_block){
            if(damage_info.dmg > GetCurrentBlock()){
                const auto temp=GetCurrentBlock();
                ReduceBlock(temp, dungeon_shared);
                dmg -= temp;
            }else{
                ReduceBlock(damage_info.dmg, dungeon_shared);
                dmg = 0;
            }
        }

        //TODO: effs
        if(dmg>0){
            if(damage_info.src.get()!=this) use_animation<Character::Animation::STAGGER>();
            //strike eff if hp!=0
            current_HP-=dmg;
            if(current_HP<0)current_HP=0;
            health_update_event();
        }
    }
    

    void Player::ReduceEnergy(int value, Dungeon::Dungeon_shared &dungeon_shared){
        dungeon_shared.overlay.on_use_energy();
        current_energy-=value;
    }
    
    void Player::AddEnergy(int value, Dungeon::Dungeon_shared &dungeon_shared){
        dungeon_shared.overlay.on_add_energy(dungeon_shared.effs);
        current_energy+=value;
    }

    const std::shared_ptr<Draw::ReTexture> &Player::img=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/character/Ironclad.png");
    const std::shared_ptr<Draw::ReTexture> &Player::img_died=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/character/corpse.png");
}

