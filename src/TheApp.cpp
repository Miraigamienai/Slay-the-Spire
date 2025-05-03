#include "TheApp.hpp"
#include "Game_object/card/red/Strike_red.hpp"//for test
#include "Game_object/card/red/Anger.hpp"//for test
#include "Game_object/card/red/Defend.hpp"//for test
#include "Game_object/card/red/Clash.hpp"//for test
#include "Core/Context.hpp"
#include "Game_object/character/Player.hpp"

TheApp::TheApp(){
    m_dungeon=std::make_shared<Dungeon::Dungeons>(m_dungeon_shared,seed);
    m_InitScreen=std::make_shared<InitScreen>();
    m_dungeon_shared.player=std::make_shared<Character::Player>();
    m_dungeon_shared.overlay.set_player_to_energy_panel(m_dungeon_shared.player); 
    for(int i=0;i<6;i++)//for test
        m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Strike_red>());
    for(int i=0;i<2;i++)
        m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Anger>());
    for(int i=0;i<1;i++)
        m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Defend>());
    for(int i=0;i<1;i++)
        m_dungeon_shared.card_group_handler.AddTop<Card::GroupType::master_deck>(std::make_shared<Card::Red::Clash>());
}
void TheApp::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
    switch (m_CurrentState) {
    case  AppStatus::State::INIT:
        m_InitScreen->render(r2);
        break;
    case  AppStatus::State::PLAYING:
        m_dungeon->render(r2);
        break;
    default:
        break;
    }
}
void TheApp::update(){
    switch (m_CurrentState) {
    case AppStatus::State::INIT:
        m_InitScreen->update();
        if(m_InitScreen->GetCurrentState()!=AppStatus::State::INIT){
            m_CurrentState=m_InitScreen->GetCurrentState();
        }
        break;
    case AppStatus::State::PLAYING:
        m_dungeon->update();
        break;
    case AppStatus::State::END:
        Core::Context::GetInstance()->SetExit(true);
        break;
    default:
        break;
    }
    
}