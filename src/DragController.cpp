#include "DragController.h"

DragController::DragController(Canvas *canvas) : target(canvas) { }

void DragController::start() {
    target->Bind(wxEVT_MOTION, &DragController::motionHandler, this);
    previousPosition = wxGetMousePosition();
}

void DragController::stop() {
    target->Unbind(wxEVT_MOTION, &DragController::motionHandler, this);
}

void DragController::motionHandler(wxMouseEvent &event) {
    wxPoint delta(wxGetMousePosition() - previousPosition);
    previousPosition = wxGetMousePosition();
    target->translateOrigin(delta.x, delta.y);
}
