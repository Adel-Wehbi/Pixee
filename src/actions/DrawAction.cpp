#include "DrawAction.h"
#include "../MyFrame.h"

DrawAction::DrawAction(const wxPoint& cell, const wxColour& color) : cell(cell), color(color) {

}

void DrawAction::perform(MyFrame& myFrame) {
    wxImage& image(myFrame.getImage());
    previousColor.Set(
        image.GetRed(cell.x, cell.y),
        image.GetGreen(cell.x, cell.y),
        image.GetBlue(cell.x, cell.y),
        image.HasAlpha() ? image.GetAlpha(cell.x, cell.y) : 255
    );
    image.SetRGB(cell.x, cell.y, color.Red(), color.Green(), color.Blue());
    if(image.HasAlpha())
        image.SetAlpha(cell.x, cell.y, color.GetAlpha());
}

void DrawAction::undo(MyFrame &editor) {
    wxImage& image(editor.getImage());
    image.SetRGB(cell.x, cell.y, previousColor.Red(), previousColor.Green(), previousColor.Blue());
    if(image.HasAlpha())
        image.SetAlpha(cell.x, cell.y, previousColor.GetAlpha());
}
