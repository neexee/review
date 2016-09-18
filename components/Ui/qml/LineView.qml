import QtQuick 2.1
import diffline 1.0

Component {
    id: lineDelegate
    Rectangle {
        id: lineRectangle
        height: 20
        width: parent.width
        function pickLineColor(modelColor) {
            if (modelColor === DiffLine.Addition)
                return "#dcffdc"
            if (modelColor === DiffLine.Deletion)
                return "#ffdcdc"
            return "white"
        }
        color: pickLineColor(model.modelData.lineType)
        Text {
            text: model.modelData.text
        }
    }
}
