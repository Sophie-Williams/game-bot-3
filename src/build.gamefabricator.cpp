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

GameBot _gamebot;


GameFabricator::GameFabricator(void)
{}


void GameFabricator::build4ButtonPanel(void)
{
    auto fnSource   = AnalogPinReader(Me4ButtonPin);
    auto fnSink     = _gamebot.ControlPanelSink();
    auto fnPanel    = assembleMe4ButtonPanel(fnSource, fnSink);

    subscribe(50, fnPanel);
}


void GameFabricator::buildMockButtonPanel(void)
{
    // GameBot *bot = _gamebot;
    auto fnSink     = _gamebot.ControlPanelSink();
    auto fnSource   = []() -> uint16_t
    {
        static uint16_t value = 950;
        value = 950 - value;
        return value;
    };

    subscribe(2000, [fnSource, fnSink]()
    {
        fnSink(Me4Button::translatePin(fnSource()));
    });
}


void GameFabricator::buildPanelButtons(void)
{
    _gamebot._controlPanelNotices.subscribe( Me1ButtonSubject( _gamebot.ButtonNoneSink(), Me4Button::BUTTON_NONE ) );
    _gamebot._controlPanelNotices.subscribe( Me1ButtonSubject( _gamebot.Button1Sink()   , Me4Button::BUTTON_1    ) );
    _gamebot._controlPanelNotices.subscribe( Me1ButtonSubject( _gamebot.Button2Sink()   , Me4Button::BUTTON_2    ) );
    _gamebot._controlPanelNotices.subscribe( Me1ButtonSubject( _gamebot.Button3Sink()   , Me4Button::BUTTON_3    ) );
    _gamebot._controlPanelNotices.subscribe( Me1ButtonSubject( _gamebot.Button4Sink()   , Me4Button::BUTTON_4    ) );
}


void GameFabricator::build4ButtonPanelViewer(void)
{
    auto fnObserver = assembleMatrixDisplayDecimal(MeLEDMatrixScl, MeLEDMatrixSda);
    _gamebot._controlPanelNotices.subscribe(fnObserver);
}


void GameFabricator::subscribe(uint16_t time, Runnable task)
{
    _gamebot._eventLoop.subscribe( TaskTimer(time, task) );
}


EventLoop GameFabricator::getEventLoop(void)
{
    return _gamebot._eventLoop;//getEventLoop();
}
