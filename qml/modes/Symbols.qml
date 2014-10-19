import QtQuick 2.0
import QuickKeyboard 1.0
import ".."

Mode {
	signal standardModeSwitched
	signal symbolsModeSwitched

	Btn { col:  0; row: 0; label: "1"; symbols: ["1"] }
	Btn { col:  2; row: 0; label: "2"; symbols: ["2"] }
	Btn { col:  4; row: 0; label: "3"; symbols: ["3"] }
	Btn { col:  6; row: 0; label: "4"; symbols: ["4"] }
	Btn { col:  8; row: 0; label: "5"; symbols: ["5"] }
	Btn { col: 10; row: 0; label: "6"; symbols: ["6"] }
	Btn { col: 12; row: 0; label: "7"; symbols: ["7"] }
	Btn { col: 14; row: 0; label: "8"; symbols: ["8"] }
	Btn { col: 16; row: 0; label: "9"; symbols: ["9"] }
	Btn { col: 18; row: 0; label: "0"; symbols: ["0"] }

	Btn { col:  0; row: 2; label: "-"; symbols: ["-"] }
	Btn { col:  2; row: 2; label: "/"; symbols: ["/"] }
	Btn { col:  4; row: 2; label: ":"; symbols: [":"] }
	Btn { col:  6; row: 2; label: ";"; symbols: [";"] }
	Btn { col:  8; row: 2; label: "("; symbols: ["("] }
	Btn { col: 10; row: 2; label: ")"; symbols: [")"] }
	Btn { col: 12; row: 2; label: "€"; symbols: ["€"] }
	Btn { col: 14; row: 2; label: "&"; symbols: ["&"] }
	Btn { col: 16; row: 2; label: "@"; symbols: ["@"] }
	Btn { col: 18; row: 2; label: "⇦"; hasPreview: false; symbols: ["\x7f"] }

	Btn { col:  0; row: 4; GridLayout.colSpan: 4; label: "#<"; hasPreview: false; onTriggered: symbolsModeSwitched(); }
	Btn { col:  4; row: 4; label: "\""; symbols: ["\""] }
	Btn { col:  6; row: 4; label: "'"; symbols: ["'"] }
	Btn { col:  8; row: 4; label: "."; symbols: ["."] }
	Btn { col: 10; row: 4; label: ","; symbols: [","] }
	Btn { col: 12; row: 4; label: "?"; symbols: ["?"] }
	Btn { col: 14; row: 4; label: "!"; symbols: ["!"] }
	Btn { col: 16; row: 4; label: "*"; symbols: ["*"] }
	Btn { col: 18; row: 4; label: "%"; symbols: ["%"] }

	Btn { col:  0; row: 6; GridLayout.colSpan: 5; label: "ABC"; onTriggered: standardModeSwitched(); hasPreview: false }
	Btn { col:  5; row: 6; GridLayout.colSpan: 10; label: "Space"; hasPreview: false; symbols: " " }
	Btn { col: 15; row: 6; GridLayout.colSpan: 5; label: "⏎"; hasPreview: false; symbols: "\n" }
}
