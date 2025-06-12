#include "Game_object/dungeon/Combat_reward_screen.hpp"
#include "Game_object/reward_item/Reward_item.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "RUtil/Game_Input.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Text_Vector_Reader.hpp"
#include "Draw/ReTexture.hpp"
#include "Draw/Draw_2D.hpp"

namespace Dungeon
{
    static inline auto DT()noexcept(noexcept(RUtil::Game_Input::delta_time())){
        return RUtil::Game_Input::delta_time();
    }
    Combat_reward_screen::Combat_reward_screen()
        :Abstraction::Is_screen(Abstraction::ScreenType::combat_reward),
        now_reward_pos(-1),
        open_timer(OPENTIMER),
        color_rgb(0.0F),
        took_all(false)
    {
        // 初始設定為"略過獎勵"文字
        auto skip_rewards_text = RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::CombatRewardScreen)[5];
        proceed_button.set_text(skip_rewards_text);
    }
    
    void Combat_reward_screen::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        if(now_reward_pos!=-1){
            reward_items[now_reward_pos]->render(r2);
        }else{
            proceed_button.render(r2);
            r2->SetColor(color_rgb,color_rgb,color_rgb,1.0F);
            //612*716
            r2->draw(SHEET, (float)Setting::WINDOW_WIDTH/2.0F-306.0F, (float)Setting::WINDOW_HEIGHT/2.0F-46.0F*Setting::SCALE -358.0F, 612.0F, 716.0F, 0.0F, 306.0F, 358.0F, Setting::SCALE, Setting::SCALE);
            
            for(const auto&it:this->reward_items) it->render(r2);
        }
    }

    void Combat_reward_screen::update(Dungeon::Dungeon_shared &dungeon_shared){
        if(open_timer!=0.0F){
            color_rgb=1.0F-open_timer/OPENTIMER;
            open_timer-=DT();
            if(open_timer<0.0F)
                open_timer=0.0F;
        }

        //button update
        this->proceed_button.update();
        if(this->proceed_button.is_logically_just_hovered())
            for(const auto&it:reward_items) it->flash();
        if(proceed_button.is_logically_clicked()){
            proceed_button.hide();
            //change screen to main_dungoen
            dungeon_shared.manager.open<Abstraction::ScreenType::main_dungeon>();
        }

        if(now_reward_pos==-1){
            for(size_t i=0;i<reward_items.size();i++){
                //reward position update
                reward_items[i]->move(static_cast<float>(Setting::WINDOW_HEIGHT)/2.0F + 124.0F - static_cast<float>(i)*100.0F*Setting::SCALE);
                //update
                reward_items[i]->update();
                //check click
                if(reward_items[i]->HitboxClicked() && on_top){
                    now_reward_pos=i;
                    proceed_button.hide();
                    break;
                }
            }
        }

        //check now
        if(now_reward_pos!=-1){
            reward_items[now_reward_pos]->take_reward(dungeon_shared);
            if(!reward_items[now_reward_pos]->is_taking_reward()){
                if(reward_items[now_reward_pos]->did_take_reward())
                    reward_items.erase(reward_items.begin()+now_reward_pos);
                now_reward_pos=-1;
                proceed_button.show();
            }
        }

        // 檢查是否所有獎勵都已經領取
        bool new_took_all = reward_items.empty();
        
        // 如果獎勵領取狀態改變，更新按鈕文字
        if(new_took_all != took_all) {
            took_all = new_took_all;
            
            // 根據獎勵領取狀態設定不同文字
            if(took_all) {
                // 如果所有獎勵都領完了，顯示"前進"
                auto proceed_text = RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::AbstractDungeon)[0];
                proceed_button.set_text(proceed_text);
            } else {
                // 否則顯示"略過獎勵"
                auto skip_rewards_text = RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::CombatRewardScreen)[5];
                proceed_button.set_text(skip_rewards_text);
            }
        }
    }

    void Combat_reward_screen::open(const std::vector<std::shared_ptr<Reward::Reward_item>> &reward_items){
        open_timer=OPENTIMER;
        this->reward_items=reward_items;
        took_all = reward_items.empty();
        
        // 設定初始按鈕文字
        if(took_all) {
            auto proceed_text = RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::AbstractDungeon)[0];
            proceed_button.set_text(proceed_text);
        } else {
            auto skip_rewards_text = RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::CombatRewardScreen)[5];
            proceed_button.set_text(skip_rewards_text);
        }
        
        proceed_button.show();
    }
    
    const std::shared_ptr<Draw::ReTexture>&Combat_reward_screen::SHEET=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/reward/rewardScreenSheet.png");
} // namespace Dungeon