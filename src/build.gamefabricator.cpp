#include "build.gamefabricator.h"
#include "subject.me4button.h"
#include "subject.me1button.h"
#include "task.notifier.h"


GameFabricator::GameFabricator(void)
{}


Runnable GameFabricator::assembleMe4Button(uint8_t pinNumber)
{
    _notice4Button.subscribe( Me1ButtonSubject(_noticeButton1,    Me4Button::BUTTON_1)    );
    _notice4Button.subscribe( Me1ButtonSubject(_noticeButton2,    Me4Button::BUTTON_2)    );
    _notice4Button.subscribe( Me1ButtonSubject(_noticeButton3,    Me4Button::BUTTON_3)    );
    _notice4Button.subscribe( Me1ButtonSubject(_noticeButton4,    Me4Button::BUTTON_4)    );
    _notice4Button.subscribe( Me1ButtonSubject(_noticeButtonNone, Me4Button::BUTTON_NONE) );

    ControllerPin pin(pinNumber);
    Me4ButtonSubject setButtonState(_notice4Button);
    return [pin, setButtonState](void) mutable -> void { setButtonState(Me4Button::translatePin(pin.readPin())); };
}
