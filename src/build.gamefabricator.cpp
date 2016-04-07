#include "build.gamefabricator.h"
#include <subject.me4button.h>
#include <subject.me1button.h>
#include <task.notifier.h>
#include <task.timer.h>
#include <hardware.me7segmentencoder.h>
#include <hardware.meledmatrixencoder.h>
#include <protocol.segmentdisplay.h>
#include <protocol.meledmatrix.h>
#include <util.encoders.h>

static const uint8_t Me7SegmentScl  = 2;
static const uint8_t Me7SegmentSda  = 8;
static const uint8_t MeLEDMatrixScl = 12;
static const uint8_t MeLEDMatrixSda = 13;


GameFabricator::GameFabricator(void)
{}


Runnable GameFabricator::buildButtonViewer(void)
{
    auto fnDisplay = assembleDisplayButton();
    auto fnPanel   = assembleMe4ButtonPanel(A0, fnDisplay);

    return TaskTimer(100, fnPanel);
}


Me4Button::PROCESSOR GameFabricator::assembleDisplayButton(void)
{
    auto fnDisplay1 = assembleSegmentedDisplayDecimal(Me7SegmentScl, Me7SegmentSda);
    auto fnDisplay2 = assembleMatrixDisplayDecimal(MeLEDMatrixScl, MeLEDMatrixSda);

    return [fnDisplay1, fnDisplay2](Me4Button::BUTTON button) mutable -> void
    {
        fnDisplay1((uint16_t) button);
        fnDisplay2((uint16_t) button);
    };
}


SinkUint16 GameFabricator::assembleSegmentedDisplayDecimal(uint8_t scl, uint8_t sda)
{
    SegmentDisplayProtocol serialize(createSegmentDisplayProtocol(scl, sda));
    DecEncoder encode(Me7SegmentEncoder::encodeDec);

    return [serialize, encode](uint16_t value) mutable -> void
    {
        serialize(encode(value));
    };
}


SinkUint16 GameFabricator::assembleMatrixDisplayDecimal(uint8_t scl, uint8_t sda)
{
    MeLEDMatrixProtocol serialize(createMeLEDMatrixProtocol(scl, sda));
    MatrixDecEncoder encode(MeLEDMatrixEncoder::encodeDec);

    return [serialize, encode](uint16_t value) mutable -> void
    {
        serialize(encode(value));
    };
}


Runnable GameFabricator::assembleMe4ButtonPanel(uint8_t pinNumber, Me4Button::PROCESSOR observer)
{
    ControllerPin pin(pinNumber);
    Me4ButtonSubject setButtonState(observer);

    return [pin, setButtonState](void) mutable -> void
    {
        setButtonState(Me4Button::translatePin(pin.readPin()));
    };
}


Me4Button::PROCESSOR GameFabricator::assembleMe4Buttons(Me1ButtonSubject::OBSERVER obNone,
                                                        Me1ButtonSubject::OBSERVER ob1,
                                                        Me1ButtonSubject::OBSERVER ob2,
                                                        Me1ButtonSubject::OBSERVER ob3,
                                                        Me1ButtonSubject::OBSERVER ob4)
{
    Notifier<Me4Button::BUTTON> fnNoticePanel;

    if (obNone) fnNoticePanel.subscribe( Me1ButtonSubject( obNone, Me4Button::BUTTON_NONE) );
    if (ob1)    fnNoticePanel.subscribe( Me1ButtonSubject( ob1,    Me4Button::BUTTON_1)    );
    if (ob2)    fnNoticePanel.subscribe( Me1ButtonSubject( ob2,    Me4Button::BUTTON_2)    );
    if (ob3)    fnNoticePanel.subscribe( Me1ButtonSubject( ob3,    Me4Button::BUTTON_3)    );
    if (ob4)    fnNoticePanel.subscribe( Me1ButtonSubject( ob4,    Me4Button::BUTTON_4)    );

    return fnNoticePanel;
}