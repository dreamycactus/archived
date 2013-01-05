#ifndef CANIMATION_H
#define CANIMATION_H

class CAnimation
{
    public:

        CAnimation();
        CAnimation(double fr, int mf);
        void Init();
        void OnAnimate();
        void Hold(bool h);
        void Reset();
        void Trans();

        void SetFrameRate(double rate);
        void SetCurrentFrame(int Frame);
        int GetCurrentFrame();

        int maxFrames;
        bool oscillate;
        int frameTransStart;

    private:
        long update;
        long nonupdate;
        double frameRate;
        double oldTime;
        int currentFrame;
        int frameInc;
        bool hold;
};

#endif // CANIMATION_H
