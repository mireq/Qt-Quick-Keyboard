import QtQuick 2.0

Rectangle {
	width: 800
	height: 480
	color: "#3a6ea5"

	WindowsFrame {
		anchors {
			left: parent.left
			top: parent.top
			right: parent.right
			bottom: keyboardArea.top
			margins: 10
		}
		WindowTitle {
			id: windowTitle
			text: "Notepad.exe"
			anchors {
				left: parent.left
				right: parent.right
				top: parent.top
				margins: 4
			}
		}
		WindowsFrame {
			borderStyle: "sunken"
			anchors {
				top: windowTitle.bottom
				left: parent.left
				right: parent.right
				bottom: parent.bottom
				margins: 4
			}
			Rectangle {
				color: "white"
				anchors.fill: parent
				anchors.margins: 2
				TextEdit {
					anchors { fill: parent; margins: 2 }
				}
			}
		}
	}

	Item {
		id: keyboardArea
		anchors { left: parent.left; right: parent.right; bottom: parent.bottom }
		height: Qt.inputMethod === undefined ? 1 : Qt.inputMethod.keyboardRectangle.height
	}
}

