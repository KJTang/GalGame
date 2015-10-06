//
//  ActionBlur.cpp
//  Test
//
//  Created by KJTang on 15/9/3.
//
//

#include "ActionBlur.h"

ActionBlur::ActionBlur(){}

ActionBlur::~ActionBlur(){}

ActionBlur* ActionBlur::create(float duration, int type)
{
    ActionBlur* temp = new ActionBlur();
    temp->init(duration, type);
    temp->autorelease();
    
    return temp;
}

bool ActionBlur::init(float duration, int type)
{
    if(ActionInterval::initWithDuration(duration))
    {
        step = duration / Director::getInstance()->getAnimationInterval() / 5;
        count = 0;
        blurType = type;
        blurValue[0] = 0;
        blurValue[1] = 2000;
        blurValue[2] = 1500;
        blurValue[3] = 1200;
        blurValue[4] = 1050;
        blurValue[5] = 900;
        blurValue[6] = 750;
        blurValue[7] = 600;
        blurValue[8] = 500;
        blurValue[9] = 450;
        blurValue[10] = 400;
        
        blur = new GLProgram();
        blur->initWithFilenames("BlurVertexShader.vert", "BlurFragmentShader.frag");
        blur->bindAttribLocation(
                                 GLProgram::ATTRIBUTE_NAME_POSITION,
                                 GLProgram::VERTEX_ATTRIB_POSITION);
        blur->bindAttribLocation(
                                 GLProgram::ATTRIBUTE_NAME_COLOR,
                                 GLProgram::VERTEX_ATTRIB_COLOR);
        blur->bindAttribLocation(
                                 GLProgram::ATTRIBUTE_NAME_TEX_COORD,
                                 GLProgram::VERTEX_ATTRIB_TEX_COORDS);
        blur->link();
        blur->updateUniforms();
        
        return true;
    }
    return false;
}

void ActionBlur::update(float dt)
{
    ++count;
    
    if (!(count % step)) {
        auto glprogramState = GLProgramState::getOrCreateWithGLProgram(blur);
        switch (blurType) {
            case NONE_TO_LITTLE:
                glprogramState->setUniformInt("u_blur", blurValue[count/step]);
                break;
            case NONE_TO_MUCH:
                glprogramState->setUniformInt("u_blur", blurValue[count/step*2]);
                break;
            case LITTLE_TO_NONE:
                if (5-count/step == 0) {
                    // reset shader to default
                    _target->setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
                }
                glprogramState->setUniformInt("u_blur",  blurValue[5-count/step]);
                break;
            case LITTLE_TO_MUCH:
                glprogramState->setUniformInt("u_blur", blurValue[count/step+5]);
                break;
            case MUCH_TO_NONE:
                if (10-count/step*2 == 0) {
                    // reset shader to default
                    _target->setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
                }
                glprogramState->setUniformInt("u_blur", blurValue[10-count/step*2]);
                break;
            case MUCH_TO_LITTLE:
                glprogramState->setUniformInt("u_blur", blurValue[11-count/step]);
                break;
                
            default:
                break;
        }
        _target->setGLProgram(blur);
        // different node need different shader, so when use more than one node, we
        // should create more than one shader
        if (count/step == 5) {
            blur = nullptr;
        }
    }
}