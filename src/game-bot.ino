#include <StandardCplusplus.h>
#include <functional-vlpp.h>
#include <functional-bot.h>
#include "build.gamefabricator.h"


static Idleloop idleloop;


void setup(void)
{
    Serial.begin(9600);

    idleloop = GameFabricator().buildButtonViewer();

    Serial.println("Setup complete");
}


void loop(void)
{
    idleloop();
}
