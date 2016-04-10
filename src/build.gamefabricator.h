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

    void buildMockButtonPanel(void);
    void buildDisplayFreeMemory(void);

    EventLoop getEventLoop(void);

protected:

    void subscribe(uint16_t time, Runnable task);

};


#endif
