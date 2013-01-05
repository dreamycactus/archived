#ifndef IAPPLICATION_H
#define IAPPLICATION_H

namespace CORE
{
    class iApplication
    {
    public:
        virtual bool Initialise() = 0;
        virtual bool Terminate() = 0;
        virtual void MainLoop() = 0;
    };

}

#endif // IAPPLICATION_H
