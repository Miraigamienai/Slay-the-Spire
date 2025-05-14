#include "Game_object/top_panel/Gold_bag_icon.hpp"
#include "RUtil/Image_book.hpp"
namespace TopPanel
{
    TopPanel::Gold_bag_icon::Gold_bag_icon():Basic_panel(ICON_X,ICON_Y,ICON_W,ICON_H){

    }
    void TopPanel::Gold_bag_icon::render(const std::shared_ptr<Draw::Draw_2D> &r2)const
    {
        r2->SetColor(-1);
        if(hitbox.Hovered()){
            r2->draw(img,ICON_X,ICON_Y,ICON_W,ICON_H,0,ICON_W/2.0F,ICON_H/2.0F,1.25F,1.25F);
        }
        else{
            r2->draw(img,ICON_X,ICON_Y,ICON_W,ICON_H);
        }
        r2->SetColor(RUtil::Colors::GOLD);
        m_font.render_center(r2, std::to_string(current_gold), ICON_X+ICON_W+NUM_OFFSET_X,ICON_Y+ICON_H/2.0F,Setting::SCALE*0.8F);
        
    }
    void TopPanel::Gold_bag_icon::update(Dungeon::Dungeon_shared &dungeon_shared)
    {
        hitbox.update();
        current_gold=dungeon_shared.player->GetGold();
    }
    const std::shared_ptr<Draw::ReTexture> &Gold_bag_icon::img=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/topPanel/panelGoldBag.png");
}
