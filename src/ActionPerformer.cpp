#include "ActionPerformer.h"

ActionPerformer::ActionPerformer(MyFrame* editor) : editor(editor){

}

void ActionPerformer::performAction(std::unique_ptr<Action> action) {
    action->perform(*editor);
    past.push(std::move(action));
}

void ActionPerformer::undo() {
    std::unique_ptr<Action>& action(past.top());
    action->undo(*editor);
    past.pop();
}
