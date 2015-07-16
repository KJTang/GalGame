//
//  VariableController.h
//  Test
//
//  Created by KJTang on 15/7/14.
//
//

#ifndef VariableController_cpp
#define VariableController_cpp

#include <cstdio>
#include <vector>

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

class VariableController
{
private:
    static VariableController* sharedVariableController;
    std::string data;
    int pos;
    
    bool init();
    std::string getString();
    
    std::vector<globalInt> Ints;
    std::vector<globalFloat> Floats;
    std::vector<globalString> Strings;
private:
    VariableController();
public:
    ~VariableController();
    
public:
    static VariableController* getInstance()
    {
        if (!sharedVariableController) {
            sharedVariableController = new VariableController();
            sharedVariableController->init();
        }
        return sharedVariableController;
    }
    
    void readFromScript();
    void readFromData();
    
    bool setInt(std::string name, int value);
    int getInt(std::string name);
    
    //unfinished
    bool setFloat(std::string name, float value);
    float getFloat(std::string name);
    
    bool setString(std::string name, std::string value);
    std::string getString(std::string name);
    
    void test();
};

#endif /* VariableController_cpp */
