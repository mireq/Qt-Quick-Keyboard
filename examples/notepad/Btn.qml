import QtQuick 2.0
import QuickKeyboard 1.0
import ".."

Button {
	id: btn
	property int row
	property int col
	property Item buttonPreview
	property bool hasPreview: true
	GridLayout.row: row
	GridLayout.col: col
	GridLayout.colSpan: 2
	GridLayout.rowSpan: 2
	width: 50
	height: 50

	WindowsFrame {
		borderStyle: mouseDown || active ? "sunken" : "raised"
		thin: mouseDown ? true : false
		bgColor: active ? "#dcd8d0" : "#d4d0c8"
		anchors { fill: parent; margins: 1 }
	}

	Text {
		text: label
		color: "black"
		anchors {
			verticalCenter: parent.verticalCenter
			left: parent.left
			right: parent.right
			leftMargin: 5
			rightMargin: 5
		}
		font.pixelSize: parent.height / 2
		maximumLineCount: 1
		fontSizeMode: Text.Fit
		horizontalAlignment: Text.AlignHCenter
	}

	Component {
		id: buttonPreviewComponent
		BtnPreview {hasPreview: btn.hasPreview}
	}

	Timer {
		id: createPreviewTimer
		interval: 40

		onTriggered: {
			buttonPreview = buttonPreviewComponent.createObject(keyboardOverlay, {"btn": btn, "content": typeof(content) == "undefined" ? undefined: content, "keyboard": keyboard});
		}
	}

	onMouseDownChanged: {
		if (mouseDown) {
			createPreviewTimer.restart();
		}
		else {
			if (buttonPreview !== null) {
				buttonPreview.destroy();
				buttonPreview = null;
			}
			createPreviewTimer.stop();
		}
	}
}
