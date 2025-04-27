#include <string.h>

#include "Draw/Text_layout.hpp"

namespace Draw{
void Text_layout::replace(std::string &text,const char* from, const char* to){
    size_t pos=0;
    const size_t from_len=strlen(from);
    const size_t to_len=strlen(to);
    while((pos=text.find(from,pos))!=std::string::npos){
        text.replace(pos,from_len,to);
        pos+=to_len;
    }
}

std::vector<std::string> Text_layout::color_string_split(const std::string &text){
    std::vector<std::string> re;
    if(text.empty()) return re;
    size_t last_pos,pos=0;
    do{
        last_pos=pos;
        pos=text.find('#',pos+1);
        if(text[last_pos]=='#'){
            auto temp=text.substr(last_pos, pos-last_pos);
            size_t space_pos=temp.find(' ');
            if(space_pos!=std::string::npos&&space_pos!=temp.size()-1){
                re.emplace_back(temp.substr(0, space_pos));
                re.emplace_back(temp.substr(space_pos));
            }else{
                re.emplace_back(temp);    
            }
        }else{
            re.emplace_back(text.substr(last_pos, pos-last_pos));
        }
    }while(pos!=std::string::npos);
    return re;
}
}