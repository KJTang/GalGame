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

ActionBlur* ActionBlur::create(float duration, int start, int end)
{
    CCASSERT(start >= 0 && end >= 0, "value cannot be less than 0");
    ActionBlur* temp = new ActionBlur();
    temp->init(duration, start, end);
    temp->autorelease();
    
    return temp;
}

bool ActionBlur::init(float duration, int start, int end)
{
    if(ActionInterval::initWithDuration(duration))
    {
        step = duration / Director::getInstance()->getAnimationInterval() / 5;
        count = 0;
        
        startLevel = start, endLevel = end;
        if (startLevel == NONE) {
            startLevel = 2000;
        }
        if (endLevel == NONE) {
            delta = (2000 - startLevel)/step;
        } else {
            delta = (endLevel - startLevel)/step;
        }

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
        
        if (endLevel == NONE && count/step == 5) {
            // reset shader to default
            _target->setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
            blur->release();
        } else {
            glprogramState->setUniformInt("u_blur", startLevel + delta*(count/step));
            _target->setGLProgram(blur);
        }
    }
}