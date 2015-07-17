//
//  ScriptController.cpp
//  Test
//
//  Created by KJTang on 15/7/13.
//
//

#include "ScriptController.h"

ScriptController* ScriptController::sharedScriptController = NULL;

ScriptController::ScriptController(){}

ScriptController::~ScriptController(){}

bool ScriptController::init()
{
    pos = 0;
    lineID = 1;
    hasErr = false;
    return true;
}

void ScriptController::runWithFile(std::string filename, int linePosition)
{
    lineID = linePosition;
    if (lineID <= 1) {
        lineID = 1;
        pos = 0;
        hasErr = false;
    }
    data = FileUtils::getInstance()->getStringFromFile(filename.c_str());
    //    log("test:\n%s", data.c_str());
    
    stateBegin();
}

std::string ScriptController::getString()
{
    std::string str;
    while (true) {
        // is it the end of script
        if (pos == data.size()) {
            return "";
        }
        // shift the blanks
        if (data[pos] == ' ') {
            ++pos;
            continue;
        }
        if (data[pos] == '\n') {
            ++pos;
            ++lineID;
            continue;
        }
        // shift the text
        if (data[pos] == '/') {
            if (data[pos+1] == '/') {
                while (data[pos] != '\n') {
                    ++pos;
                }
                ++pos;
                ++lineID;
                continue;
            } else {
                showError(UNRECOGNIZED_CHARACTOR);
                return "";
            }
        }
        // get string between " "
        else if (data[pos] == '\"') {
            while (true) {
                ++pos;
                if (pos==data.size() || data[pos]=='\n') {
                    showError(MISSED_ANOTHER_QUATATION_MARK);
                    return "";
                }
                if (data[pos] != '\"') {
                    str += data[pos];
                } else {
                    ++pos;
                    return str;
                }
            }
        }
        // get string beside '.'
        else if (isalpha(data[pos]) || isnumber(data[pos]))
        {
            while (true) {
                if (pos == data.size()) {
                    return str;
                }
                if (isalpha(data[pos]) || isnumber(data[pos])) {
                    str += data[pos];
                    ++pos;
                    continue;
                }
                if (data[pos] == '.' || data[pos] == '=' || data[pos] == '\n') {
                    ++pos;
                    return str;
                } else {
                    showError(INVALID_EXPRESSION);
                    return "";
                }
            }
        }
        else {
            showError(UNRECOGNIZED_CHARACTOR);
            return "";
        }
    }
}

int ScriptController::transStringToInt(std::string num)
{
    int result = 0;
    for (int i = 0; i != num.size(); ++i) {
        result *= 10;
        result += num[i]-'0';
    }
    return result;
}

float ScriptController::transStringToFloat(std::string num)
{
    float result = 0;
    int dot = 0;
    for (int i = 0; i != num.size(); ++i) {
        if (num[i] == '.') {
            dot = 1;
            continue;
        }
        dot *= 10;
        result *= 10;
        result += num[i]-'0';
    }
    return dot?result/dot:result;
}

void ScriptController::stateBegin()
{
    while (!GameScene::getInstance()->isMissionCompleted) {
        // wait
    }
    GameScene::getInstance()->isMissionCompleted = false;
    std::string str = getString();
    log("ready to next command, line %d", lineID);
    if (str.size()) {
        if (str=="set" || str=="get" || str=="if") {
            stateCommand(str);
        } else {
            showError(UNKNOWN_COMMAND);
        }
    }
}

