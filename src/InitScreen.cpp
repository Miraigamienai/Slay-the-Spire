#include <utility>

#include "InitScreen.hpp"
#include "Draw/Draw_2D.hpp"
#include "TheApp.hpp"
#include "Game_object/effect/Fade_wide.hpp"

#include "Util/Input.hpp"

static constexpr auto BUTTON_INIT_ORDER=std::array{
    Button::MenuButtonType::quit,
    Button::MenuButtonType::patch_notes,
    Button::MenuButtonType::setting,
    Button::MenuButtonType::stat,
    Button::MenuButtonType::info,
    Button::MenuButtonType::play
};

template <typename T, size_t...Is>
static inline auto ButtonCreater(const std::array<T, sizeof...(Is)>&id_arr, std::index_sequence<Is...>){
    return std::array{Button::Menu_button{id_arr[Is], static_cast<int>(Is)}...};
}

template <typename T, size_t N>
static inline auto ButtonCreater(const std::array<T, N>&id_arr){
    return ButtonCreater(id_arr, std::make_index_sequence<N>{});
}

InitScreen::InitScreen(State &state)
    :state(state),
    buttons(ButtonCreater(BUTTON_INIT_ORDER)),
    darken(false),
    fade_a(0.0F){}

void InitScreen::render(const std::shared_ptr<Draw::Draw_2D> &r2) const{
    bg.render(r2);
    for(const auto&it:buttons){
        it.render(r2, it.type==Button::MenuButtonType::quit || it.type==Button::MenuButtonType::play);
    }
    r2->SetColor(RUtil::BLACK, fade_a);
    r2->draw(Effect::Fade_wide::white_square, 0.0F, 0.0F, static_cast<float>(Setting::WINDOW_WIDTH), static_cast<float>(Setting::WINDOW_HEIGHT));
}

void InitScreen::update(){
    bg.update(darken);
    for(auto&it:buttons){
        it.update();
        if(it.type==Button::MenuButtonType::quit && it.Clicked()) state=State::END;
        else if(it.type==Button::MenuButtonType::play && it.Clicked()) darken=true;
    }
    
    if(Util::Input::IsKeyPressed(Util::Keycode::ESCAPE)) state=State::END;
    
    if(darken){
        fade_a+=RUtil::Game_Input::delta_time();
        if(fade_a>1.0F){
            fade_a=1.0F;
            state=State::Prepare;
        }
    }
}