/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#ifndef __CCANIMATIONCURVE_H__
#define __CCANIMATIONCURVE_H__

#include <unordered_map>
#include <functional>

#include "base/ccTypes.h"
#include "base/CCPlatformMacros.h"
#include "base/CCRef.h"
#include "math/CCMath.h"


NS_CC_BEGIN

enum class EvaluateType
{
    LINEAR,
    NEARE,
    QUAT_SLERP,
    USER_FUNCTION,
};

/**
 * curve of bone's position, rotation or scale
 */
template <int componentSize>
class AnimationCurve: public Ref
{
public:
    
    //create animation curve
    static AnimationCurve* create(float* keytime, float* value, int count);
    
    void evaluate(float time, float* dst, EvaluateType type) const;
    
    void setEvaluateFun(std::function<void(float time, float* dst)> fun);
    
    float getStartTime() const;
    
    float getEndTime() const;
    
CC_CONSTRUCTOR_ACCESS:
    
    AnimationCurve();
    virtual ~AnimationCurve();
    
    /**
     * Determine index by time.
     */
    int determineIndex(float time) const;
    
protected:
    
    float* _value;   //
    float* _keytime; //key time(0 - 1), start time _keytime[0], end time _keytime[_count - 1]
    int _count;
    int _componentSizeByte; //component size in byte, position and scale 3 * sizeof(float), rotation 4 * sizeof(float)
    
    std::function<void(float time, float* dst)> _evaluateFun;
};

NS_CC_END

#include "CCAnimationCurve.inl"

#endif
