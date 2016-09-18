import QtQuick 2.1

Component {
    Rectangle {
        height: fileView.count * 20
        width: parent.width

        ListView {
            id: fileView
            anchors.fill: parent
            orientation: Qt.Vertical
            model: modelData.diffLines
            delegate: lineDelegate
        }
        LineView {
            id: lineDelegate
        }
    }
}
