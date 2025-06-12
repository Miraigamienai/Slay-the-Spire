#include "Game_object/card/Card_generate.hpp"
#include "RUtil/Random.hpp"

#include "Game_object/card/red/Defend.hpp"
#include "Game_object/card/red/Strike_red.hpp"

#include "Game_object/card/red/Anger.hpp"
#include "Game_object/card/red/Body_slam.hpp"
#include "Game_object/card/red/Clash.hpp"
#include "Game_object/card/red/Clothesline.hpp"
#include "Game_object/card/red/Iron_wave.hpp"
#include "Game_object/card/red/Pommel_strike.hpp"
#include "Game_object/card/red/Shrug_it_off.hpp"
#include "Game_object/card/red/Twin_strike.hpp"
#include "Game_object/card/red/Wild_strike.hpp"

#include "Game_object/card/red/Bloodletting.hpp"
#include "Game_object/card/red/Entrench.hpp"
#include "Game_object/card/red/Hemokinesis.hpp"
#include "Game_object/card/red/Inflame.hpp"
#include "Game_object/card/red/Power_through.hpp"
#include "Game_object/card/red/Shockwave.hpp"
#include "Game_object/card/red/Uppercut.hpp"

#include "Game_object/card/red/Barricade.hpp"
#include "Game_object/card/red/Bludgeon.hpp"


#include "Util/Logger.hpp"

namespace Card
{
    enum class RedCardBasic{
        Bash, Defend, Strike_red, SIZE
    };
    enum class RedCommonCard{
        Anger,  Body_slam, Clash, Clothesline, Iron_wave, Pommel_strike,Shrug_it_off, Twin_strike, Wild_strike, SIZE
    };
    enum class RedUncommonCard{
        Bloodletting, Entrench, Hemokinesis, Inflame, Power_through,Shockwave, Uppercut, SIZE
    };

    enum class RedRareCard{
        Barricade, Bludgeon, SIZE
    };

    enum class RedCardName{
        Anger, Clash, Defend, Strike_red, Body_slam, Iron_wave, Twin_strike, Inflame, Bludgeon, Shrug_it_off, Pommel_strike, 
        Entrench, Wild_strike,
        Bloodletting, Hemokinesis, Power_through, Uppercut , SIZE
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
            case RedCardName::Bloodletting:
                return std::make_shared<Bloodletting>();
            case RedCardName::Hemokinesis:
                return std::make_shared<Hemokinesis>();
            case RedCardName::Power_through:
                return std::make_shared<Power_through>();
            case RedCardName::Uppercut:
                return std::make_shared<Uppercut>();
            default:
                LOG_ERROR("Unknown RedCardName");
                return std::make_shared<Strike_red>();
        }
    }
    static inline std::shared_ptr<Card::Cards> MakeRedCommonCardFactory(RedCommonCard name) {
        using namespace Red;
        switch (name) {
            case RedCommonCard::Anger:
                return std::make_shared<Anger>();
            case RedCommonCard::Body_slam:
                return std::make_shared<Body_slam>();
            case RedCommonCard::Clash:
                return std::make_shared<Clash>();
            case RedCommonCard::Clothesline:
                return std::make_shared<Clothesline>();
            case RedCommonCard::Iron_wave:
                return std::make_shared<Iron_wave>();
            case RedCommonCard::Pommel_strike:
                return std::make_shared<Pommel_strike>();
            case RedCommonCard::Shrug_it_off:
                return std::make_shared<Shrug_it_off>();
            case RedCommonCard::Twin_strike:
                return std::make_shared<Twin_strike>();
            case RedCommonCard::Wild_strike:
                return std::make_shared<Wild_strike>();
            default:
                LOG_ERROR("Unknown RedCommonCard");
                return nullptr;
        }
    }
    static inline std::shared_ptr<Card::Cards> MakeRedUncommonCardFactory(RedUncommonCard name) {
        using namespace Red;
        switch (name) {
            case RedUncommonCard::Bloodletting:
                return std::make_shared<Bloodletting>();
            case RedUncommonCard::Entrench:
                return std::make_shared<Entrench>();
            case RedUncommonCard::Hemokinesis:
                return std::make_shared<Hemokinesis>();
            case RedUncommonCard::Inflame:
                return std::make_shared<Inflame>();
            case RedUncommonCard::Power_through:
                return std::make_shared<Power_through>();
            case RedUncommonCard::Shockwave:
                return std::make_shared<Shockwave>();
            case RedUncommonCard::Uppercut:
                return std::make_shared<Uppercut>();
            default:
                LOG_ERROR("Unknown RedUncommonCard");
                return nullptr;
        }
    }
    static inline std::shared_ptr<Card::Cards> MakeRedRareCardFactory(RedRareCard name) {
        using namespace Red;
        switch (name) {
            case RedRareCard::Barricade:
                return std::make_shared<Barricade>();
            case RedRareCard::Bludgeon:
                return std::make_shared<Bludgeon>();
            default:
                LOG_ERROR("Unknown RedRareCard");
                return nullptr;
        }
    }


    std::shared_ptr<Card::Cards> Card_generate::GetRandomRedCard(RUtil::Random &rng){
        return MakeRedCardFactory(static_cast<RedCardName>(rng.NextInt(static_cast<int>(RedCardName::SIZE))));
    }
} // namespace Card
