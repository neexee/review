import QtQuick 2.6
import QtQuick.Layouts 1.0
import diffline 1.0

Rectangle {
    implicitWidth: textBackground.implicitWidth + 2 * columnSeparator.width
    implicitHeight: textBackground.implicitHeight
    Rectangle {
        id: textBackground

        anchors.left: parent.left
        anchors.right: columnSeparator.left
        anchors.top: parent.top

        height: parent.height
        implicitWidth: itemText.contentWidth
        implicitHeight: itemText.implicitHeight
        border.width: 0

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
            leftPadding: 0
            padding: 0
            anchors.left: parent.left
            anchors.right: parent.right
            horizontalAlignment: styleData.column === 1 ?  Text.AlignRight:  Text.AlignLeft
            text: styleData.value !== undefined ? styleData.value.toString() : ""
        }
    }
    Rectangle {
        id: columnSeparator
        width: 2
        color: "#204a87"
        height: parent.height
        anchors.right: parent.right
    }
}
