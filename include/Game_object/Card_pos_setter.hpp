#include <memory>

#include "Game_object/card/Cards.hpp"
#include "RUtil/Random.hpp"
#include "WindowSize.hpp"

namespace Card
{
    void set_card_pos(const std::shared_ptr<Card::Cards>&card, int s_cnt){
        constexpr float PADDING=30.0F*Setting::SCALE;
        card->SetY(static_cast<float>(Setting::WINDOW_HEIGHT)/2.0F);
        switch(s_cnt){
            case 0:
                card->SetX(static_cast<float>(Setting::WINDOW_WIDTH)/2.0F);
                break;
            case 1:
                card->SetX(static_cast<float>(Setting::WINDOW_WIDTH)/2.0F - PADDING - Card::Cards::IMG_WIDTH);
                break;
            case 2:
                card->SetX(static_cast<float>(Setting::WINDOW_WIDTH)/2.0F + PADDING + Card::Cards::IMG_WIDTH);
                break;
            case 3:
                card->SetX(static_cast<float>(Setting::WINDOW_WIDTH)/2.0F - (PADDING + Card::Cards::IMG_WIDTH)*2.0F);
                break;
            case 4:
                card->SetX(static_cast<float>(Setting::WINDOW_WIDTH)/2.0F + (PADDING + Card::Cards::IMG_WIDTH)*2.0F);
                break;
            default:
                card->SetX(RUtil::Random::GetRandomFloat(0.1F,0.9F)*Setting::SCALE);
                card->SetY(RUtil::Random::GetRandomFloat(0.2F,0.8F)*Setting::SCALE);
                break;
        }
    }    
} // namespace Card
