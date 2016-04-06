#include "build.gamefabricator.h"
#include "subject.me4button.h"
#include "subject.me1button.h"
#include "task.notifier.h"


GameFabricator::GameFabricator(void)
{}


Me4ButtonSubject *GameFabricator::assembleMe4Button(uint8_t pinNumber)
{
    ControllerPin *pin = new ControllerPin(pinNumber);
    _subject4Button    = new Me4ButtonSubject(_notice4Button, pin);

    _subjectKey1    = new Me1ButtonSubject(_noticeButton1,    Me4ButtonSubject::BUTTON_1);
    _subjectKey2    = new Me1ButtonSubject(_noticeButton2,    Me4ButtonSubject::BUTTON_2);
    _subjectKey3    = new Me1ButtonSubject(_noticeButton3,    Me4ButtonSubject::BUTTON_3);
    _subjectKey4    = new Me1ButtonSubject(_noticeButton4,    Me4ButtonSubject::BUTTON_4);
    _subjectKeyNone = new Me1ButtonSubject(_noticeButtonNone, Me4ButtonSubject::BUTTON_NONE);

    _notice4Button.subscribe(*_subjectKey1);
    _notice4Button.subscribe(*_subjectKey2);
    _notice4Button.subscribe(*_subjectKey3);
    _notice4Button.subscribe(*_subjectKey4);
    _notice4Button.subscribe(*_subjectKeyNone);

    return _subject4Button;
}
