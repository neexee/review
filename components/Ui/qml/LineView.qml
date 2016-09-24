import QtQuick 2.1
import QtQuick.Layouts 1.0
import diffline 1.0

Rectangle {
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
        elide: styleData.elideMode
        text: styleData.value !== undefined ? styleData.value.toString() : ""
    }
}
