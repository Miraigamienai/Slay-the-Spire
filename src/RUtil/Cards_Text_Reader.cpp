#include <fstream>
#include <string>
#include <map>

#include "RUtil/Cards_Text_Reader.hpp"
#include "RUtil/Text_layout_creator.hpp"
#include "RUtil/File_Pos_Getter.hpp"
#include "Draw/Text_layout.hpp"

#include "Util/Logger.hpp"

namespace RUtil{
    template <typename T>
    using BaseType = std::array<T, static_cast<size_t>(Cards_Text_ID::SIZE)>;
    
    struct _CardInfo{
        std::string name, desc, upgrade_desc;
        explicit operator CardInfo()const{
            auto temp = CardInfo{
                Text_layout_creator::GetLayout(name),
                Text_layout_creator::GetLayout(desc),
                Text_layout_creator::GetLayout(upgrade_desc)
            };
            temp.name->ChangeFontWeight(FontWeight::bold);
            return temp;
        }   
    };

    static inline std::string GetMainString(const std::string &str){
        auto sub_str=str.substr(str.find(":"));
        const auto l_pos=sub_str.find('"'),
                   r_pos=sub_str.rfind('"');
        if(l_pos>=r_pos) LOG_ERROR("TEXT contain:'{}' WRONG : '{}'", str, Cards_Text_Reader::FILENAME);
        return sub_str.substr(l_pos+1,r_pos-l_pos-1);
    }

    static void GetJsonFileText(const std::string &path, std::map<int, std::vector<std::string>>& the_map){
        std::ifstream inputFile(path);
        if(!inputFile){
            LOG_ERROR("The ERROR happends when loading path:{} Vector strings.",path);
            return;
        }

        std::string line;
        int idx=0;
        bool vec_start=false;
        while(std::getline(inputFile,line)){
            if(line == "  },"){
                ++idx;
            }else if(line.find("\"EXTENDED_DESCRIPTION\"") != std::string::npos){
                vec_start=true;
            }else if(line == "    ]"){
                vec_start=false;
            }else if(vec_start){
                const auto l_pos=line.find('"'),
                           r_pos=line.rfind('"');
                if(l_pos>=r_pos) LOG_ERROR("TEXT contain:'{}' WRONG in path:{}",line,path);    
                the_map[idx].emplace_back(line.substr(l_pos+1,r_pos-l_pos-1));
            }
        }
    }

    static BaseType<_CardInfo> GetJsonFileText(const std::string &path){
        std::ifstream inputFile(path);
        if(!inputFile){
            LOG_ERROR("The ERROR happends when loading path:{} Vector strings.",path);
            return {};
        }
        BaseType<_CardInfo> temp;

        std::string line;
        std::size_t idx=0;
        while(std::getline(inputFile,line)){
            if(line == "  },"){
                ++idx;
            }else if(line.find("\"NAME\"") != std::string::npos){
                temp[idx].name=GetMainString(line);
            }else if(line.find("\"DESCRIPTION\"") != std::string::npos){
                temp[idx].desc=GetMainString(line);
            }else if(line.find("\"UPGRADE_DESCRIPTION\"") != std::string::npos){
                temp[idx].upgrade_desc=GetMainString(line);
            }
        }
        inputFile.close();
        return temp;
    }

    const std::vector<std::shared_ptr<Draw::Text_layout>> &Cards_Text_Reader::GetExtended(Cards_Text_ID id){
        static std::map<int, std::pair<bool, std::vector<std::string>>> STR_BOX=[](){
            std::map<int, std::vector<std::string>> temp;
            GetJsonFileText(File_Pos_Getter::GetLanguageJsonPos()+FILENAME, temp);
            std::map<int, std::pair<bool, std::vector<std::string>>> result;
            for(const auto &[key, value]:temp){
                result[key]={false, value};
            }
            return result;
        }();
        static std::map<int, std::vector<std::shared_ptr<Draw::Text_layout>>> BOX;
        auto it=STR_BOX.find(static_cast<int>(id));
        if(it!=STR_BOX.end()){
            if(!it->second.first){
                it->second.first=true;
                for(const auto&text:it->second.second)
                    BOX[static_cast<int>(id)].emplace_back(Text_layout_creator::GetLayout(text));
            }
            return BOX[static_cast<int>(id)];
        }
        LOG_ERROR("Try to find the Extended that doesn't exist.");
        return BOX[0];
    }

    const CardInfo &Cards_Text_Reader::GetInfo(Cards_Text_ID id){
        static const auto STR_BOX=GetJsonFileText(File_Pos_Getter::GetLanguageJsonPos()+FILENAME);
        static BaseType<CardInfo> BOX{};
        static BaseType<bool> once_arr{};
        if(!once_arr[static_cast<int>(id)]){
            once_arr[static_cast<int>(id)]=true;
            BOX[static_cast<int>(id)] = static_cast<CardInfo>(STR_BOX[static_cast<int>(id)]);
        }
        return BOX[static_cast<int>(id)];
    }
}