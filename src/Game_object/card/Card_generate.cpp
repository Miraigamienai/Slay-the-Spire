#include "Game_object/card/Card_generate.hpp"
#include "RUtil/Random.hpp"

#include "Game_object/card/red/Anger.hpp"
#include "Game_object/card/red/Clash.hpp"
#include "Game_object/card/red/Defend.hpp"
#include "Game_object/card/red/Strike_red.hpp"

#include "Util/Logger.hpp"

namespace Card
{
    enum class RedCardName{
        Anger, Clash, Defend, Strike_red, SIZE
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
            default:
                LOG_ERROR("Unknown RedCardName");
        }
    }

    std::shared_ptr<Card::Cards> Card_generate::GetRandomRedCard(RUtil::Random &rng){
        return MakeRedCardFactory(static_cast<RedCardName>(rng.NextInt(static_cast<int>(RedCardName::SIZE))));
    }
} // namespace Card
