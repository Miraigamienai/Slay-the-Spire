#pragma once

#include <array>
#include <memory>

#include "Game_object/interface/Is_screen.hpp"
#include "Game_object/room/Shop_item.hpp"
#include "Game_object/button/Cancel_button.hpp"
#include "Draw/NumberDrawer.hpp"
#include "RUtil/Hitbox.hpp"
#include "WindowSize.hpp"

//fwd decl
namespace Card{
    class Cards;
}
namespace Effect{
    class Effect_group;
}

namespace Dungeon{
class Shop_screen final:public Interface::Is_screen
{
public:
    Shop_screen();
    ~Shop_screen()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void open(std::array<Shop_card_item, 5> &card1, std::array<Shop_card_item, 2> &card2){
        this->card1=&card1;
        this->card2=&card2;
        this->current_y=static_cast<float>(Setting::WINDOW_HEIGHT);
        this->hand_x = this->hand_target_x = static_cast<float>(Setting::WINDOW_WIDTH)/2.0F;
        this->hand_y = this->hand_target_y = static_cast<float>(Setting::WINDOW_HEIGHT);
        this->hand_timer=1.0F;
        this->cancel.show();
        closing=false;
        this->set_cards_x_pos();
    }    
private:
    std::array<Shop_card_item, 5> *card1;
    std::array<Shop_card_item, 2> *card2;
    Draw::NumberDrawer price_drawer;
    Shop_card_item* hovered_card_item;
    Button::Cancel_button cancel;
    float not_hovered_timer;
    bool something_hovered;
    float current_y;
    float hand_timer;
    float hand_x, hand_target_x;
    float hand_y, hand_target_y;
    float hand_floaty_x, hand_floaty_y;
    float hand_floaty_speed_x, hand_floaty_speed_y;
    int player_current_gold;
    int purge_cost;
    float purge_card_scale;
    bool can_purge;
    RUtil::Hitbox purge_hb;
    bool closing;
    void hand_update();
    void purge_update();
    void move_hand(float x,float y)noexcept{
        hand_target_x = x - 50.0F * Setting::SCALE;
        hand_target_y = y + 90.0F * Setting::SCALE;
    }
    void cards_update(Effect::Effect_group &top_effs);
    void set_cards_x_pos()const;
    void render_cards(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    void render_purge(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    static const std::shared_ptr<Draw::ReTexture>&GOLD_IMG,&HAND_IMG;
    static constexpr float TOP_ROW_Y = 760.0F * Setting::SCALE,
                           BOTTOM_ROW_Y = 337.0F * Setting::SCALE,
                           DRAW_START_X = static_cast<float>(Setting::WINDOW_WIDTH) * 0.16F,//the right and left space
                           GOLD_IMG_OFFSET_X = -50.0F * Setting::SCALE,
                           GOLD_IMG_OFFSET_Y = -215.0F * Setting::SCALE,
                           PRICE_TEXT_OFFSET_X = 16.0F * Setting::SCALE,
                           PRICE_TEXT_OFFSET_Y = -180.0F * Setting::SCALE,
                           PURGE_CARD_X = 1554.0F * Setting::SCALE,
                           FLOATY_MIN_SPEED = 0.4F*20.0F*0.1F,
                           FLOATY_MAX_SPEED = 3.0F*20.0F*0.1F,
                           FLOATY_THRESHOLD = 0.95F*20.0F,
                           NOT_HOVERED_TIME = 1.0F;
    static constexpr int PRICE_FONT_SIZE=23;
    static constexpr int DEFAULT_PURGE_COST=75,
                         PURGE_INCREASE_PRICE=25;
};
}