import QtQuick 2.0
import QuickKeyboard 1.0
import ".."

Mode {
	signal standardModeSwitched

	Btn { col:  0; row: 0; label: "Q"; onTriggered: standardModeSwitched() }
}
