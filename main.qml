import QtQuick
import QtQuick.Window
import QtQuick.Controls.Fusion
import QtQuick.Dialogs

ApplicationWindow {
    width: 400
    height: 600
    visible: true
    color: "#224488"

    title: qsTr("Process Camera")

    Item {
        // 좌측 상단에 정렬
        anchors.top: parent.top
        anchors.left: parent.left

        Text {
            id: camList
            x: 20
            y: 20
            width: 60
            height: 30
            color: "#ffffff"
            verticalAlignment: Text.AlignVCenter
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            text: qsTr("Cam List")
            font.pixelSize: 14
        }

        ComboBox {
            id: comboBox
            textRole: "text"
            valueRole: "value"
            x: 90
            y: 20
            width: 180
            height: 30
            font.pointSize: 11
            model: cameraListModel.availableCameras;
            currentIndex: 0
            onActivated: function(index) { 
                comboBox.currentIndex = model[index].value;
            }
        }

        Text {
            id: fontColorLabel
            x: 20
            y: 65
            width: 90
            height: 30
            color: "#ffffff"
            verticalAlignment: Text.AlignVCenter
            font.bold: true
            horizontalAlignment: Text.AlignLeft
            text: qsTr("Font Color")
            font.pixelSize: 14
        }

        Button {
            id: fontColorButton
            x: 230
            y: 60
            width: 40
            height: 40
            text: qsTr(settingManager.getColorCode())
            font.weight: Font.ExtraBold 
            font.pointSize: 8
            transformOrigin: Item.Center
            contentItem: Text {
                text: fontColorButton.text
                font: fontColorButton.font
                color: settingManager.getFontColor()
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

            }
            background: Rectangle {
                color: "black"
            }
            onClicked: {
                colorDialog.visible = true
            }
        }

        ColorDialog {
            id: colorDialog
            title: "Font Color"
            selectedColor: settingManager.getFontColor()
            onAccepted: {
                settingManager.setFontColor(colorDialog.selectedColor);
                settingManager.setColorCode(colorDialog.selectedColor);
                fontColorButton.text = settingManager.getColorCode();
                fontColorButton.contentItem.color = settingManager.getFontColor();
            }
            onRejected: {
                console.log("Canceled")
            }
            visible: false
        }

        Button {
            id: button
            x: 300
            y: 20
            width: 80
            height: 80
            text: qsTr("Run")
            font.pointSize: 12
            onClicked: {
                camObj.showCam(comboBox.currentIndex, settingManager.getColorCode());
            }
        }
    }
}
