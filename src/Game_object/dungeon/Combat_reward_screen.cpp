#include "Game_object/dungeon/Combat_reward_screen.hpp"
#include "Game_object/reward_item/Reward_item.hpp"
#include "RUtil/Game_Input.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/ReTexture.hpp"
#include "Draw/Draw_2D.hpp"

namespace Dungeon
{
    static inline auto DT()noexcept(noexcept(RUtil::Game_Input::delta_time())){
        return RUtil::Game_Input::delta_time();
    }
    Combat_reward_screen::Combat_reward_screen()
        :open_timer(OPENTIMER),
        color_rgb(0.0F)
    {

    }
    
    void Combat_reward_screen::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        //     AbstractDungeon.overlayMenu.proceedButton.render(sb);
        r2->SetColor(color_rgb,color_rgb,color_rgb,1.0F);
        //612*716
        r2->draw(SHEET, (float)Setting::WINDOW_WIDTH/2.0F-306.0F, (float)Setting::WINDOW_HEIGHT/2.0F-46.0F*Setting::SCALE -358.0F, 612.0F, 716.0F, 0.0F, 306.0F, 358.0F, Setting::SCALE, Setting::SCALE);
        
        for(const auto&it:this->reward_items) it->render(r2);
    }

    void Combat_reward_screen::update(Dungeon::Dungeon_shared &dungeon_shared){
        if(open_timer!=0.0F){
            color_rgb=1.0F-open_timer/OPENTIMER;
            open_timer-=DT();
            if(open_timer<0.0F)
                open_timer=0.0F;
        }

        //reward position
        for(size_t i=0;i<reward_items.size();i++){
            reward_items[i]->move(static_cast<float>(Setting::WINDOW_HEIGHT)/2.0F + 124.0F - static_cast<float>(i)*100.0F*Setting::SCALE);
        }

        this->took_all=reward_items.empty();
    }

    const std::shared_ptr<Draw::ReTexture>&Combat_reward_screen::SHEET=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/reward/rewardScreenSheet.png");
} // namespace Dungeon
