//
//  DataController.hpp
//  Test
//
//  Created by KJTang on 15/7/20.
//
//

#ifndef DataController_cpp
#define DataController_cpp

#include <cstdio>
#include <vector>
#include <fstream>
#include <string>

#include "cocos2d.h"
#include "GameScene.h"

using namespace::cocos2d;

struct globalInt
{
    std::string name;
    int value;
};

struct globalFloat
{
    std::string name;
    float value;
};

struct globalString
{
    std::string name;
    std::string value;
};

class DataController
{
private:
    static DataController* sharedDataController;
    std::string data;
    int pos;
    
    std::string getString();
    
    std::vector<globalInt> Ints;
    std::vector<globalFloat> Floats;
    std::vector<globalString> Strings;
    void clear();
public:
    int dataCount;
//    std::vector<std::string> dataName;
    struct dataInfo{
        std::string dataName;
        std::string chapterName;
    };
    std::vector<dataInfo> dataInfoList;
private:
    DataController();
public:
    ~DataController();
    
public:
    bool init();
    static DataController* getInstance()
    {
        if (!sharedDataController) {
            sharedDataController = new DataController();
            sharedDataController->init();
        }
        return sharedDataController;
    }
    void updateDataInfo();
    // load
    void readFromScript();
    void readFromData(const std::string &datafile);
    // save
    bool saveData(const std::string &datafile);
    // delete
    bool deleteData(const std::string &datafile);
    
    bool setInt(const std::string &name, int value);
    int getInt(const std::string &name);
    
    void test(const std::string &filename);
};

#endif /* DataController_cpp */
