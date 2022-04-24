#ifndef PIXEE_DRAGCONTROLLER_H
#define PIXEE_DRAGCONTROLLER_H


#include "Canvas.h"
#include <wx/wx.h>

class DragController {
    Canvas* target;
    wxPoint previousPosition;

public:
    explicit DragController(Canvas* canvas);
    void start();
    void stop();

private:
    void motionHandler(wxMouseEvent& event);
};


#endif // PIXEE_DRAGCONTROLLER_H
