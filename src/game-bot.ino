#include <StandardCplusplus.h>
#include <functional-vlpp.h>
#include <functional-bot.h>
#include "build.gamefabricator.h"


static Idleloop idleloop;


static void buildMachine(GameFabricator &fabricator)
{
    fabricator.buildDisplayAnimator();
    fabricator.buildButtonViewer();
}


void setup(void)
{
    Serial.begin(9600);

    GameFabricator fabricator;
    buildMachine(fabricator);
    idleloop = fabricator.getIdleloop();

    Serial.println("Setup complete");
}


void loop(void)
{
    idleloop();
}
