#include "GameScene.h"
#include <fstream>

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
    
    VariableController::getInstance()->readFromScript();
//    VariableController::getInstance()->test();

    ScriptController::getInstance()->runWithFile("file.txt");

    
//    std::string path = FileUtils::getInstance()->getWritablePath()+"global.txt";
//    log("%s", path.c_str());
//    
//    std::ofstream fout(path.c_str());
//    fout<<"//it is only a test"<<std::endl;
//    fout<<"int num = 5"<<std::endl;
//    
//    std::ifstream fin(path.c_str());
//    std::string data;
//    fin>>data;
//    log("%s", data.c_str());
    
    return true;
}
