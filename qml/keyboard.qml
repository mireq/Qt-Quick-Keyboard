import QtQuick 2.0
import QuickKeyboard 1.0
import "modes"

import QtGraphicalEffects 1.0

Item {
	id: kbd
	property bool isVisible: false
	property rect geometry: Qt.rect(keyboardRect.x, keyboardRect.y, keyboardRect.width, kbd.height - keyboardRect.y)
	width: parent.width; height: width / 3; anchors.bottom: parent.bottom

	Item {
		id: keyboardRect
		width: parent.width; height: parent.height
	}

	Keyboard {
		id: keyboard
		mode: standard
		anchors.fill: keyboardRect

		BorderImage {
			anchors.fill: parent
			source: "qrc:/gfx/quickkeyboard/keyboard_bg.png"
			border { left: 1; top: 12; right: 1; bottom: 1 }
		}

		Standard {
			id: standard
			anchors.fill: parent
			anchors.topMargin: 11
			onSymbolsModeSwitched: keyboard.mode = symbols
		}

		Symbols {
			id: symbols
			anchors.fill: parent
			anchors.topMargin: 11
			onStandardModeSwitched: keyboard.mode = standard
			onSymbolsModeSwitched: keyboard.mode = symbols2
		}

		Symbols2 {
			id: symbols2
			anchors.fill: parent
			anchors.topMargin: 11
			onStandardModeSwitched: keyboard.mode = standard
			onSymbolsModeSwitched: keyboard.mode = symbols
		}
	}

	Item {
		id: keyboardOverlay
		anchors.fill: keyboardRect
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
