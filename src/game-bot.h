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


    TaskRunner      _eventLoop;
    ControlPanel    _controlPanelNotices;


    Runnable getEventLoop(void)
    { return [this](void) -> void { _eventLoop(); }; }

    Me4Button::OBSERVER ControlPanelSink(void)
    {
        return [this](Me4Button::BUTTON button) mutable -> void
        { _controlPanelNotices(button); };
    }

};


#endif
