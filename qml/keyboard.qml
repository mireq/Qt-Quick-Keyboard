import QtQuick 2.0
import QuickKeyboard 1.0

Keyboard {
	width: 200; height: 100
	Mode {
		id: standard
		anchors.fill: parent
		Btn{ col: 0; row: 0; label: "A"; symbols: ["A"] }
		Btn{ col: 3; row: 3; label: "B"; symbols: ["B"] }
		Btn{ col: 5; row: 5; label: "C"; symbols: ["C"] }
	}
	mode: standard
}
