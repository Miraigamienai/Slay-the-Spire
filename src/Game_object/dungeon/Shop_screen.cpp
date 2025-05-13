#include <string>

#include "Game_object/dungeon/Shop_screen.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/card/Cards.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Some_Math.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/All_Image.hpp"
#include "Draw/ReTexture.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/Draw_2D.hpp"

namespace Dungeon{
    static inline auto&RUG_IMG(){
        using namespace RUtil;
        static const auto&IMG=[](){
            switch(Setting::language){
                case Language::eng:return Image_book::GetTexture(RESOURCE_DIR"/Image/shop/rug/eng.png");
                case Language::jpn:return Image_book::GetTexture(RESOURCE_DIR"/Image/shop/rug/jpn.png");
                default:return Image_book::GetTexture(RESOURCE_DIR"/Image/shop/rug/zhs.png");
            }
        }();
        return IMG;
    }

    static inline auto&PURGE_IMG(){
        using namespace RUtil;
        static const auto&IMG=[](){
            switch(Setting::language){
                case Language::eng:return Image_book::GetTexture(RESOURCE_DIR"/Image/shop/purge/eng.png");
                case Language::jpn:return Image_book::GetTexture(RESOURCE_DIR"/Image/shop/purge/jpn.png");
                default:return Image_book::GetTexture(RESOURCE_DIR"/Image/shop/purge/zhs.png");
            }
        }();
        return IMG;
    }

    static inline auto&SALE_TAG_IMG(){
        using namespace RUtil;
        static const auto&IMG=[](){
            switch(Setting::language){
                case Language::eng:return Image_book::GetTexture(RESOURCE_DIR"/Image/shop/sale_tag/eng.png");
                case Language::jpn:return Image_book::GetTexture(RESOURCE_DIR"/Image/shop/sale_tag/jpn.png");
                default:return Image_book::GetTexture(RESOURCE_DIR"/Image/shop/sale_tag/zhs.png");
            }
        }();
        return IMG;
    }

    static inline auto&SOLD_OUT_IMG(){
        using namespace RUtil;
        static const auto&IMG=[](){
            switch(Setting::language){
                case Language::eng:return Image_book::GetTexture(RESOURCE_DIR"/Image/shop/sold_out/eng.png");
                case Language::jpn:return Image_book::GetTexture(RESOURCE_DIR"/Image/shop/sold_out/jpn.png");
                default:return Image_book::GetTexture(RESOURCE_DIR"/Image/shop/sold_out/zhs.png");
            }
        }();
        return IMG;
    }

    Shop_screen::Shop_screen()
        :Interface::Is_screen(Interface::ScreenType::shop),
        card1(nullptr),
        card2(nullptr),
        price_drawer(PRICE_FONT_SIZE),
        hovered_card_item(nullptr),
        not_hovered_timer(0.0F),
        current_y(Setting::WINDOW_HEIGHT),
        hand_timer(0.0F),
        hand_x(0.0F),
        hand_target_x(0.0F),
        hand_y(0.0F),
        hand_target_y(0.0F),
        hand_floaty_x(0.0F),
        hand_floaty_y(0.0F),
        hand_floaty_speed_x(RUtil::Random::GetRandomFloat(FLOATY_MIN_SPEED, FLOATY_MAX_SPEED)),
        hand_floaty_speed_y(RUtil::Random::GetRandomFloat(FLOATY_MIN_SPEED, FLOATY_MAX_SPEED)),
        player_current_gold(0),
        purge_cost(DEFAULT_PURGE_COST),
        purge_card_scale(Setting::SCALE)
    {

    }
    
    void Shop_screen::update(Dungeon::Dungeon_shared &dungeon_shared){
        //player current gold update
        player_current_gold=dungeon_shared.player->GetGold();
        //current_y update
        if(current_y!=0.0F)
            current_y=RUtil::Math::varlerp(current_y, 0.0F, 5.0F, Setting::SCALE);
        //cards && hovered card update
        cards_update(dungeon_shared.top_effs);
        //hand update
        hand_update();
        //hovered card item action check
        if(hovered_card_item==nullptr){//not hover
            not_hovered_timer+=RUtil::Game_Input::delta_time();
            if(not_hovered_timer>1.0F) hand_target_y=static_cast<float>(Setting::WINDOW_HEIGHT);
        }else{//hover
            not_hovered_timer=0.0F;
            //check click
            if(hovered_card_item->card->HitboxClicked() && hovered_card_item->price <= player_current_gold && on_top){
                //buy the card
                //reduce gold
                player_current_gold-=hovered_card_item->price;
                dungeon_shared.player->ReduceGold(hovered_card_item->price);
                //obtain the card
                dungeon_shared.card_group_handler.obtain(hovered_card_item->card);
                //remove the card from array
                for(auto&it:*card1) if(&it==hovered_card_item)it.card=nullptr; 
                for(auto&it:*card2) if(&it==hovered_card_item)it.card=nullptr; 
                //set nullptr
                hovered_card_item=nullptr;
                //reset not_hovered_timer
                not_hovered_timer=1.0F;
            }
        }

    }
    
