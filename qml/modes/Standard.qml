import QtQuick 2.0
import QuickKeyboard 1.0
import ".."

Mode {
	signal symbolsModeChanged

	layout: GridLayout{ rows: 8; cols: 20 }
	Btn { col:  0; row: 0; label: "Q";
		symbols: shift.active ?
			["Q", "Ω"] :
			["q", "\\"]
	}
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
	Btn { col: 18; row: 2; label: "⇦"; hasPreview: false }

	Btn { col:  0; row: 4; label: "⇧"; id: shift; modifier: true; hasPreview: false }
	Btn { col:  2; row: 4; label: "Z"; }
	Btn { col:  4; row: 4; label: "X"; }
	Btn { col:  6; row: 4; label: "C"; }
	Btn { col:  8; row: 4; label: "V"; }
	Btn { col: 10; row: 4; label: "B"; }
	Btn { col: 12; row: 4; label: "N"; }
	Btn { col: 14; row: 4; label: "M"; }
	Btn { col: 16; row: 4; label: "´"; id: acute; modifier: true; hasPreview: false }
	Btn { col: 18; row: 4; label: "ˇ"; id: caron; modifier: true; hasPreview: false }

	Btn { col:  0; row: 6; GridLayout.colSpan: 5; label: "123"; onTriggered: symbolsModeChanged(); hasPreview: false }
	Btn { col:  5; row: 6; GridLayout.colSpan: 10; label: "Space"; hasPreview: false }
	Btn { col: 15; row: 6; GridLayout.colSpan: 5; label: "⏎"; hasPreview: false }
}
