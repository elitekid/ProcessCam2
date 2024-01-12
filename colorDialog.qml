import QtQuick
import QtQuick.Window
import QtQuick.Controls.Fusion
import QtQuick.Dialogs

Window {
    
    width: 400
    height: 600
    visible: true
    id: root
    title: qsTr("Process Camera")

    ColorDialog {
        id: colorDialog
        title: "Font Color"
        selectedColor: settingManager.getFontColor()
        onAccepted: {
            settingManager.setFontColor(colorDialog.selectedColor);
            settingManager.setColorCode(colorDialog.selectedColor);
            fontColorButton.text = settingManager.getColorCode();
            fontColorButton.contentItem.color = settingManager.getFontColor();
            colorDialog.close()
        }
        onRejected: {
            console.log("Canceled")
            colorDialog.close()
        }
    }
}
