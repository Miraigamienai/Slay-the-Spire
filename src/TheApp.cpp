#include "TheApp.hpp"
#include "Game_object/card/red/Strike_red.hpp"//for test
#include "Game_object/card/red/Anger.hpp"//for test
#include "Game_object/card/red/Defend.hpp"//for test
#include "Game_object/card/red/Clash.hpp"//for test
#include "Game_object/card/red/Clothesline.hpp"//for test
#include "Game_object/card/red/Shockwave.hpp"//for test
#include "Game_object/card/red/Barricade.hpp"//for test
#include "Game_object/effect/Fade_wide.hpp"
#include "RUtil/Random.hpp"

#include "Core/Context.hpp"

TheApp::TheApp()
    :current_state(State::INIT),
    m_InitScreen(current_state),
    seed(0ULL),
    fading(false),
    is_fade_to_black(false),
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
        if(is_fade_to_black) fade_a = RUtil::Math::interpolation_fade(0.0F, 1.0F, 1.0F-fade_timer/FADE_TIME);
        else fade_a = RUtil::Math::interpolation_fade(1.0F, 0.0F, 1.0F-fade_timer/FADE_TIME);
        
        fade_timer-=RUtil::Game_Input::delta_time();
        if(fade_timer<0.0F){
            if(is_fade_to_black){
                is_fade_to_black=false;
                fade_timer=FADE_TIME;
                current_state=next_state;
            }else{
                fading=false;
            }
        }
        if(is_fade_to_black || fade_a>0.5F) return;
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
    m_dungeon_shared.overlay.set_player_to_energy_panel(m_dungeon_shared.player);
    Card::Card_soul::SetTrailColor(m_dungeon_shared.player->GetCardTrailColor());
    Card::Cards::SetRenderColor(m_dungeon_shared.player->GetCardRenderColor());
    m_dungeon_shared.manager.reset();
    m_dungeon=std::make_shared<Dungeon::Dungeons>(m_dungeon_shared, seed, current_state);
    //card colors set 
    for(int i=0;i<2;i++)//for test
        m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Strike_red>());
    for(int i=0;i<2;i++)
        m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Anger>());
    for(int i=0;i<1;i++)
        m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Defend>());
    for(int i=0;i<1;i++)
        m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Clash>());
    for(int i=0;i<1;i++)
        m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Clothesline>());
    for(int i=0;i<1;i++)
        m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Shockwave>());
    for(int i=0;i<1;i++)
        m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Barricade>());
    
    fading=true;
    is_fade_to_black=false;
    fade_timer=FADE_TIME;
    fade_a=1.0F;
}

void TheApp::to_init_prepare(){
    m_InitScreen.reset();
    next_state=State::INIT;
    fade_timer=FADE_TIME;
    is_fade_to_black=true;
    fading=true;
    fade_a=0.0F;
}