    void Shop_screen::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        //rug
        r2->SetColor(RUtil::WHITE);
        r2->draw(RUG_IMG(), 0.0F, this->current_y, static_cast<float>(Setting::WINDOW_WIDTH), static_cast<float>(Setting::WINDOW_HEIGHT));
        //cards
        render_cards(r2);
        //purge
        render_purge(r2);
        //hand
        r2->draw(HAND_IMG, hand_x+hand_floaty_x, hand_y+hand_floaty_y, (float)HAND_IMG->GetWidth()*Setting::SCALE, (float)HAND_IMG->GetHeight()*Setting::SCALE);
    }
    
    void Shop_screen::render_cards(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        for(const auto&it:*card1){
            if(it.card==nullptr) continue;
            it.card->render(r2);
            r2->SetColor(RUtil::WHITE);
            r2->draw(GOLD_IMG, it.card->GetX()+GOLD_IMG_OFFSET_X, it.card->GetY()+GOLD_IMG_OFFSET_Y - (it.card->GetDrawScale()-0.75F)*200.0F*Setting::SCALE, (float)GOLD_IMG->GetWidth()*Setting::SCALE, (float)GOLD_IMG->GetHeight()*Setting::SCALE);
            if(it.price>player_current_gold)//not enough gold
                r2->SetColor_RGBA(RUtil::ToRGBA(RUtil::Colors::SALMON));
            else 
                r2->SetColor_RGBA(RUtil::ToRGBA(RUtil::Colors::SKY_BLUE));
            price_drawer.render_center(r2, std::to_string(it.price), it.card->GetX()+PRICE_TEXT_OFFSET_X, it.card->GetY()+PRICE_TEXT_OFFSET_Y - (it.card->GetDrawScale()-0.75F)*200.0F*Setting::SCALE, Setting::SCALE);
        }
        for(const auto&it:*card2){
            if(it.card==nullptr) continue;
            it.card->render(r2);
            r2->SetColor(RUtil::WHITE);
            r2->draw(GOLD_IMG, it.card->GetX()+GOLD_IMG_OFFSET_X, it.card->GetY()+GOLD_IMG_OFFSET_Y - (it.card->GetDrawScale()-0.75F)*200.0F*Setting::SCALE, (float)GOLD_IMG->GetWidth()*Setting::SCALE, (float)GOLD_IMG->GetHeight()*Setting::SCALE);
            if(it.price>player_current_gold)//not enough gold
                r2->SetColor_RGBA(RUtil::ToRGBA(RUtil::Colors::SALMON));
            else 
                r2->SetColor_RGBA(RUtil::ToRGBA(RUtil::Colors::SKY_BLUE));
            price_drawer.render_center(r2, std::to_string(it.price), it.card->GetX()+PRICE_TEXT_OFFSET_X, it.card->GetY()+PRICE_TEXT_OFFSET_Y - (it.card->GetDrawScale()-0.75F)*200.0F*Setting::SCALE, Setting::SCALE);
        }
    }
    
    void Shop_screen::render_purge(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        const float purge_card_y=this->current_y+BOTTOM_ROW_Y;
        //render bg
        r2->SetColor(RUtil::BLACK, 0.25F);
        auto&img=RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_512_bg_skill_silhouette);
        r2->draw(img, PURGE_CARD_X+18.0F*Setting::SCALE+img->offsetX-static_cast<float>(img->original_width)/2.0F, purge_card_y - 14.0F*Setting::SCALE+img->offsetY-static_cast<float>(img->original_height)/2.0F, static_cast<float>(img->GetRegionWidth()), static_cast<float>(img->GetRegionHeight()), 0.0F, static_cast<float>(img->original_width)/2.0F-img->offsetX, static_cast<float>(img->original_height)/2.0F-img->offsetY, purge_card_scale, purge_card_scale);
        //render main purge
        r2->SetColor(RUtil::WHITE);
        if(can_purge){
            const float purge_scale_offset_y=(purge_card_scale/Setting::SCALE-0.75F)*200.0F*Setting::SCALE;
            //purge img
            r2->draw(PURGE_IMG(), PURGE_CARD_X-256.0F, purge_card_y-256.0F, 512.0F, 512.0F, 0.0F, 256.0F, 256.0F, purge_card_scale, purge_card_scale);
            //gold
            r2->draw(GOLD_IMG, PURGE_CARD_X+GOLD_IMG_OFFSET_X, purge_card_y+GOLD_IMG_OFFSET_Y-purge_scale_offset_y, (float)GOLD_IMG->GetWidth()*Setting::SCALE, (float)GOLD_IMG->GetHeight()*Setting::SCALE);
            //price text
            r2->SetColor_RGBA(purge_cost>player_current_gold ? RUtil::ToRGBA(RUtil::Colors::SALMON) : RUtil::WHITE);
            price_drawer.render_center(r2, std::to_string(purge_cost), PURGE_CARD_X+PRICE_TEXT_OFFSET_X, purge_card_y+PRICE_TEXT_OFFSET_Y - purge_scale_offset_y, Setting::SCALE);
        }else{//if sold out
            r2->draw(SOLD_OUT_IMG(), PURGE_CARD_X-256.0F, purge_card_y-256.0F, 512.0F, 512.0F, 0.0F, 256.0F, 256.0F, purge_card_scale, purge_card_scale);
        }     
    }

    void Shop_screen::hand_update(){
        //move hand to hovered card if not nullptr
        if(hovered_card_item!=nullptr) move_hand(hovered_card_item->card->GetX()-Card::Cards::IMG_WIDTH/2.0F, hovered_card_item->card->GetY());
        //hand update
        if(hand_timer>0.0F){
            hand_timer-=RUtil::Game_Input::delta_time();
        }else{
            hand_x=RUtil::Math::Apply(hand_x, hand_target_x, RUtil::Game_Input::delta_time()*6.0F);
            if(hand_y>hand_target_y)//up to down
                hand_y=RUtil::Math::Apply(hand_y, hand_target_y, RUtil::Game_Input::delta_time()*6.0F);
            else //down to up
                hand_y=RUtil::Math::Apply(hand_y, hand_target_y, RUtil::Game_Input::delta_time()*1.5F);
        }
        //hand floaty update
        hand_floaty_x += hand_floaty_speed_x*RUtil::Game_Input::delta_time();
        hand_floaty_y += hand_floaty_speed_y*RUtil::Game_Input::delta_time();
        //x
        if(hand_floaty_x>FLOATY_THRESHOLD)
            hand_floaty_speed_x = -RUtil::Random::GetRandomFloat(FLOATY_MIN_SPEED, FLOATY_MAX_SPEED);
        else if(hand_floaty_x < -FLOATY_THRESHOLD)
            hand_floaty_speed_x = RUtil::Random::GetRandomFloat(FLOATY_MIN_SPEED, FLOATY_MAX_SPEED);
        //y
        if(hand_floaty_y>FLOATY_THRESHOLD)
            hand_floaty_speed_y = -RUtil::Random::GetRandomFloat(FLOATY_MIN_SPEED, FLOATY_MAX_SPEED);
        else if(hand_floaty_y < -FLOATY_THRESHOLD)
            hand_floaty_speed_y = RUtil::Random::GetRandomFloat(FLOATY_MIN_SPEED, FLOATY_MAX_SPEED);
    }

    void Shop_screen::set_cards_x_pos()const{
        constexpr float SPACE_BETWEEN_CARD=(static_cast<float>(Setting::WINDOW_WIDTH) - DRAW_START_X*2.0F - Card::Cards::IMG_WIDTH_S*5.0F)/4.0F;
        constexpr float CARD_PAD_X=SPACE_BETWEEN_CARD + Card::Cards::IMG_WIDTH_S;
        for(int i=0;i<5;i++){
            if((*card1)[i].card==nullptr) continue;
            (*card1)[i].card->SetX(static_cast<float>(Setting::WINDOW_WIDTH)/2.0F, true);
            (*card1)[i].card->SetX(DRAW_START_X + Card::Cards::IMG_WIDTH_S/2.0F + CARD_PAD_X*static_cast<float>(i));
        }
        for(int i=0;i<2;i++){
            if((*card2)[i].card==nullptr) continue;
            (*card2)[i].card->SetX(static_cast<float>(Setting::WINDOW_WIDTH)/2.0F, true);
            (*card2)[i].card->SetX(DRAW_START_X + Card::Cards::IMG_WIDTH_S/2.0F + CARD_PAD_X*static_cast<float>(i));
        }
    }

    void Shop_screen::cards_update(Effect::Effect_group &top_effs){
        hovered_card_item=nullptr;
        for(auto&it:*card1){
            if(it.card==nullptr) continue;
            it.card->SetY(this->current_y + TOP_ROW_Y, true);
            it.card->update(top_effs);
            if(it.card->HitboxHovered()){
                hovered_card_item=&it;
                it.card->Hover();
            }else{
                it.card->Unhover();
            }
        }
        for(auto&it:*card2){
            if(it.card==nullptr) continue;
            it.card->SetY(this->current_y + BOTTOM_ROW_Y, true);
            it.card->update(top_effs);
            if(it.card->HitboxHovered()){
                hovered_card_item=&it;
                it.card->Hover();
            }else{
                it.card->Unhover();
            }
        }
    }   

    const std::shared_ptr<Draw::ReTexture>&Shop_screen::GOLD_IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/shop/gold.png"),
                                          &Shop_screen::HAND_IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/shop/merchantHand.png");
}