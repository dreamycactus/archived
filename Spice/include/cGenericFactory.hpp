// Generic Factory Design Pattern used to encapsulate the creation of objects
#ifndef CGENERICFACTORY_H
#define CGENERICFACTORY_H

#include <map>
#include <string>

// Macro for map insertion

using std::string;

template<class T>
class cGenericFactory
{
    public:
                    cGenericFactory() {}        // Make into Singleton?? Yuck
                    virtual ~cGenericFactory() {}

        typedef     T* (*tObject)(); // Typedef for a function. News to me!
        typedef     std::map<std::string, tObject> tObjectMap;

        // First param is string key associated with object type
        // Second param is function pointer to a function that returns a new instance of that object
        bool        RegisterClass(const char *p_type, tObject aObject)
                    {
                        string str = string(p_type);
                        return m_objects.insert(std::pair<std::string, tObject>(str, aObject)).second;
                    }

        T*          CreateObject(const char* p_type)
                    {
                        typename tObjectMap::const_iterator it = m_objects.find((string(p_type))); // Need const_iterator because template is not instatiated

                        if (it != m_objects.end())
                        {
                            tObject toret = (*it).second;
                            return toret();
                        }

                        return 0;
                    }
    private:
        tObjectMap  m_objects;
};

#endif // CGENERICFACTORY_H
