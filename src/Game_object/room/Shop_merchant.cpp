#include "Game_object/room/Shop_merchant.hpp"
#include "Game_object/card/Card_generate.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Image_book.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/ReTexture.hpp"

namespace Room{
    Shop_merchant::Shop_merchant(Dungeon::Dungeon_shared& dungeon_shared)
        :hb(DRAW_X+250.0F*Setting::SCALE, DRAW_Y+130.0F*Setting::SCALE, HB_W, HB_H, true)
    {
        //TODO: card random probability need to be set
        for(auto &it:card1){
            it.card=Card::Card_generate::GetRandomRedCard(dungeon_shared.random_package.card_reward_rng);
            it.price=80 + RUtil::Random::GetRandomInt(40);
        }
        for(auto &it:card2){
            it.card=Card::Card_generate::GetRandomRedCard(dungeon_shared.random_package.card_reward_rng);
            it.price=80 + RUtil::Random::GetRandomInt(40);
        }
    }

    void Shop_merchant::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetColor(RUtil::WHITE);
        r2->draw(IMG, DRAW_X, DRAW_Y, 512.0F*Setting::SCALE, 512.0F*Setting::SCALE);
        if(this->hb.Hovered()){
            r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
            r2->SetColor(RUtil::WHITE, 0.5F);
            r2->draw(IMG, DRAW_X, DRAW_Y, 512.0F*Setting::SCALE, 512.0F*Setting::SCALE);
            r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
    }

    void Shop_merchant::update(Dungeon::Dungeon_shared& dungeon_shared){
        this->hb.update();
        //open screen if the hb be clicked and the shop screen is not opening
        if(this->hb.Clicked() && !dungeon_shared.manager.current_screen_equals(Interface::ScreenType::shop)){
            dungeon_shared.manager.open<Interface::ScreenType::shop>(this->card1, this->card2);
        }
    }

    const std::shared_ptr<Draw::ReTexture> &Shop_merchant::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/shop/merchantObjects.png");
}