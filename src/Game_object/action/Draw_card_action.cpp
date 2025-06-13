#include "Game_object/action/Draw_card_action.hpp"//the hpp
#include "Game_object/action/Empty_shuffle_action.hpp"//shuffle when no card
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/character/Player.hpp"

namespace Action
{
    void Draw_card_action::update(Dungeon::Dungeon_shared &dungeon_shared){
        const int draw_size=dungeon_shared.card_group_handler.size<Card::GroupType::draw_pile>(),
                  discard_size=dungeon_shared.card_group_handler.size<Card::GroupType::m_discard>();
        if(draw_size+discard_size==0){
            is_done=true;
            return;
        }
        if(dungeon_shared.card_group_handler.is_someone_flying())
            return; 
        if(first_time){
            first_time=false;
            if(amount+dungeon_shared.card_group_handler.size<Card::GroupType::hand_cards>()>10){
                amount=10-dungeon_shared.card_group_handler.size<Card::GroupType::hand_cards>();
            }
            if(amount>draw_size){
                dungeon_shared.action_group_handler.AddActionTop(std::make_shared<Action::Draw_card_action>(amount-draw_size));
                dungeon_shared.action_group_handler.AddActionTop(std::make_shared<Action::Empty_shuffle_action>(discard_size));
                if(draw_size!=0)
                    dungeon_shared.action_group_handler.AddActionTop(std::make_shared<Action::Draw_card_action>(draw_size));
                is_done=true;
                return;
            }
        }
        duration-=DT;
        while(0<amount&&duration<0.0F){
            amount--;
            duration+=ACTION_DUR_FASTER;
            dungeon_shared.card_group_handler.draw(dungeon_shared.player->get_powers());
            dungeon_shared.refresh_display();
        }
        if(amount==0)
            is_done=true;
    }

} // namespace Action
