#include <fstream>
#include <array>

#include "RUtil/Text_Vector_Reader.hpp"
#include "RUtil/Text_layout_creator.hpp"
#include "RUtil/File_Pos_Getter.hpp"
#include "Draw/Text_layout.hpp"

#include "Util/Logger.hpp"

namespace RUtil{
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
            GetJsonFileText(File_Pos_Getter::GetLanguageJsonPos()+FILENAME,temp);
            return temp;
        }();
        static std::array<std::vector<std::shared_ptr<Draw::Text_layout>>, static_cast<size_t>(Text_ID::SIZE)> BOX{};
        if(BOX[static_cast<int>(id)].empty()){
            for(const auto &it:STR_BOX[static_cast<int>(id)])
                BOX[static_cast<int>(id)].emplace_back(Text_layout_creator::GetLayout(it));
        }
        return BOX[static_cast<int>(id)];
    }
}