
//
//  DataController.cpp
//  Test
//
//  Created by KJTang on 15/7/20.
//
//

#include "DataController.h"

DataController* DataController::sharedDataController = NULL;

DataController::DataController(){}

DataController::~DataController(){}

bool DataController::init()
{
    
    return true;
}

std::string DataController::getString()
{
    std::string str;
    while (true) {
        // reach the end of file
        if (pos == data.size()) {
            return "";
        }
        // shift blank
        if (data[pos] == ' ' || data[pos] == '=' || data[pos] == ';' || data[pos] == '\n') {
            ++pos;
            continue;
        }
        // shift text
        if (data[pos] == '/') {
            if (data[pos+1] == '/') {
                while (true) {
                    if (pos == data.size()) {
                        return "";
                    }
                    if (data[pos] == '\n') {
                        break;
                    }
                    ++pos;
                }
                continue;
            }
        }
        // get string
        if (isalpha(data[pos]) || isnumber(data[pos])) {
            while (true) {
                if (pos == data.size()) {
                    return str;
                }
                if (isalpha(data[pos]) || isnumber(data[pos])) {
                    str += data[pos];
                    ++pos;
                } else {
                    return str;
                }
            }
        }
        // get string between " "
        if (data[pos] == '\"') {
            ++pos;
            while (true) {
                if (pos == data.size()) {
                    return "";
                }
                if (data[pos] != '\"') {
                    str += data[pos];
                    ++pos;
                } else {
                    ++pos;
                    return str;
                }
            }
        }
        // cannot resolve
        log("something wrong in \"global.txt\"");
        return "";
    }
}

void DataController::clear()
{
    pos = 0;
    Ints.clear();
    Floats.clear();
    Strings.clear();
}

void DataController::readFromScript()
{
    clear();
    
    data = FileUtils::getInstance()->getStringFromFile("global.txt");
    // create variables
    std::string str = getString();
    while (str.size()) {
        if (str == "int") {
            std::string str = getString();
            globalInt var;
            var.name = str;
            var.value = 0;
            Ints.push_back(var);
        }
        else if (str == "float") {
            std::string str = getString();
            globalFloat var;
            var.name = str;
            var.value = 0.0;
            Floats.push_back(var);
        }
        else if (str == "string") {
            std::string str = getString();
            globalString var;
            var.name = str;
            Strings.push_back(var);
        }
        else {
            log("something wrong in \"global.txt\"");
            break;
        }
        str = getString();
    }
}

void DataController::readFromData()
{
    log("read variables from game data");
}

bool DataController::saveData(std::string datafile)
{
    std::string path = FileUtils::getInstance()->getWritablePath()+datafile;
    log("filepath = %s", path.c_str());

//    if (FileUtils::getInstance()->isFileExist(path)) {
//        return false;
//    }
    log("saving------------------------");
    
    using namespace std;
    std::ofstream fout(path.c_str());
    
    GameScene::getInstance()->saveData();
    
    fout<<"pos "<<GameScene::getInstance()->UserData.pos<<endl;
    fout<<"lineID "<<GameScene::getInstance()->UserData.lineID<<endl;
    
    if (GameScene::getInstance()->UserData.bgmFilename.size()) {
        log("bgm filename = %s", GameScene::getInstance()->UserData.bgmFilename.c_str());
        fout<<"bgm filename "<<GameScene::getInstance()->UserData.bgmFilename<<endl;
    }
    if (GameScene::getInstance()->UserData.bgpFilename.size()) {
        fout<<"bgp filename "<<GameScene::getInstance()->UserData.bgpFilename<<endl;
        fout<<"bgp scale "<<GameScene::getInstance()->UserData.bgpScale<<endl;
        fout<<"bgp positionx "<<GameScene::getInstance()->UserData.bgpPositionX<<endl;
        fout<<"bgp positiony "<<GameScene::getInstance()->UserData.bgpPositionY<<endl;
    }
    if (GameScene::getInstance()->UserData.textContent.size()) {
        fout<<"text content "<<GameScene::getInstance()->UserData.textContent<<endl;
    }
    for (int i = 0; i != 4; ++i) {
        if (GameScene::getInstance()->UserData.characterFilename[i].size()) {
            fout<<"character "<<i<<" filename "<<GameScene::getInstance()->UserData.characterFilename[i]<<endl;
            fout<<"character "<<i<<" scale "<<GameScene::getInstance()->UserData.characterScale[i]<<endl;
            fout<<"character "<<i<<" positionx "<<GameScene::getInstance()->UserData.characterPositionX[i]<<endl;
            fout<<"character "<<i<<" positiony "<<GameScene::getInstance()->UserData.characterPositionY[i]<<endl;
        }
    }
    
    return true;
}

bool DataController::setInt(std::string name, int value)
{
    for (int i = 0; i != Ints.size(); ++i) {
        if (name == Ints[i].name) {
            Ints[i].value = value;
            return true;
        }
    }
    return false;
}

int DataController::getInt(std::string name)
{
    for (int i = 0; i != Ints.size(); ++i) {
        if (name == Ints[i].name) {
            return Ints[i].value;
        }
    }
    // cannot find
    return -1;
}

void DataController::test()
{
//    log("--ints:");
//    for (int i = 0; i != Ints.size(); ++i) {
//        log("%s %d", Ints[i].name.c_str(), Ints[i].value);
//    }
//    log("--floats:");
//    for (int i = 0; i != Floats.size(); ++i) {
//        log("%s %f", Floats[i].name.c_str(), Floats[i].value);
//    }
//    log("--strings:");
//    for (int i = 0; i != Strings.size(); ++i) {
//        log("%s %s", Strings[i].name.c_str(), Strings[i].value.c_str());
//    }
    
    log("test------------------------");
    std::string path = FileUtils::getInstance()->getWritablePath()+"test";
    std::ifstream fin(path.c_str());
    
    std::string str;
    getline(fin, str);
    while (str.size()) {
        log("test---------- %s", str.c_str());
        getline(fin, str);
    }
}