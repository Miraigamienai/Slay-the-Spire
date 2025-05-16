#include "Game_object/top_panel/Deck_icon.hpp"
#include "RUtil/Image_book.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
namespace TopPanel
{
    TopPanel::Deck_icon::Deck_icon():Basic_panel(ICON_X,ICON_Y,ICON_W,ICON_H){

    }
    void TopPanel::Deck_icon::render(const std::shared_ptr<Draw::Draw_2D> &r2)const
    {
        r2->SetColor(-1);
        if(hitbox.Hovered()){
            r2->draw(img,ICON_X,ICON_Y,ICON_W,ICON_H,0,ICON_W/2.0F,ICON_H/2.0F,1.25F,1.25F);
        }
        else{
            r2->draw(img,ICON_X,ICON_Y,ICON_W,ICON_H);
        }
        m_font.render_center(r2,std::to_string(deck_num),ICON_X+ICON_W*3.0F/4.0F,ICON_Y+ICON_H/4.0F,Setting::SCALE*0.8F);
        
    }
    void TopPanel::Deck_icon::update(Dungeon::Dungeon_shared &dungeon_shared)
    {
        deck_num=dungeon_shared.card_group_handler.size<Card::GroupType::master_deck>();
        hitbox.update();
    }
    const std::shared_ptr<Draw::ReTexture> &Deck_icon::img=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/topPanel/deck.png");
}
