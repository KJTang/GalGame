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
    void clear();
    // load
    void readFromScript();
    void readFromData();
    // save
    bool saveData(std::string datafile);
    
    bool setInt(std::string name, int value);
    int getInt(std::string name);
    
    //unfinished
    bool setFloat(std::string name, float value);
    float getFloat(std::string name);
    
    bool setString(std::string name, std::string value);
    std::string getString(std::string name);
    
    void test();
};

#endif /* DataController_cpp */
