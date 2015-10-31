//
//  DataController.cpp
//  Test
//
//  Created by KJTang on 15/7/20.
//
//

#include "DataController.h"
#include "PromptBoxSprite.h"

#include <iostream>

DataController* DataController::sharedDataController = NULL;

DataController::DataController(){}

DataController::~DataController(){}

bool DataController::init()
{
    dataCount = 0;
    std::string path = FileUtils::getInstance()->getWritablePath()+"DataInfo";
    
    if(!FileUtils::getInstance()->isFileExist(path))
    {
        std::ofstream fout(path);
        fout<<0<<std::endl;
        fout.close();
    } else {
        std::ifstream fin(path);
        fin>>dataCount;
        for (int i = 0; i != dataCount; ++i) {
            dataInfo temp;
            fin>>temp.dataName;
            fin>>temp.chapterName;
            dataInfoList.push_back(temp);
        }
        fin.close();
    }
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

void DataController::updateDataInfo()
{
    std::string path = FileUtils::getInstance()->getWritablePath()+"DataInfo";
    std::ofstream fout(path);
    dataCount = static_cast<int>(dataInfoList.size());
    fout<<dataCount<<std::endl;
    for (int i = 0; i != dataCount; ++i) {
        fout<<dataInfoList[i].dataName<<" "<<dataInfoList[i].chapterName<<std::endl;
    }
    fout.close();
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
            var.value = -1;
            Ints.push_back(var);
        }
        else if (str == "float") {
            std::string str = getString();
            globalFloat var;
            var.name = str;
            var.value = -1.0;
            Floats.push_back(var);
        }
        else if (str == "string") {
            std::string str = getString();
            globalString var;
            var.name = str;
            var.value = "default";
            Strings.push_back(var);
        }
        else {
            log("something wrong in \"global.txt\"");
            break;
        }
        str = getString();
    }
}

void DataController::readFromData(const std::string &datafile)
{
    std::string path = FileUtils::getInstance()->getWritablePath()+datafile;
    
    CCASSERT(FileUtils::getInstance()->isFileExist(path), "datafile is not exist!!");
    
    std::ifstream fin(path);
    
    std::string str;
    
    Ints.clear(), Floats.clear(), Strings.clear();
    
    while (fin>>str) {
        if (str == "int") {
            globalInt var;
            fin>>var.name;
            fin>>var.value;
            Ints.push_back(var);
        } else if (str == "float") {
            globalFloat var;
            fin>>var.name;
            fin>>var.value;
            Floats.push_back(var);
        } else if (str == "string") {
            globalString var;
            fin>>var.name;
            fin>>var.value;
            Strings.push_back(var);
        } else {
            
        }
    }
    log("variables loaded!");
    
    fin.close();
}

