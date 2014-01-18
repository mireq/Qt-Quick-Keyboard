import QtQuick 2.0
import QuickKeyboard 1.0

Item {
	width: 800; height: 480

	Image {
		id: background
		source: "qrc:/gfx/keyboard/bg.jpg"
		anchors.fill: parent
	}

	Keyboard {
		id: keyboard
		anchors { left: parent.left; right: parent.right; bottom: parent.bottom }
		height: Math.round(width / 3)

		BorderImage {
			anchors.fill: parent
			source: "qrc:/gfx/keyboard/keyboard_bg.png"
			border { left: 1; top: 12; right: 1; bottom: 1 }
		}

		mode: standard

		Mode {
			id: standard
			layout: Layout{ rows: 8; cols: 20 }
			anchors.fill: parent
			anchors.topMargin: 11

			Btn { col:  0; row: 0; label: "Q"; }
			Btn { col:  2; row: 0; label: "W"; }
			Btn { col:  4; row: 0; label: "E"; }
			Btn { col:  6; row: 0; label: "R"; }
			Btn { col:  8; row: 0; label: "T"; }
			Btn { col: 10; row: 0; label: "Y"; }
			Btn { col: 12; row: 0; label: "U"; }
			Btn { col: 14; row: 0; label: "I"; }
			Btn { col: 16; row: 0; label: "O"; }
			Btn { col: 18; row: 0; label: "P"; }

			Btn { col:  0; row: 2; label: "A"; }
			Btn { col:  2; row: 2; label: "S"; }
			Btn { col:  4; row: 2; label: "D"; }
			Btn { col:  6; row: 2; label: "F"; }
			Btn { col:  8; row: 2; label: "G"; }
			Btn { col: 10; row: 2; label: "H"; }
			Btn { col: 12; row: 2; label: "J"; }
			Btn { col: 14; row: 2; label: "K"; }
			Btn { col: 16; row: 2; label: "L"; }
			Btn { col: 18; row: 2; label: "⇦"; }

			Btn { col:  0; row: 4; label: "⇧"; }
			Btn { col:  2; row: 4; label: "Z"; }
			Btn { col:  4; row: 4; label: "X"; }
			Btn { col:  6; row: 4; label: "C"; }
			Btn { col:  8; row: 4; label: "V"; }
			Btn { col: 10; row: 4; label: "B"; }
			Btn { col: 12; row: 4; label: "N"; }
			Btn { col: 14; row: 4; label: "M"; }
			Btn { col: 16; row: 4; label: "´"; }
			Btn { col: 18; row: 4; label: "ˇ"; }

			Btn { col:  0; row: 6; Layout.colSpan: 5; label: "123"; }
			Btn { col:  5; row: 6; Layout.colSpan: 10; label: "Space"; }
			Btn { col: 15; row: 6; Layout.colSpan: 5; label: "⏎"; }

		}
	}
}
