#ifndef THEAPP_HPP
#define THEAPP_HPP
#include "Game_object/dungeon/Dungeons.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "InitScreen.hpp"

enum class State:int{
    INIT,
    Prepare,
    PLAYING,
    GameOver,
    END
};

class TheApp {
public:
    TheApp();
    ~TheApp()=default;
    void update();
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const;
private:
    State current_state, next_state;
    InitScreen m_InitScreen;
    Dungeon::Dungeon_shared m_dungeon_shared;
    unsigned long long int seed;
    std::shared_ptr<Dungeon::Dungeons> m_dungeon;//for delay init
    bool fading, is_fade_to_black;
    float fade_a, fade_timer;

    void prepare();
    void to_init_prepare();
    static constexpr float FADE_TIME = 2.0F;
};

#endif
