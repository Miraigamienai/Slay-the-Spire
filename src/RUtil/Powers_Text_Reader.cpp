#include <fstream>
#include <algorithm>

#include "RUtil/Powers_Text_Reader.hpp"
#include "RUtil/Text_layout_creator.hpp"
#include "RUtil/File_Pos_Getter.hpp"
#include "Draw/Text_layout.hpp"

#include "Util/Logger.hpp"

namespace RUtil
{
    template <typename T>
    using BaseType = std::array<T, static_cast<size_t>(Powers_Text_ID::SIZE)>;

    template <typename T>
    using DescriptionType = BaseType<std::array<T, 2>>;

    static void GetJsonFileText(const std::string &path, DescriptionType<std::string> &arr){
        std::ifstream inputFile(path);
        if(!inputFile){
            LOG_ERROR("The ERROR happends when loading path:{} Vector strings.",path);
            return;
        }

        std::string line;
        bool desc_started=false;
        std::size_t idx1=0, idx2=0;
        while(std::getline(inputFile,line)){
            if(line.find("\"DESCRIPTIONS\"") != std::string::npos){
                desc_started=true;
            }else if(desc_started){
                if(std::all_of(line.begin(), line.end(), [](char c){return c==' '||c==']';})){
                    desc_started=false;
                    ++idx1;
                    idx2=0;
                }else if(idx2<2){
                    const auto l_pos=line.find('"');
                    const auto r_pos=line.rfind('"');
                    if(l_pos>=r_pos) LOG_ERROR("TEXT contain:'{}' WRONG in path:{}",line,path);
                    arr[idx1][idx2++]=line.substr(l_pos+1,r_pos-l_pos-1);
                }
            }
        }
        inputFile.close();
    }

    static BaseType<std::string> GetJsonFileText(const std::string &path){
        std::ifstream inputFile(path);
        if(!inputFile){
            LOG_ERROR("The ERROR happends when loading path:{} Vector strings.",path);
            return {};
        }
        BaseType<std::string> temp;

        std::string line;
        std::size_t idx=0;
        while(std::getline(inputFile,line)){
            if(line.find("\"NAME\"") != std::string::npos){
                std::string sub_str=line.substr(line.find(":"));
                const auto l_pos=sub_str.find('"');
                const auto r_pos=sub_str.rfind('"');
                if(l_pos>=r_pos) LOG_ERROR("TEXT contain:'{}' WRONG in path:{}",line,path);    
                temp[idx++]=sub_str.substr(l_pos+1,r_pos-l_pos-1);
            }
        }
        inputFile.close();
        return temp;
    }

    const std::array<std::shared_ptr<Draw::Text_layout>, 2> &Powers_Text_Reader::GetDescriptions(const Powers_Text_ID id){
        static const DescriptionType<std::string> STR_BOX=[](){
            DescriptionType<std::string> temp;
            GetJsonFileText(File_Pos_Getter::GetLanguageJsonPos()+FILENAME, temp);
            return temp;
        }();
        static DescriptionType<std::shared_ptr<Draw::Text_layout>> BOX{};
        static BaseType<bool> once_arr{};
        if(!once_arr[static_cast<int>(id)]){
            once_arr[static_cast<int>(id)]=true;
            for(int i=0;i<2;i++)
                BOX[static_cast<int>(id)][i] = Text_layout_creator::GetLayout(STR_BOX[static_cast<int>(id)][i]);
        }
        return BOX[static_cast<int>(id)];
    }

    const std::shared_ptr<Draw::Text_layout> &Powers_Text_Reader::GetName(const Powers_Text_ID id){
        static const BaseType<std::string> STR_BOX=GetJsonFileText(File_Pos_Getter::GetLanguageJsonPos()+FILENAME);
        static BaseType<std::shared_ptr<Draw::Text_layout>> BOX{};
        static BaseType<bool> once_arr{};
        if(!once_arr[static_cast<int>(id)]){
            once_arr[static_cast<int>(id)]=true;
            BOX[static_cast<int>(id)] = Text_layout_creator::GetLayout(STR_BOX[static_cast<int>(id)]);
        }
        return BOX[static_cast<int>(id)];
    }
} // namespace RUtil
