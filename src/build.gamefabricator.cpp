#include "build.gamefabricator.h"
#include "subject.me4button.h"
#include "subject.me1button.h"


GameFabricator::GameFabricator(void)
{}


Me4ButtonSubject *GameFabricator::assembleMe4Button(uint8_t pinNumber)
{
    ControllerPin *pin = new ControllerPin(pinNumber);
    _subject4Button = new Me4ButtonSubject(pin);

    _subjectKey1    = new Me1ButtonSubject(*_subject4Button, Me4ButtonSubject::BUTTON_1);
    _subjectKey2    = new Me1ButtonSubject(*_subject4Button, Me4ButtonSubject::BUTTON_2);
    _subjectKey3    = new Me1ButtonSubject(*_subject4Button, Me4ButtonSubject::BUTTON_3);
    _subjectKey4    = new Me1ButtonSubject(*_subject4Button, Me4ButtonSubject::BUTTON_4);
    _subjectKeyNone = new Me1ButtonSubject(*_subject4Button, Me4ButtonSubject::BUTTON_NONE);

    _subject4Button->attach(*_subjectKey1);
    _subject4Button->attach(*_subjectKey2);
    _subject4Button->attach(*_subjectKey3);
    _subject4Button->attach(*_subjectKey4);
    _subject4Button->attach(*_subjectKeyNone);

    return _subject4Button;
}
