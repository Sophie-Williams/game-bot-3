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


void GameFabricator::build4ButtonPanelViewer(void)
{
    auto fnObserver = assembleMatrixDisplayDecimal(MeLEDMatrixScl, MeLEDMatrixSda);
    _gamebot._controlPanelNotices.subscribe(fnObserver);
}


void GameFabricator::buildSerializeFreeMemory(void)
{
    auto fn = []() { serializeFreeMemory(""); };
    auto fnButtonPressed = Me1ButtonSubject( ButtonObserver(fn), Me4Button::BUTTON_1 );
    _gamebot._controlPanelNotices.subscribe( fnButtonPressed );
}


void GameFabricator::buildDisplayFreeMemory(void)
{
    auto fnMatrixDisplay = assembleMatrixDisplayDecimal(MeLEDMatrixScl, MeLEDMatrixSda);

    auto fnFreeMemory   = [fnMatrixDisplay]() { fnMatrixDisplay(freeMemory()); };
    auto fnZero         = [fnMatrixDisplay]() { fnMatrixDisplay(0);            };

    auto fnButtonPressed    = Me1ButtonSubject( ButtonObserver( fnFreeMemory ), Me4Button::BUTTON_2    );
    auto fnButtonReleased   = Me1ButtonSubject( ButtonObserver( fnZero       ), Me4Button::BUTTON_NONE );

    _gamebot._controlPanelNotices.subscribe( fnButtonPressed  );
    _gamebot._controlPanelNotices.subscribe( fnButtonReleased );
}


void GameFabricator::subscribe(uint16_t time, Runnable task)
{
    _gamebot._eventLoop.subscribe( TaskTimer(time, task) );
}


EventLoop GameFabricator::getEventLoop(void)
{
    return _gamebot._eventLoop;//getEventLoop();
}
