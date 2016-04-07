#include "build.gamefabricator.h"
#include "subject.me4button.h"
#include "subject.me1button.h"
#include "task.notifier.h"


GameFabricator::GameFabricator(void)
{}


Runnable GameFabricator::assembleMe4Button(uint8_t pinNumber)
{
    _notice4Button.subscribe( Me1ButtonSubject(_noticeButton1,    Me4ButtonSubject::BUTTON_1)    );
    _notice4Button.subscribe( Me1ButtonSubject(_noticeButton2,    Me4ButtonSubject::BUTTON_2)    );
    _notice4Button.subscribe( Me1ButtonSubject(_noticeButton3,    Me4ButtonSubject::BUTTON_3)    );
    _notice4Button.subscribe( Me1ButtonSubject(_noticeButton4,    Me4ButtonSubject::BUTTON_4)    );
    _notice4Button.subscribe( Me1ButtonSubject(_noticeButtonNone, Me4ButtonSubject::BUTTON_NONE) );

    ControllerPin pin(pinNumber);
    Me4ButtonSubject noticePin(_notice4Button);
    return [pin, noticePin](void) mutable -> void { noticePin(pin.readPin()); };
}
