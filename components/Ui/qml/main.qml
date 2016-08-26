import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.0
import QtQuick.Window 2.1
import review.handler 1.0

ApplicationWindow {
    width: 640
    height: 480
    minimumWidth: 400
    minimumHeight: 300

    title: "Review prototype"

    ApplicationWindow {
        id: aboutBox

        width: 280
        height: 120
        title: "About Review"

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 8
            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Label {
                    anchors.centerIn: parent
                    horizontalAlignment: Text.AlignHCenter
                    text: "This is a graphical git-diff-blame implementation.\n 2016"
                }
            }
            Button {
                text: "Ok"
                isDefault: true
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                onClicked: aboutBox.close()
            }
            Keys.onReturnPressed: aboutBox.close()
            focus: true
        }
    }
    menuBar: MenuBar {
        Menu {
            title: "&File"
            MenuItem { text: "Quit"; onTriggered: Qt.quit() }
        }
        Menu {
            title: "&Help"
            MenuItem { text: "About..." ; onTriggered: aboutBox.show() }
        }
    }
    ToolBar {
        id: toolBar
        width: parent.width

        RowLayout {
            anchors.fill: parent
            SpinBox {
                id: fontSizeSpinBox
                implicitWidth: 50
                value: 0
                onValueChanged: reviewHandler.fontSize = value
            }
            Item { Layout.fillWidth: true }
        }
    }
    TextArea {
        Accessible.name: "reviewHandler"
        id: textArea
        frameVisible: false
        width: parent.width
        anchors.top: toolBar.bottom
        anchors.bottom: parent.bottom
        text: reviewHandler.text
        textFormat: Qt.PlainText
        Component.onCompleted: forceActiveFocus()
    }
    ReviewHandler {
        id: reviewHandler
        objectName: "reviewHandler"
        target: textArea
        cursorPosition: textArea.cursorPosition
        selectionStart: textArea.selectionStart
        selectionEnd: textArea.selectionEnd
        onFontSizeChanged: fontSizeSpinBox.value = reviewHandler.fontSize
    }
}
