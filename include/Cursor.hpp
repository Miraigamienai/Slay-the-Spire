#pragma once

//fwd decl
namespace Draw{
    class ReTexture;
    class Draw_2D;
}

class Cursor{
public:
    Cursor()=delete;~Cursor()=delete;Cursor(const Cursor &) = delete;Cursor(Cursor &&) = delete;Cursor &operator=(const Cursor &) = delete;Cursor &operator=(Cursor &&) = delete;
    
    static const std::shared_ptr<Draw::ReTexture> &GetTexture(){return Texture;}
    
    // int GetWidth()const{return width;}
    // int GetHeight()const{return height;}
    static void Draw(const std::shared_ptr<Draw::Draw_2D> &Draw2D);
    static void SetVisible(bool is_visible);
private:
    static const int&input_x,&input_y;
    static const std::shared_ptr<Draw::ReTexture> &Texture;
    // const int width=50,height=50;
    static bool is_visible;
};
