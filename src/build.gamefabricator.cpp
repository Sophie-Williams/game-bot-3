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


uint16_t freeMemory();
class ButtonObserver
{
private:

    SourceUint16    _source;
    SinkUint16      _sink;

public:

    ButtonObserver(SourceUint16 source, SinkUint16 sink) : _source(source), _sink(sink) {}

    void operator()(BUTTON_STATE button)
    {
        if (button == BUTTON_PRESSED) _sink(_source());
    }
};

class Uint16
{
private:

    uint16_t _value;

public:

    Uint16(uint16_t value) : _value(value) {}

    uint16_t operator()(void)
    { return _value; }
};

template<typename TYPE>
class Constant
{
private:

    TYPE _value;

public:

    Constant(TYPE value) : _value(value) {}

    TYPE operator()(void)
    { return _value; }
};


void GameFabricator::buildDisplayFreeMemory(void)
{
    auto fnMatrixDisplay         = assembleMatrixDisplayDecimal(MeLEDMatrixScl, MeLEDMatrixSda);
    auto fnSegmentedDisplay      = assembleSegmentedDisplayDecimal(Me7SegmentScl, Me7SegmentSda);

    auto fnObserverForMatrix     = ButtonObserver(freeMemory, fnMatrixDisplay);
    auto fnObserverForSegmented  = ButtonObserver(freeMemory, fnSegmentedDisplay);

    // auto fnObserverZeroMatrix    = ButtonObserver([](){return 0;}, fnMatrixDisplay);
    // auto fnObserverZeroSegmented = ButtonObserver([](){return 0;}, fnSegmentedDisplay);
    auto fnObserverZeroMatrix    = ButtonObserver(Constant<uint16_t>(0), fnMatrixDisplay);
    auto fnObserverZeroSegmented = ButtonObserver(Constant<uint16_t>(0), fnSegmentedDisplay);

    _gamebot._controlPanelNotices.subscribe( Me1ButtonSubject( fnObserverForMatrix    , Me4Button::BUTTON_2 ) );
    _gamebot._controlPanelNotices.subscribe( Me1ButtonSubject( fnObserverForSegmented , Me4Button::BUTTON_4 ) );
    _gamebot._controlPanelNotices.subscribe( Me1ButtonSubject( fnObserverZeroMatrix   , Me4Button::BUTTON_NONE ) );
    _gamebot._controlPanelNotices.subscribe( Me1ButtonSubject( fnObserverZeroSegmented, Me4Button::BUTTON_NONE ) );
}


void GameFabricator::subscribe(uint16_t time, Runnable task)
{
    _gamebot._eventLoop.subscribe( TaskTimer(time, task) );
}


EventLoop GameFabricator::getEventLoop(void)
{
    return _gamebot._eventLoop;//getEventLoop();
}
