#include "../include/CAnimation.h"

CAnimation::CAnimation()
{
    frameRate = 1.2;
    maxFrames = 0;
    Init();

}

CAnimation::CAnimation(double fr, int mf)
{
    frameRate = fr; maxFrames = mf;
    Init();
}

void CAnimation::Init()
{
    currentFrame = 0;
    frameInc = 1;
    oldTime = 0;
    oscillate = false;
    update = nonupdate = 0;
    hold = false;
    frameTransStart = 0;
}
void CAnimation::OnAnimate()
{
    if (hold)
        return;
    if ((int)(update*frameRate) > nonupdate)
    {
        ++nonupdate;
        return;
    }
    ++update;
    currentFrame += frameInc;
    if (oscillate)
    {
        if (frameInc > 0)
        {
            if (currentFrame >= maxFrames - 1)
                frameInc = -frameInc;
        }
        else
        {
            if (currentFrame <= 0)
                frameInc = -frameInc;
        }
    }
    else
    {
        if (currentFrame > maxFrames - 1)
            currentFrame = 0;
    }

}

void CAnimation::Trans()
{
    currentFrame = frameTransStart;
}

void CAnimation::Hold(bool h)
{
    hold = h;
}

void CAnimation::Reset()
{
    hold = false;
    update = nonupdate = currentFrame = 0;
}

void CAnimation::SetFrameRate(double rate)
{
    frameRate = rate;
}

void CAnimation::SetCurrentFrame(int frame)
{
    if (frame < 0 || frame > maxFrames)
        return;
    currentFrame = frame;
}

int CAnimation::GetCurrentFrame()
{
    return currentFrame;
}
