#include "Game_object/top_panel/Setting_icon.hpp"
#include "RUtil/Image_book.hpp"
namespace TopPanel
{
    TopPanel::Setting_icon::Setting_icon():Basic_panel(ICON_X,ICON_Y,ICON_W,ICON_H){

    }
    void TopPanel::Setting_icon::render(const std::shared_ptr<Draw::Draw_2D> &r2)const
    {
        r2->SetColor(-1);
        if(hitbox.Hovered()){
            r2->draw(img,ICON_X,ICON_Y,ICON_W,ICON_H,0,ICON_W/2.0F,ICON_H/2.0F,1.25F,1.25F);
        }
        else{
            r2->draw(img,ICON_X,ICON_Y,ICON_W,ICON_H);
        }
        
    }
    void TopPanel::Setting_icon::update(Dungeon::Dungeon_shared &dungeon_shared)
    {
        hitbox.update();
    }
    const std::shared_ptr<Draw::ReTexture> &Setting_icon::img=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/topPanel/settings.png");
}
