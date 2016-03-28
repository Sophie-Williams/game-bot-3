#ifndef BUILD_GAMEFABRICATOR_H
#define BUILD_GAMEFABRICATOR_H

#include <build.robotfabricator.h>

class Me4ButtonSubject;


class GameFabricator : public RobotFabricator
{
public:

    GameFabricator(void);


protected:

    Me4ButtonSubject assembleMe4Button(uint8_t pinNumber);

};


#endif
