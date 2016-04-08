#ifndef GAME_BOT_H
#define GAME_BOT_H

#include <interfaces.h>
#include <subject.me4button.h>
#include <task.notifier.h>
#include <task.runner.h>


class GameBot
{
public:

    TaskRunner _runner;
    Notifier<Me4Button::BUTTON> _me4ButtonPanel;

    Me4Button::PROCESSOR get4ButtonProc(void)
    {
        return [this](Me4Button::BUTTON button) mutable -> void
        {
            _me4ButtonPanel(button);
        };
    }

    Runnable getIdleloop(void)
    {
        return [this](void) mutable -> void
        {
            _runner();
        };
    }

};


#endif
