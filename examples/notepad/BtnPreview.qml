import QtQuick 2.0
import QuickKeyboard 1.0
import ".."

WindowsFrame {
	id: preview

	property bool hasPreview: true

	property Item content
	property Item keyboard
	property Item btn

	property int backgroundBorder: 25
	property int padding: 10

	property int centeredX: -width / 2 + btn.width / 2 + btn.x
	property int minX: 0
	property int maxX: btn.parent.width - width

	state: "default"

	x: Math.max(Math.min(centeredX, maxX), minX)
	y: btn.y - height * 1.3
	width: buttonContent.width
	height: buttonContent.height
	visible: (previewItems.count + symbolsItems.count > 0) && hasPreview

	Component {
		id: textPreview
		Text {
			id: labelPreview
			property bool active: (index == currentSymbolIndex) || (currentSymbolIndex == -1)
			text: modelData.label == undefined ? modelData : modelData.label
			width: Math.max(contentWidth, contentHeight) / (modelData.label == undefined ? 1.4 : 1.0)
			horizontalAlignment: Text.AlignHCenter
			color: "black"
			font.pixelSize: btn.height
			opacity: active ? 1.0 : 0.6
			transform: Scale {
				xScale: active ? 1.0 : 0.6
				yScale: xScale
				origin.x: width / 2
				origin.y: height / 2
				Behavior on xScale {
					NumberAnimation {}
				}
			}
		}
	}

	Item {
		id: buttonContent
		height: chars.height; width: chars.width
		Row {
			id: chars
			Repeater {
				id: previewItems
				model: 0
				delegate: textPreview
			}
			Repeater {
				id: symbolsItems
				model: 0
				delegate: textPreview
			}
		}

		MouseArea {
			id: buttonsArea
			anchors.fill: parent
			onPressed: preview.state = "symbols"
			onReleased: btn.triggered()
			onPositionChanged: {
				var underMouseIndex = Math.floor(mouse.x * symbolsItems.count / chars.width);
				if (underMouseIndex < 0) {
					underMouseIndex = 0;
				}
				if (underMouseIndex >= symbolsItems.count) {
					underMouseIndex = symbolsItems.count - 1;
				}
				currentSymbolIndex = underMouseIndex;
			}
		}
	}

	Timer {
		interval: 800
		running: mouseDown && symbols.length > 1
		onTriggered: btn.GridLayout.layout.redirectEventsToItem(buttonsArea)
	}

	states: [
		State {
			name: "preview"
			PropertyChanges { target: previewItems; visible: true; model: [{'label': label}] }
		},
		State {
			name: "symbols"
			PropertyChanges { target: symbolsItems; visible: true; model: symbols }
		}
	]

	Component.onCompleted: {
		if (symbols) {
			state = "preview";
		}
	}
}
