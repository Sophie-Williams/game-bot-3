#include "build.gamefabricator.h"
#include "subject.me4button.h"
#include "subject.me1button.h"
#include "task.notifier.h"


GameFabricator::GameFabricator(void)
{}


Me4ButtonSubject *GameFabricator::assembleMe4Button(uint8_t pinNumber)
{
    Notifier notice4Button;
    Notifier notice1Button;

    ControllerPin *pin = new ControllerPin(pinNumber);
    _subject4Button    = new Me4ButtonSubject(notice4Button, pin);

    _subjectKey1    = new Me1ButtonSubject(notice1Button, *_subject4Button, Me4ButtonSubject::BUTTON_1);
    _subjectKey2    = new Me1ButtonSubject(notice1Button, *_subject4Button, Me4ButtonSubject::BUTTON_2);
    _subjectKey3    = new Me1ButtonSubject(notice1Button, *_subject4Button, Me4ButtonSubject::BUTTON_3);
    _subjectKey4    = new Me1ButtonSubject(notice1Button, *_subject4Button, Me4ButtonSubject::BUTTON_4);
    _subjectKeyNone = new Me1ButtonSubject(notice1Button, *_subject4Button, Me4ButtonSubject::BUTTON_NONE);

    notice4Button.subscribe(*_subjectKey1);
    notice4Button.subscribe(*_subjectKey2);
    notice4Button.subscribe(*_subjectKey3);
    notice4Button.subscribe(*_subjectKey4);
    notice4Button.subscribe(*_subjectKeyNone);

    return _subject4Button;
}
