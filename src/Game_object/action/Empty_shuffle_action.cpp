#include "Game_object/action/Empty_shuffle_action.hpp"
namespace Action
{
    Empty_shuffle_action::Empty_shuffle_action(const int discard_pile_size) noexcept
    : amount(discard_pile_size),
      cnt(0),
      first_time(true)
    {
        this->duration=0.0F;
    }
    void Empty_shuffle_action::update(Card::Card_group_handler &card_group_handler,Action_group_handler &/* action_group_handler */,const RUtil::Random_package &random_package){
        if(first_time){
            first_time=false;
            card_group_handler.discard_pile_shuffle_with_rng(random_package.card_shuffle_rng);
        }
        duration-=DT;
        while(cnt<amount&&duration<0.0F){
            cnt++;
            duration+=OEN_CARD_SHUFFLE_TIME;
            if(cnt<11)
                card_group_handler.shuffle(false);
            else
                card_group_handler.shuffle(true);
        }
        if(cnt>=amount)
            is_done=true;
    }    
} // namespace Action
