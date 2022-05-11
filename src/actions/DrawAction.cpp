#include "DrawAction.h"
#include "../MyFrame.h"

// hopefully only temporary
namespace {
    wxColour getColourAt(const wxImage& image, wxPoint coord) {
        return wxColour (
                image.GetRed(coord.x, coord.y),
                image.GetGreen(coord.x, coord.y),
                image.GetBlue(coord.x, coord.y),
                image.HasAlpha() ? image.GetAlpha(coord.x, coord.y) : 255
            );
    }
    // wxColour's built in == operator returns false on seemingly equivalent values
    bool isSameColor(const wxColour& left, const wxColour& right) {
        return left.GetRGBA() == right.GetRGBA();
    }
}

DrawAction::DrawAction(const wxPoint& cell, const wxColour& color) : cell(cell), color(color) {

}

bool DrawAction::perform(MyFrame& myFrame) {
    wxImage& image(myFrame.getImage());
    previousColor = getColourAt(image, cell);
    if(isSameColor(previousColor, color))
        return false;
    image.SetRGB(cell.x, cell.y, color.Red(), color.Green(), color.Blue());
    if(image.HasAlpha())
        image.SetAlpha(cell.x, cell.y, color.GetAlpha());
    return true;
}

void DrawAction::undo(MyFrame &editor) {
    wxImage& image(editor.getImage());
    image.SetRGB(cell.x, cell.y, previousColor.Red(), previousColor.Green(), previousColor.Blue());
    if(image.HasAlpha())
        image.SetAlpha(cell.x, cell.y, previousColor.GetAlpha());
}
