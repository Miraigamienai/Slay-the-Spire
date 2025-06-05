#include "Game_object/map/Map_generator.hpp"
#include "Game_object/map/Map_node.hpp"
#include "Game_object/map/Map_edge.hpp"
#include "RUtil/Random.hpp"

#include "Util/Logger.hpp"

namespace Map{
enum class NodePos{
    Current,
    Next
};

class GenHelper{
public:
    GenHelper(size_t h, size_t w)
        :h(static_cast<int>(h)), w(static_cast<int>(w)),
        map(h, decltype(map)::value_type{w, nullptr}){}
    auto &GetMap(){return map;}
    void GenNewNowNode(){if(map[now_y][now_x]==nullptr) map[now_y][now_x]=std::make_shared<Map::Map_node>(now_x,now_y);}
    void GenNewNextNode(){if(map[now_y+1][next_x]==nullptr) map[now_y+1][next_x]=std::make_shared<Map::Map_node>(next_x,now_y+1);}
    auto GetNode(NodePos p, Direction d){return map[now_y+MY(p)][now_x+MX(d)];}
    auto GetNode(NodePos p, Direction d)const{return map[now_y+MY(p)][now_x+MX(d)];}
    bool HasNode(NodePos p, Direction d)const noexcept{return map[now_y+MY(p)][now_x+MX(d)]!=nullptr;}
    void GenEdge(){
        auto dir=GetDir(next_x-now_x);
        if(!map[now_y][now_x]->HasEdge(dir)) map[now_y][now_x]->add_edge(dir, NewEdge(map[now_y][now_x], map[now_y+1][next_x]));
    }
    void GenBossEdge(){
        if(!map[now_y][now_x]->IsToBoss()){
            map[now_y][now_x]->SetToBoss();
            map[now_y][now_x]->add_edge(Direction::middle, std::make_shared<Map_edge>(map[now_y][now_x]->x, map[now_y][now_x]->y, 3, now_y+2, map[now_y][now_x]->GetOffsetX(), map[now_y][now_x]->GetOffsetY(), 0.0F, 0.0F, true));
        }
    }
    void SetStartX(int v)noexcept{now_x=v;now_y=0;}
    void GenNextX(RUtil::Random &rng){next_x = now_x + rng.NextInt((IsLeftRestricted() ? 0 : -1), (IsRightRestricted() ? 0 : 1)+1);}
    bool Finished()const noexcept{return now_y+1 >= h;}
    void AddLayer()noexcept{++now_y;now_x=next_x;}
    const int h, w;
private:
    Map_generator::MapType map;
    int now_x, now_y;
    int next_x;

    bool IsLeftRestricted()const noexcept{return now_x==0 || (HasNode(NodePos::Current, Direction::left) && GetNode(NodePos::Current, Direction::left)->HasEdge(Direction::right));}
    bool IsRightRestricted()const noexcept{return now_x==w-1 || (HasNode(NodePos::Current, Direction::right) && GetNode(NodePos::Current, Direction::right)->HasEdge(Direction::left));}
    static std::shared_ptr<Map_edge> NewEdge(const std::shared_ptr<Map_node>&from, const std::shared_ptr<Map_node>&to){return std::make_shared<Map_edge>(from->x, from->y, to->x, to->y, from->GetOffsetX(), from->GetOffsetY(), to->GetOffsetX(), to->GetOffsetY(), false);}
    static constexpr int MY(NodePos p)noexcept{return p==NodePos::Current ? 0 : 1;}
    static constexpr int MX(Direction d)noexcept{return d==Direction::middle ? 0 : (d==Direction::left ? -1 : 1);}
    static constexpr Direction GetDir(int x)noexcept{return x==0 ? Direction::middle : (x==-1 ? Direction::left : Direction::right);}
};

Map_generator::MapType Map_generator::Get_Map(size_t height,size_t width,int density, RUtil::Random &rng){
    GenHelper G{height, width};

    int first_node=-1;
    for(int i=0;i<density;i++){//try create density times
        int start_node=rng.NextInt(width);
        if(i==0)first_node=start_node;//set first node
        while(start_node==first_node&&i==1) start_node=rng.NextInt(width);//make sure path at least two
        
        G.SetStartX(start_node);
        G.GenNewNowNode();
        while(!G.Finished()){
            G.GenNextX(rng);
            G.GenNewNextNode();
            G.GenEdge();
            G.AddLayer();
        }
        G.GenBossEdge();
    }
    
    return G.GetMap();
}
}