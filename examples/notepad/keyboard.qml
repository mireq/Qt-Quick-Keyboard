import QtQuick 2.0
import QuickKeyboard 1.0
import "quickkeyboard/modes"

Item {
	id: kbd
	property bool isVisible: false
	property rect geometry: Qt.rect(keyboardRect.x, keyboardRect.y, keyboardRect.width, kbd.height - keyboardRect.y)
	width: parent.width; height: width / 3; anchors.bottom: parent.bottom
	//visible: isVisible

	WindowsFrame {
		id: keyboardRect
		width: parent.width; height: parent.height
	}

	Keyboard {
		id: keyboard
		mode: standard
		anchors { fill: keyboardRect; margins: 4 }

		Standard {
			id: standard
			anchors.fill: parent
			onSymbolsModeSwitched: keyboard.mode = symbols
		}

		Symbols {
			id: symbols
			anchors.fill: parent
			onStandardModeSwitched: keyboard.mode = standard
			onSymbolsModeSwitched: keyboard.mode = symbols2
		}

		Symbols2 {
			id: symbols2
			anchors.fill: parent
			onStandardModeSwitched: keyboard.mode = standard
			onSymbolsModeSwitched: keyboard.mode = symbols
		}
	}

	Item {
		id: keyboardOverlay
		anchors.fill: keyboard
	}

	states: [
		State {
			name: "visible"
			when: isVisible
			PropertyChanges { target: keyboardRect; y: 0  }
		},
		State {
			name: "hidden"
			when: !isVisible
			PropertyChanges { target: keyboardRect; y: kbd.height  }
		}
	]

	transitions: [
		Transition {
			to: "visible"
			NumberAnimation { properties: "y" }
		}
	]
}
