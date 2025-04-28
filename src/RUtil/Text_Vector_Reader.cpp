#include<fstream>

#include "RUtil/Text_Vector_Reader.hpp"
#include "Draw/Text_layout_all.hpp"
#include "Draw/Text_layout_color.hpp"
#include "Draw/Text_layout_normal.hpp"
#include "WindowSize.hpp"//get language

#include "Util/Logger.hpp"

namespace RUtil{
    enum class FileName{
        ui
    };

    static inline constexpr auto GetJsonFilePos(FileName file_name,Language lang){
        switch (lang){
            case Language::eng:
                switch(file_name){
                    default:return RESOURCE_DIR"/language/" "eng/" "ui.json";
                }
            case Language::jpn:
                switch(file_name){
                    default:return RESOURCE_DIR"/language/" "jpn/" "ui.json";
                }
            default:
                switch(file_name){
                    default:return RESOURCE_DIR"/language/" "zht/" "ui.json";
                }
        }
        
    }

    static inline bool HasOrbCode(const std::string &text)noexcept{
        for(size_t i=0;i+2<text.size();i++)
            if(text[i] == '[' && text[i + 2] == ']')
                return true;
        return false;
    }
    static inline bool HasNumCode(const std::string &text)noexcept{
        for(size_t i=0;i+2<text.size();i++)
            if(text[i] == '!' && text[i + 2] == '!')
                return true;
        return false;
    }
    static std::shared_ptr<Draw::Text_layout> GetLayout(const std::string &text){
        if(HasOrbCode(text)||HasNumCode(text))
            return std::make_shared<Draw::Text_layout_all>(text);
        if(text.find('#')!=std::string::npos)
            return std::make_shared<Draw::Text_layout_color>(text);
        return std::make_shared<Draw::Text_layout_normal>(text);
    }

    static void GetJsonFileText(const std::string &path,std::vector<std::vector<std::string>>&vec){
        std::ifstream inputFile(path);
        if(!inputFile){
            LOG_ERROR("The ERROR happends when loading path:{} Vector strings.",path);
        }else{
            std::string line;
            bool vec_started=false;
            while(std::getline(inputFile,line)){
                const auto l_pos=line.find('"');
                if(10<line.length() && l_pos!=line.npos && line.compare(l_pos,6,"\"TEXT\"")==0){
                    vec_started=true;
                    vec.emplace_back();
                }else if(4<line.length()&&line[4]==']')
                    vec_started=false;
                else if(vec_started){
                    const auto r_pos=line.rfind('"');
                    if(l_pos>=r_pos) LOG_ERROR("TEXT contain:'{}' WRONG in path:{}",line,path);
                    vec.back().emplace_back(line.substr(l_pos+1,r_pos-l_pos-1));
                }
            }
            inputFile.close();
        }
    }

    const std::vector<std::shared_ptr<Draw::Text_layout>> &Text_Vector_Reader::GetTextVector(const Text_ID id){
        static const std::vector<std::vector<std::string>> STR_BOX=[](){
            std::vector<std::vector<std::string>> temp;
            //load ui
            GetJsonFileText(GetJsonFilePos(FileName::ui, Setting::language),temp);
            return temp;
        }();
        static std::vector<std::vector<std::shared_ptr<Draw::Text_layout>>> BOX{STR_BOX.size()};
        if(BOX[static_cast<int>(id)].empty()){
            for(const auto &it:STR_BOX[static_cast<int>(id)])
                BOX[static_cast<int>(id)].emplace_back(it.empty()?nullptr:GetLayout(it));
        }
        return BOX[static_cast<int>(id)];
    }
}