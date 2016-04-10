#include <StandardCplusplus.h>
#include <functional-vlpp.h>
#include <functional-bot.h>
#include "build.gamefabricator.h"


static EventLoop eventloop;


static void buildMachine(GameFabricator &fabricator)
{
    fabricator.build4ButtonPanel();
    // fabricator.buildMockButtonPanel();
    // fabricator.buildPanelButtons();
    fabricator.build4ButtonPanelViewer();
    fabricator.buildDisplayAnimator();
}


void setup(void)
{
    Serial.begin(9600);

    GameFabricator fabricator;
    buildMachine(fabricator);
    eventloop = fabricator.getEventLoop();

    Serial.println("Setup complete");
}


void loop(void)
{
    eventloop();
}
