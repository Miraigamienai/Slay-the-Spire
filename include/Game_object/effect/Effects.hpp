#pragma once

#include <memory>
#include <SDL_stdinc.h>

//fwd decl;
namespace Draw{
    class Draw_2D;
}

namespace Effect{
class Effects
{
public:
    virtual ~Effects()=default;
    virtual void render(const std::shared_ptr<Draw::Draw_2D> &r2)const=0;
    virtual void update()=0;
    bool IsDone()const noexcept{return is_done;}
    void TimeGo()noexcept{
        duration-=DT;
        if(duration<0.0F)is_done=true;
    }
    void QuickDisappear(float x){duration/=x;}
protected:
    bool is_done=false;
    Uint32 color=0xffffffff;
    float duration=0.0F,scale=0.0F,color_a=1.0F;
    static const float &DT;
};
} // namespace Effect
