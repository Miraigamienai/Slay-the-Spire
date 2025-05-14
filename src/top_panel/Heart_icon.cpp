#include "Game_object/top_panel/Heart_icon.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/Text_layout_all.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
namespace TopPanel
{
    TopPanel::Heart_icon::Heart_icon():Basic_panel(ICON_X,ICON_Y,ICON_W,ICON_H){

    }
    void TopPanel::Heart_icon::render(const std::shared_ptr<Draw::Draw_2D> &r2)const
    {
        r2->SetColor(-1);
        if(hitbox.Hovered()){
            r2->draw(img,ICON_X,ICON_Y,ICON_W,ICON_H,0,ICON_W/2.0F,ICON_H/2.0F,1.25F,1.25F);
        }
        else{
            r2->draw(img,ICON_X,ICON_Y,ICON_W,ICON_H);
        }
        r2->SetColor(RUtil::Colors::RED);
        m_font.render_center(r2, std::to_string(current_HP)+"/"+std::to_string(max_HP), ICON_X+ICON_W+NUM_OFFSET_X,ICON_Y+ICON_H/2.0F,Setting::SCALE*0.8F);
        
    }
    void TopPanel::Heart_icon::update(Dungeon::Dungeon_shared &dungeon_shared)
    {
        hitbox.update();
        max_HP=dungeon_shared.player->GetMaxHP();
        current_HP=dungeon_shared.player->GetCurrentHP();
    }
    const std::shared_ptr<Draw::ReTexture> &Heart_icon::img=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/topPanel/panelHeart.png");
}
