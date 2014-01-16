import QtQuick 2.0

Rectangle {
	width: 800; height: 600
	color: "white"

	Rectangle {
		anchors.fill: input
		color: "#eee"
		border { width: 1; color: "gray" }
	}

	TextEdit {
		id: input
		anchors { top: parent.top; left: parent.left; right: parent.right; margins: 10 }
	}
}
