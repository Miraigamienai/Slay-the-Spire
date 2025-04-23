#pragma once

namespace Dungeon{
    struct Dungeon_shared;
}

namespace Action{
class Actions
{
public:
    virtual ~Actions()=default;
    virtual void update(Dungeon::Dungeon_shared &dungeon_shared)=0;
    bool IsDone()const{return is_done;}
protected:
    void TimeGo(){
        duration-=DT;
        if(duration<0.0F)
            is_done=true;
    }
    bool is_done=false;
    float duration=0.0F;
    static const float &DT;
    constexpr static float ACTION_DUR_XFAST=0.1F,ACTION_DUR_FASTER = 0.2F,ACTION_DUR_FAST = 0.25F,ACTION_DUR_MED = 0.5F,ACTION_DUR_LONG = 1.0F,ACTION_DUR_XLONG = 1.5F;
};   
}