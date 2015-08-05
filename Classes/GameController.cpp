//
//  GameController.cpp
//  Test
//
//  Created by KJTang on 15/7/14.
//
//

#include "GameController.h"

GameController* GameController::sharedGameController = NULL;

GameController::GameController(){}

GameController::~GameController(){}

bool GameController::init()
{
    // shaders
    LoadShader();

    currentState = STATE_PREPARING;
    return true;
}

void GameController::LoadShader()
{
    // grey shader
    auto greyShader = new GLProgram();
    greyShader->initWithFilenames("GreyVertexShader.vert", "GreyFragmentShader.frag");
    greyShader->bindAttribLocation(
                                   GLProgram::ATTRIBUTE_NAME_POSITION,
                                   GLProgram::VERTEX_ATTRIB_POSITION);
    greyShader->bindAttribLocation(
                                   GLProgram::ATTRIBUTE_NAME_COLOR,
                                   GLProgram::VERTEX_ATTRIB_COLOR);
    greyShader->bindAttribLocation(
                                   GLProgram::ATTRIBUTE_NAME_TEX_COORD,
                                   GLProgram::VERTEX_ATTRIB_TEX_COORDS);
    greyShader->link();
    greyShader->updateUniforms();
    GLProgramCache::getInstance()->addGLProgram(greyShader, "grey");    
    // text's shader
    auto textBlur = new GLProgram();
    textBlur->initWithFilenames("TextVertexShader.vert", "TextBlurShader.frag");
    textBlur->bindAttribLocation(
                                 GLProgram::ATTRIBUTE_NAME_POSITION,
                                 GLProgram::VERTEX_ATTRIB_POSITION);
    textBlur->bindAttribLocation(
                                 GLProgram::ATTRIBUTE_NAME_COLOR,
                                 GLProgram::VERTEX_ATTRIB_COLOR);
    textBlur->bindAttribLocation(
                                 GLProgram::ATTRIBUTE_NAME_TEX_COORD,
                                 GLProgram::VERTEX_ATTRIB_TEX_COORDS);
    textBlur->link();
    textBlur->updateUniforms();
    GLProgramCache::getInstance()->addGLProgram(textBlur, "textblur");
    
    auto textClear = new GLProgram();
    textClear->initWithFilenames("TextVertexShader.vert", "TextClearShader.frag");
    textClear->bindAttribLocation(
                                 GLProgram::ATTRIBUTE_NAME_POSITION,
                                 GLProgram::VERTEX_ATTRIB_POSITION);
    textClear->bindAttribLocation(
                                 GLProgram::ATTRIBUTE_NAME_COLOR,
                                 GLProgram::VERTEX_ATTRIB_COLOR);
    textClear->bindAttribLocation(
                                 GLProgram::ATTRIBUTE_NAME_TEX_COORD,
                                 GLProgram::VERTEX_ATTRIB_TEX_COORDS);
    textClear->link();
    textClear->updateUniforms();
    GLProgramCache::getInstance()->addGLProgram(textClear, "textclear");
}

void GameController::saveData(std::string dataname)
{
    std::string path = FileUtils::getInstance()->getWritablePath()+"dataname";
}

void GameController::loadData()
{
    
}

void GameController::enterStartScene()
{
    switch (currentState) {
        case STATE_PREPARING: {
            Director::getInstance()->runWithScene(StartScene::create());
            break;
        }
        case STATE_GAME_SCENE: {
            GameScene::getInstance()->clear();
            Director::getInstance()->purgeCachedData();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5, StartScene::create()));
            break;
        }
        case STATE_CONFIG_SCENE: {
            Director::getInstance()->popScene();
            break;
        }
        default:
            //
            break;
    }
    currentState = STATE_START_SCENE;
}

void GameController::enterGameScene(std::string dataFilename)
{
    if (dataFilename.size()) {
        switch (currentState) {
            case STATE_START_SCENE:
                Director::getInstance()->purgeCachedData();
                Director::getInstance()->replaceScene(TransitionFade::create(0.5, GameScene::getInstance()));
                GameScene::getInstance()->startSavedGame(dataFilename);
                break;
            default:
                break;
        }
    } else {
        switch (currentState) {
            case STATE_START_SCENE: {
                Director::getInstance()->purgeCachedData();
                Director::getInstance()->replaceScene(TransitionFade::create(0.5, GameScene::getInstance()));
                GameScene::getInstance()->startNewGame();
                break;
            }
                
            default:
                break;
        }
    }
    currentState = STATE_GAME_SCENE;
}

void GameController::enterConfigScene()
{
//    Director::getInstance()->purgeCachedData();
    Director::getInstance()->pushScene(TransitionFade::create(0.5, ConfigScene::create()));
    currentState = STATE_CONFIG_SCENE;
}

void GameController::exitGame()
{
    // used on android
//    Director::getInstance()->end();
    // used on iOS
    exit(0);
}

void GameController::loadBGM(std::string filename)
{
    bgmFilename = filename;
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(bgmFilename.c_str());
}

void GameController::playBGM()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(bgmFilename.c_str());
}

void GameController::pauseBGM()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void GameController::resumeBGM()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void GameController::stopBGM()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void GameController::setBGMVolume(float v)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(v);
}