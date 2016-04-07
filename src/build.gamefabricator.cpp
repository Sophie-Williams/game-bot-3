#include "build.gamefabricator.h"
#include <subject.me4button.h>
#include <subject.me1button.h>
#include <task.notifier.h>
#include <hardware.me7segmentencoder.h>
#include <hardware.meledmatrixencoder.h>
#include <protocol.segmentdisplay.h>
#include <protocol.meledmatrix.h>
#include <util.encoders.h>


GameFabricator::GameFabricator(void)
{}


void GameFabricator::assembleDisplayButton(void)
{
    auto fnDisplay1 = assembleSegmentedDisplayButton();
    auto fnDisplay2 = assembleMatrixDisplayButton();

    auto fn = [fnDisplay1, fnDisplay2](Me4Button::BUTTON button) mutable -> void
    {
        fnDisplay1(button);
        fnDisplay2(button);
    };

    _bot._notice4Button.subscribe(fn);
}


Me4Button::PROCESSOR GameFabricator::assembleSegmentedDisplayButton(void)
{
    SegmentDisplayProtocol serializer1(createSegmentDisplayProtocol(2, 8));
    DecEncoder encoder1(Me7SegmentEncoder::encodeDec);

    return [serializer1, encoder1](Me4Button::BUTTON button) mutable -> void
    {
        serializer1(encoder1((uint16_t) button));
    };
}


Me4Button::PROCESSOR GameFabricator::assembleMatrixDisplayButton(void)
{
    MeLEDMatrixProtocol serializer2(createMeLEDMatrixProtocol(12, 13));
    MatrixDecEncoder encoder2(MeLEDMatrixEncoder::encodeDec);

    return [serializer2, encoder2](Me4Button::BUTTON button) mutable -> void
    {
        serializer2(encoder2((uint16_t) button));
    };
}


Runnable GameFabricator::assembleMe4Button(uint8_t pinNumber)
{
    _bot._notice4Button.subscribe( Me1ButtonSubject(_bot._noticeButton1,    Me4Button::BUTTON_1)    );
    _bot._notice4Button.subscribe( Me1ButtonSubject(_bot._noticeButton2,    Me4Button::BUTTON_2)    );
    _bot._notice4Button.subscribe( Me1ButtonSubject(_bot._noticeButton3,    Me4Button::BUTTON_3)    );
    _bot._notice4Button.subscribe( Me1ButtonSubject(_bot._noticeButton4,    Me4Button::BUTTON_4)    );
    _bot._notice4Button.subscribe( Me1ButtonSubject(_bot._noticeButtonNone, Me4Button::BUTTON_NONE) );

    ControllerPin pin(pinNumber);
    Me4ButtonSubject setButtonState(_bot._notice4Button);
    return [pin, setButtonState](void) mutable -> void { setButtonState(Me4Button::translatePin(pin.readPin())); };
}
