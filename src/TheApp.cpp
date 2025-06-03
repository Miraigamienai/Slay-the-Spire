#include "TheApp.hpp"
#include "Game_object/card/red/Strike_red.hpp"//for test
#include "Game_object/card/red/Anger.hpp"//for test
#include "Game_object/card/red/Defend.hpp"//for test
#include "Game_object/card/red/Clash.hpp"//for test
#include "Game_object/card/red/Clothesline.hpp"//for test
#include "Game_object/card/red/Shockwave.hpp"//for test
#include "Game_object/card/red/Barricade.hpp"//for test
#include "Core/Context.hpp"
#include "Game_object/character/Player.hpp"
TheApp::TheApp()
    :current_state(State::INIT),
    m_InitScreen(current_state)
{
    m_dungeon=std::make_shared<Dungeon::Dungeons>(m_dungeon_shared,seed);
    m_dungeon_shared.player=std::make_shared<Character::Player>();
    m_dungeon_shared.overlay.set_player_to_energy_panel(m_dungeon_shared.player);
    //card colors set 
    Card::Card_soul::SetTrailColor(m_dungeon_shared.player->GetCardTrailColor());
    Card::Cards::SetRenderColor(m_dungeon_shared.player->GetCardRenderColor());
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
}
void TheApp::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
    switch (current_state) {
    case State::INIT:
        m_InitScreen.render(r2);
        break;
    case State::PLAYING:
        m_dungeon->render(r2);
        break;
    default:
        break;
    }
}
void TheApp::update(){
    switch (current_state) {
    case State::INIT:
        m_InitScreen.update();
        break;
    case State::PLAYING:
        m_dungeon->update();
        if (m_dungeon->is_game_over()){ // there is a bug
            current_state=State::INIT;
            m_dungeon.reset();
            m_dungeon_shared.player.reset();
            m_dungeon=std::make_shared<Dungeon::Dungeons>(m_dungeon_shared,seed);
            m_dungeon_shared.player=std::make_shared<Character::Player>();
            m_dungeon_shared.overlay.set_player_to_energy_panel(m_dungeon_shared.player); 
            
        }
        break;
    case State::END:
        Core::Context::GetInstance()->SetExit(true);
        break;
    default:
        break;
    }
    
}