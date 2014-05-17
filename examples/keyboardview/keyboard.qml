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

	Keyboard {
		id: keyboard
		anchors { left: parent.left; right: parent.right; bottom: parent.bottom }
		height: Math.round(width / 3)

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
