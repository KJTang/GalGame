//
//  BlurInAndOut.cpp
//  Test
//
//  Created by KJTang on 15/8/4.
//
//

#include "BlurInAndOut.h"

/*
 * Blur In: blur the target
 */

BlurIn::BlurIn(){}

BlurIn::~BlurIn(){}

BlurIn* BlurIn::create(float duration)
{
    BlurIn* temp = new BlurIn();
    temp->init(duration);
    temp->autorelease();
    
    return temp;
}

bool BlurIn::init(float duration)
{
    if(ActionInterval::initWithDuration(duration))
    {
        countFlag = duration / Director::getInstance()->getAnimationInterval() / 3;
        count = -1;
        
        // min blur
        GLProgram *temp = GLProgramCache::getInstance()->getGLProgram("minblur");
        if (!temp) {
            auto blur1 = new GLProgram();
            blur1->initWithFilenames("BlurVertexShader.vert", "BlurFragmentShader1.frag");
            blur1->bindAttribLocation(
                                      GLProgram::ATTRIBUTE_NAME_POSITION,
                                      GLProgram::VERTEX_ATTRIB_POSITION);
            blur1->bindAttribLocation(
                                      GLProgram::ATTRIBUTE_NAME_COLOR,
                                      GLProgram::VERTEX_ATTRIB_COLOR);
            blur1->bindAttribLocation(
                                      GLProgram::ATTRIBUTE_NAME_TEX_COORD,
                                      GLProgram::VERTEX_ATTRIB_TEX_COORDS);
            blur1->link();
            blur1->updateUniforms();
            GLProgramCache::getInstance()->addGLProgram(blur1, "minblur");
        }
        
        // mid blur
        temp = GLProgramCache::getInstance()->getGLProgram("midblur");
        if (!temp) {
            auto blur2 = new GLProgram();
            blur2->initWithFilenames("BlurVertexShader.vert", "BlurFragmentShader2.frag");
            blur2->bindAttribLocation(
                                      GLProgram::ATTRIBUTE_NAME_POSITION,
                                      GLProgram::VERTEX_ATTRIB_POSITION);
            blur2->bindAttribLocation(
                                      GLProgram::ATTRIBUTE_NAME_COLOR,
                                      GLProgram::VERTEX_ATTRIB_COLOR);
            blur2->bindAttribLocation(
                                      GLProgram::ATTRIBUTE_NAME_TEX_COORD,
                                      GLProgram::VERTEX_ATTRIB_TEX_COORDS);
            blur2->link();
            blur2->updateUniforms();
            GLProgramCache::getInstance()->addGLProgram(blur2, "midblur");
        }
        
        // max blur
        temp = GLProgramCache::getInstance()->getGLProgram("maxblur");
        if (!temp) {
            auto blur3 = new GLProgram();
            blur3->initWithFilenames("BlurVertexShader.vert", "BlurFragmentShader3.frag");
            blur3->bindAttribLocation(
                                      GLProgram::ATTRIBUTE_NAME_POSITION,
                                      GLProgram::VERTEX_ATTRIB_POSITION);
            blur3->bindAttribLocation(
                                      GLProgram::ATTRIBUTE_NAME_COLOR,
                                      GLProgram::VERTEX_ATTRIB_COLOR);
            blur3->bindAttribLocation(
                                      GLProgram::ATTRIBUTE_NAME_TEX_COORD,
                                      GLProgram::VERTEX_ATTRIB_TEX_COORDS);
            blur3->link();
            blur3->updateUniforms();
            GLProgramCache::getInstance()->addGLProgram(blur3, "maxblur");
        }
        
        return true;
    }
    return false;
}

void BlurIn::update(float dt)
{
    ++count;
    if (count == 0) {
        _target->setGLProgram(GLProgramCache::getInstance()->getGLProgram("minblur"));
    } else if (count == countFlag * 1) {
        _target->setGLProgram(GLProgramCache::getInstance()->getGLProgram("midblur"));
    } else if (count == countFlag * 2) {
        _target->setGLProgram(GLProgramCache::getInstance()->getGLProgram("maxblur"));
    }
}

