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
	Rectangle {
		color: "green"
		anchors.fill: parent
	}
	onTriggered: console.log(label)
}
