#ifndef PIXEE_ACTION_H
#define PIXEE_ACTION_H

class MyFrame;

class Action {
public:
    virtual void perform(MyFrame& editor) = 0;
    virtual void undo(MyFrame& editor) = 0;
};


#endif //PIXEE_ACTION_H
