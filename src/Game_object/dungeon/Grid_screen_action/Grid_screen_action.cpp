#include "Game_object/dungeon/Grid_screen_action/Grid_screen_action.hpp"
#include "Game_object/card/Cards.hpp"
#include "Game_object/effect/Fade_wide.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "Draw/Draw_2D.hpp"
#include "WindowSize.hpp"

namespace Dungeon{
namespace GridScreenAction{
    void Grid_screen_action::render_two_card(const std::shared_ptr<Draw::Draw_2D> &r2, const std::shared_ptr<Card::Cards> &card1, const std::shared_ptr<Card::Cards> &card2)const{
        //left card
        card1->SetX(static_cast<float>(Setting::WINDOW_WIDTH)*0.36F, true);
        card1->SetY(static_cast<float>(Setting::WINDOW_HEIGHT)*0.5F, true);
        card1->render(r2);
        //right card
        card2->SetX(static_cast<float>(Setting::WINDOW_WIDTH)*0.63F, true);
        card2->SetY(static_cast<float>(Setting::WINDOW_HEIGHT)*0.5F, true);
        card2->render(r2);
    }

    void Grid_screen_action::render_dark_cover(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetColor(RUtil::BLACK, 0.8F);
        r2->draw(Effect::Fade_wide::white_square, 0.0F, 0.0F, static_cast<float>(Setting::WINDOW_WIDTH), static_cast<float>(Setting::WINDOW_HEIGHT)-64.0F*Setting::SCALE);
    }
}
}