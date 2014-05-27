import QtQuick 2.0
import QuickKeyboard 1.0
import "quickkeyboard/modes"

WindowsFrame {
	id: kbd
	property bool isVisible: false
	property rect geometry
	width: parent.width; height: width / 3; anchors.bottom: parent.bottom
	visible: isVisible

	Keyboard {
		id: keyboard
		mode: standard
		anchors { fill: parent; margins: 4 }

		Standard {
			id: standard
			anchors.fill: parent
			onSymbolsModeSwitched: keyboard.mode = symbols
		}

		Symbols {
			id: symbols
			anchors.fill: parent
			onStandardModeSwitched: keyboard.mode = standard
		}
	}

	Item {
		id: keyboardOverlay
		anchors.fill: keyboard
	}
}
