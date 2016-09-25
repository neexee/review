import QtQuick 2.1
import QtQuick.Layouts 1.0
import diffline 1.0

Rectangle {
    implicitHeight: itemText.implicitHeight
    implicitWidth: itemText.implicitWidth
    function selectColumn() {
        if (styleData.column === 0) {
            return rowColumn
        }
        if (styleData.column === 1) {
            return infoColumn
        }
        return textColumn
    }
    function pickLineColor() {
        if (styleData.row < 0) {
            return "white"
        }

        var line = modelData.Line(styleData.row);
        if (line.lineType === DiffLine.Addition) {
            return "#dcffdc"
        }
        if (line.lineType === DiffLine.Deletion) {
            return "#ffdcdc"
        }
        return "white"
    }

    color: pickLineColor()
    Text {
        id: itemText
        font.family: review.fixedFont.font
        font.pointSize: review.fixedFont.font.pointSize
        elide: styleData.elideMode
        text: styleData.value !== undefined ? styleData.value.toString() : ""
    }
}