/*
 * Blur Out: clear the target
 */

BlurOut::BlurOut(){}

BlurOut::~BlurOut(){}

BlurOut* BlurOut::create(float duration)
{
    BlurOut* temp = new BlurOut();
    temp->init(duration);
    temp->autorelease();
    
    return temp;
}

bool BlurOut::init(float duration)
{
    if(ActionInterval::initWithDuration(duration))
    {
        countFlag = duration / Director::getInstance()->getAnimationInterval() / 3;
        count = -1;
        
        // min blur
        GLProgram *temp = GLProgramCache::getInstance()->getGLProgram("noblur");
        if (!temp) {
            auto blur1 = new GLProgram();
            blur1->initWithFilenames("BlurVertexShader.vert", "BlurFragmentShader0.frag");
            blur1->bindAttribLocation(
                                      GLProgram::ATTRIBUTE_NAME_POSITION,
                                      GLProgram::VERTEX_ATTRIB_POSITION);
            blur1->bindAttribLocation(
                                      GLProgram::ATTRIBUTE_NAME_COLOR,
                                      GLProgram::VERTEX_ATTRIB_COLOR);
            blur1->bindAttribLocation(
                                      GLProgram::ATTRIBUTE_NAME_TEX_COORD,
                                      GLProgram::VERTEX_ATTRIB_TEX_COORDS);
            blur1->link();
            blur1->updateUniforms();
            GLProgramCache::getInstance()->addGLProgram(blur1, "noblur");
        }
        // mid blur
        temp = GLProgramCache::getInstance()->getGLProgram("minblur");
        if (!temp) {
            auto blur2 = new GLProgram();
            blur2->initWithFilenames("BlurVertexShader.vert", "BlurFragmentShader1.frag");
            blur2->bindAttribLocation(
                                      GLProgram::ATTRIBUTE_NAME_POSITION,
                                      GLProgram::VERTEX_ATTRIB_POSITION);
            blur2->bindAttribLocation(
                                      GLProgram::ATTRIBUTE_NAME_COLOR,
                                      GLProgram::VERTEX_ATTRIB_COLOR);
            blur2->bindAttribLocation(
                                      GLProgram::ATTRIBUTE_NAME_TEX_COORD,
                                      GLProgram::VERTEX_ATTRIB_TEX_COORDS);
            blur2->link();
            blur2->updateUniforms();
            GLProgramCache::getInstance()->addGLProgram(blur2, "minblur");
        }
        // max blur
        temp = GLProgramCache::getInstance()->getGLProgram("midblur");
        if (!temp) {
            auto blur3 = new GLProgram();
            blur3->initWithFilenames("BlurVertexShader.vert", "BlurFragmentShader2.frag");
            blur3->bindAttribLocation(
                                      GLProgram::ATTRIBUTE_NAME_POSITION,
                                      GLProgram::VERTEX_ATTRIB_POSITION);
            blur3->bindAttribLocation(
                                      GLProgram::ATTRIBUTE_NAME_COLOR,
                                      GLProgram::VERTEX_ATTRIB_COLOR);
            blur3->bindAttribLocation(
                                      GLProgram::ATTRIBUTE_NAME_TEX_COORD,
                                      GLProgram::VERTEX_ATTRIB_TEX_COORDS);
            blur3->link();
            blur3->updateUniforms();
            GLProgramCache::getInstance()->addGLProgram(blur3, "midblur");
        }
        
        return true;
    }
    return false;
}

void BlurOut::update(float dt)
{
    ++count;
    if (count == 0) {
        _target->setGLProgram(GLProgramCache::getInstance()->getGLProgram("midblur"));
    } else if (count == countFlag * 1) {
        _target->setGLProgram(GLProgramCache::getInstance()->getGLProgram("minblur"));
    } else if (count == countFlag * 2) {
        _target->setGLProgram(GLProgramCache::getInstance()->getGLProgram("noblur"));
    }
}