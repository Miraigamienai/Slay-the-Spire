#pragma once

#include <SDL_stdinc.h>//Uint
#include <glm/glm.hpp>//glm::degress
#include <glm/gtc/constants.hpp>//two pi
#include <vector>
#include <string>
#include <algorithm>//std::clamp

//if template not good for using,
//it will change to float.
namespace RUtil{
class Math{
public:
    Math() = delete;
    Math(const Math &) = delete;
    Math(Math &&) = delete;
    ~Math() = delete;
    Math &operator=(const Math &) = delete;
    Math &operator=(Math&&)=delete;
    template <typename... Args>
    static void Normalize(Args&... args){
        const auto Sum=(args+...);
        ((args/=static_cast<float>(Sum)),...);
    }
    template <typename T>
    static constexpr T Apply(const T start,const T target,const float t)noexcept(noexcept(start+(target-start)*t)){return start+(target-start)*t;}
    static float interpolation_exp(float v, float p, float a);
    static float interpolation_expin(float v, float p, float a){
        //v^p(a-1)  ->  [v^-p, 1]     //(v^p(a-1) - v^-p) / (1 - v^-p)  ->  [0,1]
        const float m=(float)std::pow((double)v,(double)(-p));
        return ((float)std::pow((double)v,(double)(p*(a-1.0F)))-m)/(1.0F-m);
    }
    static float interpolation_expout(float v, float p, float a){
        //v^(-a*p)  ->  [v^-p, 1]     //(v^(-a*p) - v^-p) / (1 - v^-p)  ->  [0,1]
        const float m=(float)std::pow((double)v,(double)(-p));
        return 1.0F - ((float)std::pow((double)v,(double)(-a*p))-m)/(1.0F-m);
    }
    static float interpolation_powout(int p, float a);
    static float fadelerp(float start,float target);
    static float scrolllerp(float start,float target);
    static float varlerp(float start,const float target,const float speed,const float threshold);
    static Uint32 color_lerp_rgb(Uint32 start,Uint32 target,float t);
    static float interpolation_exp10(float start,float target,float a);
    static float interpolation_exp10in(float start,float target,float a){return Apply(start,target,interpolation_expin(2.0F,10.0F,a));}
    static float interpolation_exp10out(float start,float target,float a){return Apply(start,target,interpolation_expout(2.0F,10.0F,a));}
    static float interpolation_exp5in(float start,float target,float a){return Apply(start,target,interpolation_expin(2.0F,5.0F,a));}
    static float interpolation_exp5out(float start,float target,float a){return Apply(start,target,interpolation_expout(2.0F,5.0F,a));}
    template <typename T>
    static constexpr T interpolation_fade(T start,T target,float a){
        //from gdx
        return Apply(start,target,std::clamp(a * a * a * (a * (a * 6.0F - 15.0F) + 10.0F),0.0F,1.0F));
    }
    template <typename T>
    static constexpr T interpolation_swing(T start,T target,float a)noexcept(noexcept(Apply<T>(start, target, 0.0F))){
        //from gdx
        if(a<=0.5F){
            a*=2.0F;
            return Apply(start, target, a * a * (2.5F * a + 1.5F)/2.0F);
        }
        --a;
        return Apply(start, target, a * a * (2.5F * a + 1.5F)/2.0F + 1.0F);
    }
    template <typename T>
    static constexpr T interpolation_swing_out(T start,T target,float a)noexcept(noexcept(Apply<T>(start, target, 0.0F))){
        //from gdx
        --a;
        return Apply(start, target, a * a * (3.0F * a + 2.0F) + 1.0F);
    }
    static float interpolation_powout2(float start,float target,float a);
    static constexpr float interpolation_elastic_out(float a){
        return 1.0F-std::pow(2.0F,-10.0F*a)*std::sin(glm::two_pi<float>()*a*-10.0F);
    }
    static int StrToInt(const std::string &str);
    static float GetRadian(const glm::vec2 &v){return atan2f(v.y,v.x);}
    static constexpr float GetDegress(const glm::vec2 &v){return glm::degrees(atan2f(v.y,v.x));}
    static float BounceOut(float t);
    static float BounceIn(float t);
    static glm::vec2 BezierQuadratic(const glm::vec2 p0,const glm::vec2 p1,const glm::vec2 p2,const float t);
    static glm::vec2 CatmullRomSpline(const std::vector<glm::vec2> &controls,float t,const int len,const int vec_start_pos=0);
    static constexpr int GetIntLength(const int x)noexcept{
        return x<100000?(x<100?(x<10?1:2):(x<1000?3:4)):(x<10000000?(x<1000000?6:7):(x<100000000?8:(x<1000000000?9:10)));
        //        5               [12]        [34]                       [67]                    [8 9 10]
    };
    static constexpr Uint32 GetColorUint32_RGB(int r,int g,int b)noexcept{return r<<24|g<<16|b<<8;};
    static constexpr Uint32 GetColorUint32_RGB(float r,float g,float b)noexcept{return static_cast<Uint32>(r*255.0F)<<24|static_cast<Uint32>(g*255.0F)<<16|static_cast<Uint32>(b*255.0F)<<8;}
    static constexpr float color_norm(Uint32 x)noexcept{return static_cast<float>(x)/255.0F;}
    static constexpr glm::vec3 TO_VEC3(Uint32 color){
        return glm::vec3{
            color_norm((color&0xff000000)>>24),
            color_norm((color&0x00ff0000)>>16),
            color_norm((color&0x0000ff00)>>8)
        };
    }
    //only work if value not bigger or smaller than 2*len
    static constexpr int SimpleRangeChange(const int value,const int len)noexcept{return len<=value?value-len:(value<0?value+len:value);}
};
}