void ScriptController::stateCommand(std::string cmd)
{
    /* **********************
     *          set
     * **********************
     */
    if (cmd == "set") {
        std::string str = getString();
        // setting bgp
        if (str == "bgp") {
            std::string str = getString();
            if (str == "name") {
                std::string str = getString();
                log("set bgp name = %s", str.c_str());
                GameScene::getInstance()->setBgpFilename(str);
            } else if (str == "effect") {
                std::string str = getString();
                log("set bgp effect = %s", str.c_str());
            } else if (str == "scale") {
                std::string str = getString();
                log("set bgp scale = %s", str.c_str());
                GameScene::getInstance()->setBgpScale(transStringToFloat(str));
            } else if (str == "duration") {
                std::string str = getString();
                log("set bgp duration = %s", str.c_str());
                GameScene::getInstance()->setBgpDuration(transStringToFloat(str));
            } else if (str == "position") {
                std::string x = getString();
                std::string y = getString();
                log("set bgp position = %s, %s", x.c_str(), y.c_str());
                GameScene::getInstance()->setBgpPosition(transStringToFloat(x), transStringToFloat(y));
            } else if (str == "start") {
                log("set bgp start");
                GameScene::getInstance()->setBgpStart();
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // setting cg
        else if (str == "cg") {
            std::string str = getString();
            if (str == "name") {
                std::string str = getString();
                log("set cg name = %s", str.c_str());
            } else if (str == "effect") {
                std::string str = getString();
                log("set cg effect = %s", str.c_str());
            } else if (str == "Xscale") {
                std::string str = getString();
                log("set cg xscale = %s", str.c_str());
            } else if (str == "Yscale") {
                std::string str = getString();
                log("set cg yscale = %s", str.c_str());
            } else if (str == "Xposition") {
                std::string str = getString();
                log("set cg xposition = %s", str.c_str());
            } else if (str == "Yposition") {
                std::string str = getString();
                log("set cg yposition = %s", str.c_str());
            } else if (str == "flowable") {
                std::string str = getString();
                log("set cg flowable = %s", str.c_str());
            } else if (str == "start") {
                std::string str = getString();
                log("set cg start = %s", str.c_str());
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // setting text
        else if (str == "text") {
            std::string str = getString();
            if (str == "content") {
                std::string str = getString();
                log("set text content = %s", str.c_str());
                GameScene::getInstance()->setTextContent(str);
            } else if (str == "start") {
                GameScene::getInstance()->setTextShow(transStringToFloat(getString()));
            } else if (str == "clear") {
                GameScene::getInstance()->setTextClear();
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // setting bgm
        else if (str == "bgm") {
            std::string str = getString();
            if (str == "name") {
                std::string str = getString();
                log("set bgm name = %s", str.c_str());
            } else if (str == "start") {
                std::string str = getString();
                log("set bgm start = %s", str.c_str());
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // setting sound effect
        else if (str == "se") {
            std::string str = getString();
            if (str == "name") {
                std::string str = getString();
                log("set se name = %s", str.c_str());
            } else if (str == "start") {
                std::string str = getString();
                log("set se start = %s", str.c_str());
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // setting charactor
        else if (str == "ch01") {
            std::string str = getString();
            if (str == "name") {
                std::string str = getString();
                log("set ch01 name = %s", str.c_str());
            } else if (str == "effect") {
                std::string str = getString();
                log("set ch01 effect = %s", str.c_str());
            } else if (str == "Xscale") {
                std::string str = getString();
                log("set ch01 xscale = %s", str.c_str());
            } else if (str == "Yscale") {
                std::string str = getString();
                log("set ch01 yscale = %s", str.c_str());
            } else if (str == "Xposition") {
                std::string str = getString();
                log("set ch01 xposition = %s", str.c_str());
            } else if (str == "Yposition") {
                std::string str = getString();
                log("set ch01 yposition = %s", str.c_str());
            } else if (str == "start") {
                std::string str = getString();
                log("set ch01 start = %s", str.c_str());
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        else if (str == "ch02") {
            std::string str = getString();
            if (str == "name") {
                std::string str = getString();
                log("set ch02 name = %s", str.c_str());
            } else if (str == "effect") {
                std::string str = getString();
                log("set ch02 effect = %s", str.c_str());
            } else if (str == "Xscale") {
                std::string str = getString();
                log("set ch02 xscale = %s", str.c_str());
            } else if (str == "Yscale") {
                std::string str = getString();
                log("set ch02 yscale = %s", str.c_str());
            } else if (str == "Xposition") {
                std::string str = getString();
                log("set ch02 xposition = %s", str.c_str());
            } else if (str == "Yposition") {
                std::string str = getString();
                log("set ch02 yposition = %s", str.c_str());
            } else if (str == "start") {
                std::string str = getString();
                log("set ch02 start = %s", str.c_str());
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        else if (str == "ch03") {
            std::string str = getString();
            if (str == "name") {
                std::string str = getString();
                log("set ch03 name = %s", str.c_str());
            } else if (str == "effect") {
                std::string str = getString();
                log("set ch03 effect = %s", str.c_str());
            } else if (str == "Xscale") {
                std::string str = getString();
                log("set ch03 xscale = %s", str.c_str());
            } else if (str == "Yscale") {
                std::string str = getString();
                log("set ch03 yscale = %s", str.c_str());
            } else if (str == "Xposition") {
                std::string str = getString();
                log("set ch03 xposition = %s", str.c_str());
            } else if (str == "Yposition") {
                std::string str = getString();
                log("set ch03 yposition = %s", str.c_str());
            } else if (str == "start") {
                std::string str = getString();
                log("set ch03 start = %s", str.c_str());
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        else if (str == "ch04") {
            std::string str = getString();
            if (str == "name") {
                std::string str = getString();
                log("set ch04 name = %s", str.c_str());
            } else if (str == "effect") {
                std::string str = getString();
                log("set ch04 effect = %s", str.c_str());
            } else if (str == "Xscale") {
                std::string str = getString();
                log("set ch04 xscale = %s", str.c_str());
            } else if (str == "Yscale") {
                std::string str = getString();
                log("set ch04 yscale = %s", str.c_str());
            } else if (str == "Xposition") {
                std::string str = getString();
                log("set ch04 xposition = %s", str.c_str());
            } else if (str == "Yposition") {
                std::string str = getString();
                log("set ch04 yposition = %s", str.c_str());
            } else if (str == "start") {
                std::string str = getString();
                log("set ch04 start = %s", str.c_str());
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // variables
        else if (str == "globalint") {
            std::string var = getString();
            std::string opr = getString();
            int num = transStringToInt(getString());
            if (opr == "equal") {
                VariableController::getInstance()->setInt(var, num);
                // for variables calculations, we don't need to wait
                GameScene::getInstance()->isMissionCompleted = true;
            } else if (opr == "add") {
                int temp = VariableController::getInstance()->getInt(var);
                VariableController::getInstance()->setInt(var, temp+num);
                GameScene::getInstance()->isMissionCompleted = true;
            } else if (opr == "minus") {
                int temp = VariableController::getInstance()->getInt(var);
                VariableController::getInstance()->setInt(var, temp-num);
                GameScene::getInstance()->isMissionCompleted = true;
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        else {
            showError(UNKNOWN_COMMAND);
        }
    }
    /* **********************
     *          get
     * **********************
     */
    else if (cmd == "get") {
        std::string str = getString();
        // touch event
        if (str == "touch") {
            log("waiting for a screen touch");
            GameScene::getInstance()->enableScreenTouchEventListener(true);
        }
        // get info of bgp
        else if (str == "bgp") {
            std::string str = getString();
            if (str == "name") {
                log("bgp name");
            } else if (str == "effect") {
                log("bgp effect");
            } else if (str == "Xscale") {
                log("bgp xscale");
            } else if (str == "Yscale") {
                log("bgp yscale");
            } else if (str == "Xposition") {
                log("bgp xposition");
            } else if (str == "Yposition") {
                log("bgp yposition");
            } else if (str == "start") {
                log("bgp start");
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // get info of cg
        else if (str == "cg") {
            std::string str = getString();
            if (str == "name") {
                log("cg name");
            } else if (str == "effect") {
                log("cg effect");
            } else if (str == "Xscale") {
                log("cg xscale");
            } else if (str == "Yscale") {
                log("cg yscale");
            } else if (str == "Xposition") {
                log("cg xposition");
            } else if (str == "Yposition") {
                log("cg yposition");
            } else if (str == "flowable") {
                log(" cg flowable");
            } else if (str == "start") {
                log("cg start");
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // get info of text
        else if (str == "text") {
            std::string str = getString();
            if (str == "content") {
                log("text content");
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // get info of bgm
        else if (str == "bgm") {
            std::string str = getString();
            if (str == "name") {
                log("bgm name");
            } else if (str == "start") {
                log("bgm start");
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // get info of se
        else if (str == "se") {
            std::string str = getString();
            if (str == "name") {
                log("se name");
            } else if (str == "start") {
                log("se start");
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // get info of charactor
        else if (str == "ch01") {
            std::string str = getString();
            if (str == "name") {
                log("ch01 name");
            } else if (str == "effect") {
                log("ch01 effect");
            } else if (str == "Xscale") {
                log("ch01 xscale");
            } else if (str == "Yscale") {
                log("ch01 yscale");
            } else if (str == "Xposition") {
                log("ch01 xposition");
            } else if (str == "Yposition") {
                log("ch01 yposition");
            } else if (str == "start") {
                log("ch01 start");
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        else if (str == "ch02") {
            std::string str = getString();
            if (str == "name") {
                log("ch02 name");
            } else if (str == "effect") {
                log("ch02 effect");
            } else if (str == "Xscale") {
                log("ch02 xscale");
            } else if (str == "Yscale") {
                log("ch02 yscale");
            } else if (str == "Xposition") {
                log("ch02 xposition");
            } else if (str == "Yposition") {
                log("ch02 yposition");
            } else if (str == "start") {
                log("ch02 start");
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        else if (str == "ch03") {
            std::string str = getString();
            if (str == "name") {
                log("ch03 name");
            } else if (str == "effect") {
                log("ch03 effect");
            } else if (str == "Xscale") {
                log("ch03 xscale");
            } else if (str == "Yscale") {
                log("ch03 yscale");
            } else if (str == "Xposition") {
                log("ch03 xposition");
            } else if (str == "Yposition") {
                log("ch03 yposition");
            } else if (str == "start") {
                log("ch03 start");
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        else if (str == "ch04") {
            std::string str = getString();
            if (str == "name") {
                log("ch04 name");
            } else if (str == "effect") {
                log("ch04 effect");
            } else if (str == "Xscale") {
                log("ch04 xscale");
            } else if (str == "Yscale") {
                log("ch04 yscale");
            } else if (str == "Xposition") {
                log("ch04 xposition");
            } else if (str == "Yposition") {
                log("ch04 yposition");
            } else if (str == "start") {
                log("ch04 start");
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // variables
        else if (str == "globalint") {
            std::string var = getString();
            int value = VariableController::getInstance()->getInt(var);
            log("%s = %d", var.c_str(), value);
            GameScene::getInstance()->isMissionCompleted = true;
        }
        else {
            showError(UNKNOWN_COMMAND);
        }
    }
    /* **********************
     *          if
     * **********************
     */
    else if (cmd == "if") {
        
    }
    if (!hasErr)
        stateBegin();
}

void ScriptController::stateEnd()
{
    log("stateEnd");
}

void ScriptController::showError(int errID)
{
    hasErr = true;
    switch (errID) {
        case UNRECOGNIZED_CHARACTOR:
            log("err: unrecognized charactor, line %d", lineID);
            break;
        case MISSED_ANOTHER_QUATATION_MARK:
            log("err: missed another quatation mark, line %d", lineID);
            break;
        case INVALID_EXPRESSION:
            log("err: invalid expression, line %d", lineID);
            break;
        case UNKNOWN_COMMAND:
            log("err: unknown command, line %d", lineID);
            break;
        case XXX:
            log("XXX");
            break;
        default:
            break;
    }
    //
    stateEnd();
}
