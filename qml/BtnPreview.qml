import QtQuick 2.0
import QuickKeyboard 1.0

import QtGraphicalEffects 1.0

Item {
	id: preview

	property bool hasPreview: true

	property Item content
	property Item keyboard
	property Item btn

	property int backgroundBorder: 25
	property int padding: 10

	property int centeredX: -width / 2 + btn.width / 2 + btn.x
	property int minX: - backgroundBorder
	property int maxX: btn.parent.width - width + backgroundBorder

	state: "default"

	x: Math.max(Math.min(centeredX, maxX), minX)
	y: btn.y - height + backgroundBorder
	width: buttonContent.width + backgroundBorder * 2 + padding * 2
	height: buttonContent.height + backgroundBorder * 2 + padding * 2
	visible: (previewItems.count + symbolsItems.count > 0) && hasPreview

	ShaderEffectSource {
		id: contentBlurSource
		visible: content != undefined
		sourceItem: content
		sourceRect: Qt.rect(preview.x + backgroundBorder, preview.y + keyboardOverlay.y + backgroundBorder, buttonContent.width, buttonContent.height)
	}

	FastBlur {
		source: contentBlurSource
		visible: content != undefined
		anchors.fill: parent
		anchors.margins: backgroundBorder
		radius: 32
	}

	ShaderEffectSource {
		id: keyboardBlurSource
		visible: content != undefined
		sourceItem: keyboard
		sourceRect: Qt.rect(preview.x + backgroundBorder, preview.y + backgroundBorder, buttonContent.width + padding * 2, buttonContent.height + padding * 2)
	}

	FastBlur {
		source: keyboardBlurSource
		visible: content != undefined
		anchors.fill: parent
		anchors.margins: backgroundBorder
		radius: 32
	}

	BorderImage {
		property int borderSize: backgroundBorder + 1

		anchors.fill: parent
		source: "qrc:/gfx/quickkeyboard/preview_bg.png"
		border { left: borderSize; top: borderSize; right: borderSize; bottom: borderSize }
	}

	Component {
		id: textPreview
		Text {
			id: labelPreview
			property bool active: (index == currentSymbolIndex) || (currentSymbolIndex == -1)
			text: modelData.label == undefined ? modelData : modelData.label
			width: Math.max(contentWidth, contentHeight) / (modelData.label == undefined ? 1.4 : 1.0)
			horizontalAlignment: Text.AlignHCenter
			color: "white"
			font.pixelSize: btn.height
			font.weight: Font.Bold
			style: Text.Raised; styleColor: "#000000"
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
		x: backgroundBorder + padding; y: backgroundBorder + padding
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
