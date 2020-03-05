#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>
using namespace cv; using namespace std;
class CustomizedException : public exception
{
    char msg[100];
public:
    CustomizedException(const char* e)
    {
        strcpy(msg, e);
    }
    virtual const char* what()
    {
        return msg;
    }
};

#endif // EXCEPTIONS_H
