import QtQuick 2.0
import QuickKeyboard 1.0

import QtGraphicalEffects 1.0

Button {
	id: btn
	property int row
	property int col
	property Item buttonPreview
	GridLayout.row: row
	GridLayout.col: col
	GridLayout.colSpan: 2
	GridLayout.rowSpan: 2
	width: 50
	height: 50

	BorderImage {
		anchors.fill: parent
		source: active ? "qrc:/gfx/keyboard/btn_pressed.png" : "qrc:/gfx/keyboard/btn.png"
		border { left: 2; top: 2; right: 2; bottom: 2 }
	}

	Text {
		text: label
		color: "white"
		anchors {
			verticalCenter: parent.verticalCenter
			left: parent.left
			right: parent.right
			leftMargin: 5
			rightMargin: 5
		}
		font.pixelSize: parent.height / 2
		font.weight: Font.Bold
		style: Text.Raised; styleColor: "#000000"
		maximumLineCount: 1
		fontSizeMode: Text.Fit
		horizontalAlignment: Text.AlignHCenter
	}
	onTriggered: console.log(label)

	Component {
		id: buttonPreviewComponent
		BtnPreview {}
	}

	onActiveChanged: {
		if (active) {
			buttonPreview = buttonPreviewComponent.createObject(keyboardOverlay, {"btn": btn, "content": content, "keyboard": keyboard});
		}
		else {
			buttonPreview.destroy();
		}
	}

	Timer {
		interval: 800
		running: active
		onTriggered: console.log(btn.GridLayout.layout)
	}
}
