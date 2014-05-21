import QtQuick 2.0
import QuickKeyboard 1.0
import "modes"

import QtGraphicalEffects 1.0

Rectangle {
	id: kbd
	property bool isVisible: false
	property rect geometry
	width: parent.width; height: width / 3; anchors.bottom: parent.bottom
	visible: isVisible
	Keyboard {
		id: keyboard
		mode: standard
		anchors.fill: parent

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
		}
	}

	Item {
		id: keyboardOverlay
		anchors.fill: keyboard
	}
}
