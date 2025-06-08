#include "Game_object/card/Card_generate.hpp"
#include "RUtil/Random.hpp"

#include "Game_object/card/red/Anger.hpp"
#include "Game_object/card/red/Clash.hpp"
#include "Game_object/card/red/Defend.hpp"
#include "Game_object/card/red/Strike_red.hpp"
#include "Game_object/card/red/Body_slam.hpp"
#include "Game_object/card/red/Flex.hpp"
#include "Game_object/card/red/Iron_wave.hpp"
#include "Game_object/card/red/Strike_red.hpp"
#include "Game_object/card/red/Twin_strike.hpp"
#include "Game_object/card/red/Inflame.hpp"
#include "Game_object/card/red/Bludgeon.hpp"
#include "Game_object/card/red/Shrug_it_off.hpp"
#include "Game_object/card/red/Pommel_strike.hpp"
#include "Game_object/card/red/Wild_strike.hpp"
#include "Game_object/card/red/Entrench.hpp"
#include "Game_object/card/status/Wound.hpp"


#include "Util/Logger.hpp"

namespace Card
{
    enum class RedCardName{
        Anger, Clash, Defend, Strike_red, Body_slam, Flex, Iron_wave, Twin_strike, Inflame, Bludgeon, Shrug_it_off, Pommel_strike, 
        Entrench, Wild_strike, SIZE
    };

    static inline std::shared_ptr<Card::Cards> MakeRedCardFactory(RedCardName name) {
        using namespace Red;
        switch (name) {
            case RedCardName::Anger:
                return std::make_shared<Anger>();
            case RedCardName::Clash:
                return std::make_shared<Clash>();
            case RedCardName::Defend:
                return std::make_shared<Defend>();
            case RedCardName::Strike_red:
                return std::make_shared<Strike_red>();
            case RedCardName::Body_slam:
                return std::make_shared<Body_slam>();
            case RedCardName::Flex:
                return std::make_shared<Flex>();
            case RedCardName::Iron_wave:
                return std::make_shared<Iron_wave>();
            case RedCardName::Twin_strike:
                return std::make_shared<Twin_strike>();
            case RedCardName::Inflame:
                return std::make_shared<Inflame>();
            case RedCardName::Bludgeon:
                return std::make_shared<Bludgeon>();
            case RedCardName::Shrug_it_off:
                return std::make_shared<Shrug_it_off>();
            case RedCardName::Pommel_strike:
                return std::make_shared<Pommel_strike>();
            case RedCardName::Entrench:
                return std::make_shared<Entrench>();
            case RedCardName::Wild_strike:
                return std::make_shared<Wild_strike>();
            default:
                LOG_ERROR("Unknown RedCardName");
                return std::make_shared<Strike_red>();
        }
    }

    std::shared_ptr<Card::Cards> Card_generate::GetRandomRedCard(RUtil::Random &rng){
        return MakeRedCardFactory(static_cast<RedCardName>(rng.NextInt(static_cast<int>(RedCardName::SIZE))));
    }
} // namespace Card
