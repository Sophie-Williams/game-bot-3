#ifndef BUILD_GAMEFABRICATOR_H
#define BUILD_GAMEFABRICATOR_H

#include <build.robotfabricator.h>
#include <task.notifier.h>

class Me4ButtonSubject;
class Me1ButtonSubject;


class GameFabricator : public RobotFabricator
{
public:

    GameFabricator(void);


protected:

    Me4ButtonSubject *assembleMe4Button(uint8_t pinNumber);


private:

    Notifier<Me4ButtonSubject> _notice4Button;
    Notifier<Me1ButtonSubject> _noticeButtonNone;
    Notifier<Me1ButtonSubject> _noticeButton1;
    Notifier<Me1ButtonSubject> _noticeButton2;
    Notifier<Me1ButtonSubject> _noticeButton3;
    Notifier<Me1ButtonSubject> _noticeButton4;

    Me4ButtonSubject    *_subject4Button;
    Me1ButtonSubject    *_subjectKey1;
    Me1ButtonSubject    *_subjectKey2;
    Me1ButtonSubject    *_subjectKey3;
    Me1ButtonSubject    *_subjectKey4;
    Me1ButtonSubject    *_subjectKeyNone;
};


#endif
