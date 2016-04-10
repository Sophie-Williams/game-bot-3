#ifndef GAME_BOT_H
#define GAME_BOT_H

#include <interfaces.h>
#include <subject.me4button.h>
#include <task.notifier.h>
#include <task.runner.h>


class GameBot
{
public:

    using ControlPanel  = Notifier<Me4Button::BUTTON>;
    using ButtonNone    = Notifier<BUTTON_STATE>;
    using Button1       = Notifier<BUTTON_STATE>;
    using Button2       = Notifier<BUTTON_STATE>;
    using Button3       = Notifier<BUTTON_STATE>;
    using Button4       = Notifier<BUTTON_STATE>;


    TaskRunner      _eventLoop;
    ControlPanel    _controlPanelNotices;
    ButtonNone      _buttonNoneNotices;
    Button1         _button1Notices;
    Button2         _button2Notices;
    Button3         _button3Notices;
    Button4         _button4Notices;


    Runnable getEventLoop(void)
    { return [this](void) -> void { _eventLoop(); }; }

    Me4Button::OBSERVER ControlPanelSink(void)
    {
        return [this](Me4Button::BUTTON button) mutable -> void
        { _controlPanelNotices(button); };
    }

    Me4Button::OBSERVER ExperimentalSink(void)
    {
        return [this](Me4Button::BUTTON) -> void
        {};
    }

    SinkButton ButtonNoneSink(void)
    {
        return [this](BUTTON_STATE state) mutable -> void
        { _buttonNoneNotices(state); };
    }

    SinkButton Button1Sink(void)
    {
        return [this](BUTTON_STATE state) mutable -> void
        {  _button1Notices(state); };
    }

    SinkButton Button2Sink(void)
    {
        return [this](BUTTON_STATE state) mutable -> void
        {  _button2Notices(state); };
    }

    SinkButton Button3Sink(void)
    {
        return [this](BUTTON_STATE state) mutable -> void
        {  _button3Notices(state); };
    }

    SinkButton Button4Sink(void)
    {
        return [this](BUTTON_STATE state) mutable -> void
        {  _button4Notices(state); };
    }

};


#endif
