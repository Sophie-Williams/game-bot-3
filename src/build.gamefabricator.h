#ifndef BUILD_GAMEFABRICATOR_H
#define BUILD_GAMEFABRICATOR_H

#include <build.robotfabricator.h>

class Me4ButtonSubject;
class Me1ButtonSubject;


class GameFabricator : public RobotFabricator
{
public:

    GameFabricator(void);


protected:

    Me4ButtonSubject *assembleMe4Button(uint8_t pinNumber);


private:

    Me4ButtonSubject    *_subject4Button;
    Me1ButtonSubject    *_subjectKey1;
    Me1ButtonSubject    *_subjectKey2;
    Me1ButtonSubject    *_subjectKey3;
    Me1ButtonSubject    *_subjectKey4;
    Me1ButtonSubject    *_subjectKeyNone;
};


#endif