bool DataController::saveData(const std::string &datafile)
{
    std::string path = FileUtils::getInstance()->getWritablePath()+datafile;
    
    using namespace std;
    std::ofstream fout(path.c_str());
    
    // save flags to GameScene::UserData
    GameScene::getInstance()->saveFlags();
    // flags
    fout<<"scriptpath "<<GameScene::getInstance()->UserData.scriptPath<<endl;
    fout<<"pos "<<GameScene::getInstance()->UserData.pos<<endl;
    fout<<"lineID "<<GameScene::getInstance()->UserData.lineID<<endl;
    fout<<"gobackPos "<<GameScene::getInstance()->UserData.gobackPos<<endl;
    fout<<"gobackLineID "<<GameScene::getInstance()->UserData.gobackLineID<<endl;
    fout<<"condition "<<GameScene::getInstance()->UserData.isConditionFullFilled<<endl;
    fout<<"choicetablePos "<<GameScene::getInstance()->UserData.choiceTablePos<<endl;
    fout<<"choicetableLine "<<GameScene::getInstance()->UserData.choiceTableLineID<<endl;
    // scene
    if (GameScene::getInstance()->UserData.bgmFilename.size()) {
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
        fout<<"text pos "<<GameScene::getInstance()->UserData.textPos<<endl;
        fout<<"text lineid "<<GameScene::getInstance()->UserData.textLineID<<endl;
    }
    for (int i = 0; i != 4; ++i) {
        if (GameScene::getInstance()->UserData.characterFilename[i].size()) {
            fout<<"character "<<i<<" filename "<<GameScene::getInstance()->UserData.characterFilename[i]<<endl;
            fout<<"character "<<i<<" scale "<<GameScene::getInstance()->UserData.characterScale[i]<<endl;
            fout<<"character "<<i<<" positionx "<<GameScene::getInstance()->UserData.characterPositionX[i]<<endl;
            fout<<"character "<<i<<" positiony "<<GameScene::getInstance()->UserData.characterPositionY[i]<<endl;
        }
    }
    
    // save the variables
    for (int i = 0; i != Ints.size(); ++i) {
        fout<<"int "<<Ints[i].name<<" "<<Ints[i].value<<endl;
    }
    for (int i = 0; i != Floats.size(); ++i) {
        fout<<"float "<<Floats[i].name<<" "<<Floats[i].value<<endl;
    }
    for (int i = 0; i != Strings.size(); ++i) {
        fout<<"string "<<Strings[i].name<<" "<<Strings[i].value<<endl;
    }
    
    fout.close();
    
    // save screen shot
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //定义一个屏幕大小的渲染纹理
    RenderTexture* pScreen = RenderTexture::create(visibleSize.width, visibleSize.height, Texture2D::PixelFormat::RGBA8888);
    //获得当前的场景指针
    Scene* pCurScene = Director::getInstance()->getRunningScene();
    //渲染纹理开始捕捉
    pScreen->begin();
    //当前场景参与绘制
    pCurScene->visit();
    //结束捕捉
    pScreen->end();
    
    //保存为png
    pScreen->saveToFile(datafile+".png", Image::Format::PNG, true, [&](RenderTexture*, const std::string&) {
        // when saved, create a PromptBox
        auto prompt = PromptBoxSprite::create();
        Director::getInstance()->getRunningScene()->addChild(prompt, 20);
        auto visibleSize = Director::getInstance()->getVisibleSize();
        prompt->setPosition(-prompt->getContentSize().width/2, visibleSize.height*0.8);
        prompt->setText("Data Saved");
        prompt->start();
    });

    // update
    bool found = false;
    for (int i = 0; i != dataInfoList.size(); ++i) {
        if (dataInfoList[i].dataName == datafile) {
            found = true;
            break;
        }
    }
    if (!found) {
        dataInfo temp;
        temp.dataName = datafile;
        temp.chapterName = GameScene::getInstance()->UserData.scriptPath;
        dataInfoList.push_back(temp);
    }
    updateDataInfo();

    // TEST
    DataController::getInstance()->test(datafile);

    return true;
}

bool DataController::deleteData(const std::string &datafile)
{
    std::string path = FileUtils::getInstance()->getWritablePath()+datafile;
    
    if (!FileUtils::getInstance()->isFileExist(path)) {
        return false;
    }
    for (int i = 0; i != dataInfoList.size(); ++i) {
        if (dataInfoList[i].dataName == datafile) {
            dataInfoList.erase(dataInfoList.begin() + i);
            --dataCount;
            break;
        }
    }
    FileUtils::getInstance()->removeFile(path);
    FileUtils::getInstance()->removeFile(path+".png");
    CCASSERT(!(FileUtils::getInstance()->isFileExist(path)||FileUtils::getInstance()->isFileExist(path+".png")), "Data should be delete!!");
    updateDataInfo();
    return true;
}

bool DataController::setInt(const std::string &name, int value)
{
    for (int i = 0; i != Ints.size(); ++i) {
        if (name == Ints[i].name) {
            Ints[i].value = value;
            return true;
        }
    }
    return false;
}

int DataController::getInt(const std::string &name)
{
    for (int i = 0; i != Ints.size(); ++i) {
        if (name == Ints[i].name) {
            return Ints[i].value;
        }
    }
    // cannot find
    return -2;
}

void DataController::test(const std::string &filename)
{
    log("test------------------------");
    std::string path = FileUtils::getInstance()->getWritablePath()+filename;
    log("%s", path.c_str());
    std::ifstream fin(path.c_str());
    
    std::string str;
    getline(fin, str);
    while (str.size()) {
        log("test---------- %s", str.c_str());
        getline(fin, str);
    }
    log("test------------------------");
    
    fin.close();
}