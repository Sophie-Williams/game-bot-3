#ifndef BUILD_GAMEFABRICATOR_H
#define BUILD_GAMEFABRICATOR_H

#include <build.robotfabricator.h>
#include <task.notifier.h>
#include <task.runner.h>
#include "game-bot.h"


class GameFabricator : public RobotFabricator
{
public:

    GameFabricator(void);

    void build4ButtonPanel(void);
    void build4ButtonPanelViewer(void);

    Idleloop getIdleloop(void);

protected:

    void subscribe(uint16_t time, Runnable task);

    Me4Button::PROCESSOR    assembleMe4Buttons(Me1ButtonSubject::OBSERVER obNone,
                                               Me1ButtonSubject::OBSERVER ob1,
                                               Me1ButtonSubject::OBSERVER ob2,
                                               Me1ButtonSubject::OBSERVER ob3,
                                               Me1ButtonSubject::OBSERVER ob4);

    GameBot *_gamebot;

};


#endif
