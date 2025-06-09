#include "Game_object/reward_item/Gold_reward_item.hpp"
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
        return RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::RewardItem)[1];
    }

    Gold_reward_item::Gold_reward_item(int gold_amount):gold_amt(gold_amount){
        TEXT()->SetFontSize(FONTSIZE);
        TEXT()->set_num_info(Draw::number_info{0, 0, gold_amt, Draw::NumStatus::normal});
    };
    
    void Gold_reward_item::child_render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetColor(RUtil::Colors::WHITE);
        r2->draw(IMG, ITEM_X-32.0F, this->y-32.0F - 2.0F*Setting::SCALE, 64.0F, 64.0F, 0.0F, 32.0F, 32.0F, Setting::SCALE, Setting::SCALE);
    }

    void Gold_reward_item::take_reward(Dungeon::Dungeon_shared &dungeon_shared){
        dungeon_shared.player->AddGold(gold_amt);
        took_reward=true;
    }

    void Gold_reward_item::child_render_text(const std::shared_ptr<Draw::Draw_2D> &r2, Uint32 color)const{
        TEXT()->SetFontColor(color);
        TEXT()->render_top_left(r2, TEXT_X, this->y+5.0F*Setting::SCALE, Setting::SCALE);
    }
    
    const std::shared_ptr<Draw::ReTexture>&Gold_reward_item::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/shop/gold.png");
} // namespace Reward
