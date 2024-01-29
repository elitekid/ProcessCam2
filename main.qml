import QtQuick
import QtQuick.Window
import QtQuick.Controls.Fusion
import QtQuick.Dialogs

ApplicationWindow {
    width: 400
    height: 350
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
            text: qsTr("Camera")
            font.pixelSize: 14
        }

        ComboBox {
            id: camListComboBox
            textRole: "text"
            valueRole: "value"
            x: 100
            y: 20
            width: 180
            height: 30
            font.pointSize: 11
            model: camera_list_model.available_cameras;
            currentIndex: setting_manager.GetCamera();
            onActivated: { 
                const index = camListComboBox.currentIndex;
                setting_manager.SetCamera(index);
            }
        }

        Text {
            id: fontListLabel
            x: 20
            y: 55
            width: 90
            height: 30
            color: "#ffffff"
            verticalAlignment: Text.AlignVCenter
            font.bold: true
            horizontalAlignment: Text.AlignLeft
            text: qsTr("Font")
            font.pixelSize: 14
        }

        ComboBox {
            id: fontLIstComboBox
            textRole: "text"
            valueRole: "value"
            x: 100
            y: 60
            width: 130
            height: 20
            font.pointSize: 8
            model: font_list_model.font_list;
            currentIndex: font_list_model.GetIndexByText(setting_manager.GetFont());
            onActivated: {
                const index = fontLIstComboBox.currentIndex;
                const comboList = font_list_model.GetItem(index);

                setting_manager.SetFont(comboList.text);
                setting_manager.SetFontPath(comboList.value);

                fontExample.font.family = comboList.text;
            }
        }

        Text {
            id: fontColorLabel
            x: 20
            y: 80
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
            id: fontColorDialog
            x: 100
            y: 90
            width: 130
            height: 10
            transformOrigin: Item.Center
            background: Rectangle {
                color: setting_manager.GetFontColor()
            }
            onClicked: {
                colorDialog.visible = true
            }
        }

        Button {
            id: fontExample
            x: 240
            y: 60
            width: 40
            height: 40
            text: qsTr(setting_manager.GetColorCode())
            font.weight: Font.ExtraBold 
            font.pointSize: 8
            font.family: setting_manager.GetFont()
            transformOrigin: Item.Center
            contentItem: Text {
                text: fontExample.text
                font: fontExample.font
                color: setting_manager.GetFontColor()
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                color: "black"
            }
        }

        ColorDialog {
            id: colorDialog
            title: "Font Color"
            selectedColor: setting_manager.GetFontColor()
            onAccepted: {
                const colorCode = colorDialog.selectedColor;
                setting_manager.SetFontColor(colorCode);
                setting_manager.SetColorCode(colorCode);
                fontColorDialog.background.color = setting_manager.GetFontColor();
                fontExample.text = setting_manager.GetColorCode();
                fontExample.contentItem.color = setting_manager.GetFontColor();
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
                qt_camera.ShowCam();
            }
        }

        // Line
        Rectangle {
            id: dividingLine
            x: 20
            y: 120
            width: 360
            height: 2
            color: "#ffffff"
        }

        Text {
            id: screenModeLabel
            x: 20
            y: 130
            width: 90
            height: 30
            color: "#ffffff"
            verticalAlignment: Text.AlignVCenter
            font.bold: true
            horizontalAlignment: Text.AlignLeft
            text: qsTr("Full Screen Mode")
            font.pixelSize: 14
        }

        CheckBox {
            id: screenModeCheckBox
            x: 135
            y: 130
            checked: setting_manager.GetFullScreenMode()
            onCheckedChanged: {
                setting_manager.SetFullScreenMode(checked)
            }
        }
    }
}
