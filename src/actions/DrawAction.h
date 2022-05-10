#ifndef PIXEE_DRAWACTION_H
#define PIXEE_DRAWACTION_H


#include "../Action.h"

#include "wx/wx.h"

class MyFrame;

class DrawAction : public Action {
    wxPoint cell;
    wxColour color;
    wxColour previousColor;
public:
    DrawAction(const wxPoint& cell, const wxColour& color);
    void perform(MyFrame& editor) override;
    void undo(MyFrame& editor) override;
};


#endif //PIXEE_DRAWACTION_H
