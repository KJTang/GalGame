
//
//  scriptController.cpp
//  Test
//
//  Created by KJTang on 15/7/13.
//
//

#include "scriptController.h"

scriptController* scriptController::sharedScriptController = NULL;

scriptController::scriptController(){}

scriptController::~scriptController(){}

bool scriptController::init()
{
    return true;
}

void scriptController::test()
{
    log("running");
    FILE *fin = std::fopen("file.txt", "r");
    
    if (fin) {
        log("open file");
        
        char c;
        fgetc(fin);
        
        log("----%c", c);
        
        fclose(fin);
    }
    else
        log("cannot open file");
}