#ifndef BUILD_GAMEFABRICATOR_H
#define BUILD_GAMEFABRICATOR_H

#include <build.robotfabricator.h>
#include <subject.me4button.h>
#include <task.notifier.h>
#include <task.runner.h>


class GameFabricator : public RobotFabricator
{
public:

    GameFabricator(void);


protected:

    Me4Button::PROCESSOR    assembleDisplayButton(void);
    SinkUint16              assembleSegmentedDisplayButton(void);
    SinkUint16              assembleMatrixDisplayButton(void);
    Runnable                assembleMe4ButtonPanel(uint8_t pinNumber, Me4Button::PROCESSOR observer);
    void                    assembleMe4Buttons(void);


private:

    class GameBot
    {
    public:

        GameBot(void) {}

        void operator()(void) { while (true) _runner(); }


    public:

        TaskRunner _runner;

        Notifier<Me4Button::BUTTON> _notice4Button;

        Notifier<BUTTON_STATE> _noticeButtonNone;
        Notifier<BUTTON_STATE> _noticeButton1;
        Notifier<BUTTON_STATE> _noticeButton2;
        Notifier<BUTTON_STATE> _noticeButton3;
        Notifier<BUTTON_STATE> _noticeButton4;

    };

    GameBot _bot;

};


#endif
