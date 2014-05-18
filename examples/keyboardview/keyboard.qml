import QtQuick 2.0
import QuickKeyboard 1.0
import "modes"

import QtGraphicalEffects 1.0

Item {
	id: main
	width: 800; height: 480

	Image {
		id: content
		source: "qrc:/gfx/keyboard/bg.jpg"
		anchors.fill: parent
	}

	BorderImage {
		source: "qrc:/gfx/keyboard/panel_bg.png"
		height: childrenRect.height + 40
		border { left: 9; top: 9; right: 9; bottom: 9 }
		anchors {
			left: parent.left
			right: parent.right
			top: parent.top
			margins: 20
		}

		TextEdit {
			id: textInput
			font.pixelSize: 30
			color: "white"
			anchors { left: parent.left; right: parent.right; top: parent.top; margins: 20 }
			clip: true
		}
	}

	Keyboard {
		id: keyboard
		anchors { left: parent.left; right: parent.right; bottom: parent.bottom }
		height: Math.round(width / 3)

		Component.onCompleted: keyboard.dispatcher.setFocusObject(textInput)

		ShaderEffectSource {
			id: contentBlurSource
			sourceItem: content
			sourceRect: Qt.rect(keyboard.x, keyboard.y + 11, keyboard.width, keyboard.height - 11)
		}

		FastBlur {
			source: contentBlurSource
			anchors.fill: keyboard
			anchors.topMargin: 11
			radius: 32
		}

		BorderImage {
			anchors.fill: parent
			source: "qrc:/gfx/keyboard/keyboard_bg.png"
			border { left: 1; top: 12; right: 1; bottom: 1 }
		}

		mode: standard

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
