#ifndef PIXEE_ACTIONPERFORMER_H
#define PIXEE_ACTIONPERFORMER_H

#include "Action.h"
#include <stack>
#include <memory>

class MyFrame;

class ActionPerformer {
    MyFrame* editor;
    std::stack<std::unique_ptr<Action>> past;
public:
    explicit ActionPerformer(MyFrame* editor);
    void performAction(std::unique_ptr<Action> action);
    void undo();
};


#endif //PIXEE_ACTIONPERFORMER_H
