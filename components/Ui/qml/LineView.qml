import QtQuick 2.1
import QtQuick.Layouts 1.0
import diffline 1.0

Component {
    id: lineDelegate
    RowLayout {
        height: 20
        width: parent.width
        spacing: 0
        Rectangle {
            Layout.fillHeight: true
            Layout.preferredWidth: 20
            color: lineRectangle.color
            Text {
                text: model.modelData.lineNumber
            }
        }
        Rectangle {
            Layout.fillHeight: true
            Layout.preferredWidth: 80
            color: lineRectangle.color
            Text {
                text: model.modelData.commit.Summary()
            }
        }
        Rectangle {
            id: lineRectangle
            Layout.fillHeight: true
            Layout.fillWidth: true
            function pickLineColor(modelColor) {
                if (modelColor === DiffLine.Addition)
                    return "#dcffdc"
                if (modelColor === DiffLine.Deletion)
                    return "#ffdcdc"
                return "white"
            }
            color: pickLineColor(model.modelData.lineType)
            TextEdit {
                text: model.modelData.text
                selectByMouse: true
                readOnly: true
            }
        }
    }
}
