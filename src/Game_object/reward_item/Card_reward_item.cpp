#include "Game_object/reward_item/Card_reward_item.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Text_Vector_Reader.hpp"
#include "Draw/ReTexture.hpp"
#include "Draw/Text_layout.hpp"
#include "Draw/Draw_2D.hpp"


namespace Reward
{
    static inline auto& TEXT()noexcept(noexcept(RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::RewardItem))){
        return RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::RewardItem)[2];
    }

    Card_reward_item::Card_reward_item(const std::vector<std::shared_ptr<Card::Cards>>&cards,Uint32 PlayerColor_RGB)
        :PlayerColor_RGB(PlayerColor_RGB),
        card_reward(cards)
    {
        TEXT()->SetFontSize(24);
    }
    
    void Card_reward_item::child_render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        if(!taking_reward){
            r2->SetColor(RUtil::WHITE);
            r2->draw(NORMAL_IMG, ITEM_X-32.0F, this->y-32.0F - 2.0F*Setting::SCALE, 64.0F, 64.0F, 0.0F, 32.0F, 32.0F, Setting::SCALE, Setting::SCALE);
        }else{
            this->card_reward.render(r2,PlayerColor_RGB);
        }
    }

    void Card_reward_item::take_reward(Dungeon::Dungeon_shared &dungeon_shared){
        if(!taking_reward){//first in
            taking_reward=true;
            card_reward.Open();
        }
        
        this->card_reward.update(dungeon_shared);
        taking_reward = !card_reward.IsChosen() && !card_reward.SkipButtonClicked();
        took_reward=card_reward.IsChosen();
    }

    void Card_reward_item::child_render_text(const std::shared_ptr<Draw::Draw_2D> &r2, Uint32 color)const{
        TEXT()->SetFontColor(color);
        TEXT()->render_center(r2, TEXT_X, this->y+5.0F*Setting::SCALE, 0.0F, 0.0F, 0.0F, Setting::SCALE);
    }
    
    const std::shared_ptr<Draw::ReTexture>&Card_reward_item::NORMAL_IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/reward/normalCardReward.png");
} // namespace Reward
