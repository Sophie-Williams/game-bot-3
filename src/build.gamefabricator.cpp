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


Me4Button::PROCESSOR GameFabricator::assembleDisplayButton(void)
{
    auto fnDisplay1 = assembleSegmentedDisplayButton();
    auto fnDisplay2 = assembleMatrixDisplayButton();

    return [fnDisplay1, fnDisplay2](Me4Button::BUTTON button) mutable -> void
    {
        fnDisplay1((uint16_t) button);
        fnDisplay2((uint16_t) button);
    };
}


SinkUint16 GameFabricator::assembleSegmentedDisplayButton(void)
{
    SegmentDisplayProtocol serializer1(createSegmentDisplayProtocol(2, 8));
    DecEncoder encoder1(Me7SegmentEncoder::encodeDec);

    return [serializer1, encoder1](uint16_t value) mutable -> void
    {
        serializer1(encoder1(value));
    };
}


SinkUint16 GameFabricator::assembleMatrixDisplayButton(void)
{
    MeLEDMatrixProtocol serializer2(createMeLEDMatrixProtocol(12, 13));
    MatrixDecEncoder encoder2(MeLEDMatrixEncoder::encodeDec);

    return [serializer2, encoder2](uint16_t value) mutable -> void
    {
        serializer2(encoder2(value));
    };
}


Runnable GameFabricator::assembleMe4ButtonPanel(uint8_t pinNumber, Me4Button::PROCESSOR observer)
{
    ControllerPin pin(pinNumber);
    Me4ButtonSubject setButtonState(observer);
    return [pin, setButtonState](void) mutable -> void { setButtonState(Me4Button::translatePin(pin.readPin())); };
}


void GameFabricator::assembleMe4Buttons(void)
{
    _bot._notice4Button.subscribe( Me1ButtonSubject( _bot._noticeButton1,    Me4Button::BUTTON_1)    );
    _bot._notice4Button.subscribe( Me1ButtonSubject( _bot._noticeButton2,    Me4Button::BUTTON_2)    );
    _bot._notice4Button.subscribe( Me1ButtonSubject( _bot._noticeButton3,    Me4Button::BUTTON_3)    );
    _bot._notice4Button.subscribe( Me1ButtonSubject( _bot._noticeButton4,    Me4Button::BUTTON_4)    );
    _bot._notice4Button.subscribe( Me1ButtonSubject( _bot._noticeButtonNone, Me4Button::BUTTON_NONE) );
}