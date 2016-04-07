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

static const uint8_t Me4ButtonPin   = A0;
static const uint8_t Me7SegmentScl  = 2;
static const uint8_t Me7SegmentSda  = 8;
static const uint8_t MeLEDMatrixScl = 12;
static const uint8_t MeLEDMatrixSda = 13;


GameFabricator::GameFabricator(void)
{}


void GameFabricator::buildButtonViewer(void)
{
    auto fnSource   = AnalogPinReader(Me4ButtonPin);
    auto fnSink     = assembleMatrixDisplayDecimal(MeLEDMatrixScl, MeLEDMatrixSda);
    auto fnPanel    = assembleMe4ButtonPanel(fnSource, fnSink);

    subscribe(50, fnPanel);
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