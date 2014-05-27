import QtQuick 2.0

Item {
	property alias text: text.text

	width: 800
	height: 18
	Canvas {
		contextType: "2d"
		antialiasing: false
		anchors.fill: parent
		onPaint: {
			context.reset();
			context.globalCompositeOperation = "source-over";
			var gradient = context.createLinearGradient(0, 0, width, height);
			gradient.addColorStop(0.0, "#0a246a");
			gradient.addColorStop(1.0, "#a6caf0");
			context.fillStyle = gradient;
			context.fillRect(0, 0, width, height);

		}
		onWidthChanged: requestPaint()
		onHeightChanged: requestPaint()
	}

	WindowsFrame {
		id: close
		thin: true
		borderStyle: closeMouse.pressed ? "sunken" : "raised"
		anchors {
			right: parent.right
			top: parent.top
			bottom: parent.bottom
			margins: 2
		}
		width: height + 1
		Canvas {
			contextType: "2d"
			antialiasing: false
			anchors.fill: parent
			anchors.margins: 3
			onPaint: {
				context.reset();
				context.globalCompositeOperation = "source-over";
				context.lineWidth = 1;
				context.strokeStyle = "#000000";

				context.beginPath();
				context.moveTo(0, 0);
				context.lineTo(width - 2, height -1);
				context.stroke();
				context.beginPath();
				context.strokeStyle = "#000000";
				context.moveTo(1, 0);
				context.lineTo(width - 1, height -1);
				context.stroke();

				context.beginPath();
				context.moveTo(width - 2, 0);
				context.lineTo(1, height -1);
				context.stroke();
				context.beginPath();
				context.strokeStyle = "#000000";
				context.moveTo(width - 1, 0);
				context.lineTo(0, height -1);
				context.stroke();
			}
			onWidthChanged: requestPaint()
			onHeightChanged: requestPaint()
		}

		MouseArea {
			id: closeMouse
			anchors.fill: parent
			onClicked: Qt.quit();
		}
	}

	Text {
		id: text
		anchors {
			left: parent.left
			right: close.left
			top: parent.top
			bottom: parent.bottom
		}
		anchors.margins: 2
		font.pixelSize: 12
		font.bold: true
		color: "#ffffff"
		elide: Text.ElideRight
	}
}
