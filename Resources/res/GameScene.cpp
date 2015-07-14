#include "GameScene.h"
#include <stdio.h>

GameScene::GameScene() {
}

GameScene::~GameScene() {
}

bool GameScene::init() {
    if (!Scene::init())
        return false;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    auto bg = Sprite::create("HelloWorld.png");
    bg->setPosition(visibleSize.width/2, visibleSize.height/2);
    this->addChild(bg);
    
    FILE *fin = std::fopen("file.txt", "r");
    
    if (fin) {
        log("opened file");
        
        char c;
        fgetc(fin);
        
        log("----%c", c);
        
        fclose(fin);
    }
    else
        log("cannot open file");
    
//
//    std::ifstream fin("file.txt");
//    if (!fin) {
//        log("cannot open");
//    }
//    std::string data;
//    fin>>data;
//    log("file: %s", data.c_str());
//    fin.close();
    
    return true;
}