import QtQuick 2.0
import QuickKeyboard 1.0

Button {
	property int row
	property int col
	Layout.row: row
	Layout.col: col
	Layout.colSpan: 2
	Layout.rowSpan: 2
	width: 50
	height: 50

	BorderImage {
		anchors.fill: parent
		source: parent.active ? "qrc:/gfx/keyboard/btn_pressed.png" : "qrc:/gfx/keyboard/btn.png"
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
}
