#include "build.gamefabricator.h"
#include "subject.me4button.h"


GameFabricator::GameFabricator(void)
{}


Me4ButtonSubject GameFabricator::assembleMe4Button(uint8_t pinNumber)
{
    ControllerPin *pin = new ControllerPin(pinNumber);
    return Me4ButtonSubject(pin);
}
