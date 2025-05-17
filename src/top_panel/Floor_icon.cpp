#include "Game_object/top_panel/Floor_icon.hpp"
#include "RUtil/Image_book.hpp"
namespace TopPanel
{
    TopPanel::Floor_icon::Floor_icon():Basic_panel(ICON_X,ICON_Y,ICON_W,ICON_H){

    }
    void TopPanel::Floor_icon::render(const std::shared_ptr<Draw::Draw_2D> &r2)const
    {
        r2->SetColor(-1);
        if(hitbox.Hovered()){
            r2->draw(img,ICON_X,ICON_Y,ICON_W,ICON_H,0,ICON_W/2.0F,ICON_H/2.0F,1.25F,1.25F);
        }
        else{
            r2->draw(img,ICON_X,ICON_Y,ICON_W,ICON_H);
        }
        
    }
    void TopPanel::Floor_icon::update()
    {
        hitbox.update();
    }
    const std::shared_ptr<Draw::ReTexture> &Floor_icon::img=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/topPanel/floor.png");
}
