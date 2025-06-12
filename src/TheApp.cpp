#include "TheApp.hpp"

#include "Game_object/card/red/Bash.hpp"
#include "Game_object/card/red/Defend.hpp"
#include "Game_object/card/red/Strike_red.hpp"


//for test
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


#include "Game_object/effect/Fade_wide.hpp"
#include "RUtil/Random.hpp"

#include "Core/Context.hpp"

TheApp::TheApp()
    :current_state(State::INIT),
    m_InitScreen(current_state),
    seed(0ULL),
    fading(false),
    fade_a(0.0F){}

void TheApp::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
    switch (current_state) {
    case State::INIT:
        m_InitScreen.render(r2);
        break;
    case State::PLAYING:
    case State::GameOver:
        m_dungeon->render(r2);
        break;
    default:
        break;
    }
    r2->SetColor(RUtil::BLACK, fade_a);
    r2->draw(Effect::Fade_wide::white_square, 0.0F, 0.0F, static_cast<float>(Setting::WINDOW_WIDTH), static_cast<float>(Setting::WINDOW_HEIGHT));
}

void TheApp::update(){
    if(fading){
        fade_a = RUtil::Math::interpolation_fade(1.0F, 0.0F, 1.0F-fade_timer/FADE_TIME);
        fade_timer-=RUtil::Game_Input::delta_time();
        if(fade_timer<0.0F) fading=false;
        if(fade_a>0.75F) return;
    }

    switch (current_state) {
        case State::INIT:
            m_InitScreen.update();
            break;
        case State::Prepare:
            prepare();
            current_state=State::PLAYING;
            break;
        case State::PLAYING:
            m_dungeon->update();
            break;
        case State::GameOver:
            to_init_prepare();
            current_state=State::INIT;
            break;
        case State::END:
            Core::Context::GetInstance()->SetExit(true);
            break;
        default:
            break;
    }
}

void TheApp::prepare(){
    seed=RUtil::Random::GetRandomDefault();
    m_dungeon_shared.player=std::make_shared<Character::Player>();
    Card::Card_soul::SetTrailColor(m_dungeon_shared.player->GetCardTrailColor());
    Card::Cards::SetRenderColor(m_dungeon_shared.player->GetCardRenderColor());
    m_dungeon_shared.manager.reset();
    m_dungeon_shared.current_node = m_dungeon_shared.next_node = nullptr;
    m_dungeon=std::make_shared<Dungeon::Dungeons>(m_dungeon_shared, seed, current_state);

    
    m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Bash>());
    for(int i=0;i<4;i++)
    m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Defend>());
    for(int i=0;i<5;i++)
    m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Strike_red>());


    //for test
    m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Anger>());
    m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Body_slam>());
    m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Clash>());
    m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Clothesline>());
    m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Iron_wave>());
    m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Pommel_strike>());
    m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Shrug_it_off>());
    m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Twin_strike>());
    m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Wild_strike>());
    m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Bloodletting>());
    m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Entrench>());
    m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Hemokinesis>());
    m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Inflame>());
    m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Power_through>());
    m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Shockwave>());
    m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Uppercut>());

    m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Barricade>());
    m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Bludgeon>());

    
    fade();
}

void TheApp::to_init_prepare(){
    m_InitScreen.reset();
    fade_timer=FADE_TIME;
    fade();
}
