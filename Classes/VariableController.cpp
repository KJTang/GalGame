//
//  VariableController.cpp
//  Test
//
//  Created by KJTang on 15/7/14.
//
//

#include "VariableController.h"

VariableController* VariableController::sharedVariableController = NULL;

VariableController::VariableController(){}

VariableController::~VariableController(){}

bool VariableController::init()
{
    
    return true;
}

std::string VariableController::getString()
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

void VariableController::readFromScript()
{
    data = FileUtils::getInstance()->getStringFromFile("global.txt");
    pos = 0;
    
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

void VariableController::readFromData()
{
    log("read variables from game data");
}

bool VariableController::setInt(std::string name, int value)
{
    for (int i = 0; i != Ints.size(); ++i) {
        if (name == Ints[i].name) {
            Ints[i].value = value;
            return true;
        }
    }
    return false;
}

int VariableController::getInt(std::string name)
{
    for (int i = 0; i != Ints.size(); ++i) {
        if (name == Ints[i].name) {
            return Ints[i].value;
        }
    }
    // cannot find
    return -1;
}

void VariableController::test()
{
//    std::string str;
//    str = getString();
//    while (str.size()) {
//        log("test: %s", str.c_str());
//        str = getString();
//    }
    
    log("--ints:");
    for (int i = 0; i != Ints.size(); ++i) {
        log("%s %d", Ints[i].name.c_str(), Ints[i].value);
    }
    log("--floats:");
    for (int i = 0; i != Floats.size(); ++i) {
        log("%s %f", Floats[i].name.c_str(), Floats[i].value);
    }
    log("--strings:");
    for (int i = 0; i != Strings.size(); ++i) {
        log("%s %s", Strings[i].name.c_str(), Strings[i].value.c_str());
    }
}