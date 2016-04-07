#ifndef BUILD_GAMEFABRICATOR_H
#define BUILD_GAMEFABRICATOR_H

#include <build.robotfabricator.h>
#include <subject.me4button.h>
#include <subject.me1button.h>
#include <task.notifier.h>
#include <task.runner.h>


class GameFabricator : public RobotFabricator
{
public:

    GameFabricator(void);

    Runnable buildButtonViewer(void);

protected:

    Me4Button::PROCESSOR    assembleDisplayButton(void);
    SinkUint16              assembleSegmentedDisplayDecimal(uint8_t scl, uint8_t sda);
    SinkUint16              assembleMatrixDisplayDecimal(uint8_t scl, uint8_t sda);
    Runnable                assembleMe4ButtonPanel(uint8_t pinNumber, Me4Button::PROCESSOR observer);

    Me4Button::PROCESSOR    assembleMe4Buttons(Me1ButtonSubject::OBSERVER obNone,
                                               Me1ButtonSubject::OBSERVER ob1,
                                               Me1ButtonSubject::OBSERVER ob2,
                                               Me1ButtonSubject::OBSERVER ob3,
                                               Me1ButtonSubject::OBSERVER ob4);


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
