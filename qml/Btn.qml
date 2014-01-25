import QtQuick 2.0
import QuickKeyboard 1.0

import QtGraphicalEffects 1.0

Button {
	id: btn
	property int row
	property int col
	property Item buttonPreview
	GridLayout.row: row
	GridLayout.col: col
	GridLayout.colSpan: 2
	GridLayout.rowSpan: 2
	width: 50
	height: 50

	BorderImage {
		anchors.fill: parent
		source: active ? "qrc:/gfx/keyboard/btn_pressed.png" : "qrc:/gfx/keyboard/btn.png"
		border { left: 2; top: 2; right: 2; bottom: 2 }
	}

	Text {
		text: label
		color: "white"
		anchors {
			verticalCenter: parent.verticalCenter
			left: parent.left
			right: parent.right
			leftMargin: 5
			rightMargin: 5
		}
		font.pixelSize: parent.height / 2
		font.weight: Font.Bold
		style: Text.Raised; styleColor: "#000000"
		maximumLineCount: 1
		fontSizeMode: Text.Fit
		horizontalAlignment: Text.AlignHCenter
	}
	onTriggered: console.log(label)

	Component {
		id: buttonPreviewComponent
		Item {
			id: preview

			property Item content
			property Item keyboard
			property Item btn

			property int backgroundBorder: 25
			property int padding: 10

			property int centeredX: -width / 2 + btn.width / 2 + btn.x
			property int minX: - backgroundBorder
			property int maxX: btn.parent.width - width + backgroundBorder

			x: Math.max(Math.min(centeredX, maxX), minX)
			y: btn.y - height
			width: buttonContent.width + backgroundBorder * 2 + padding * 2
			height: buttonContent.height + backgroundBorder * 2 + padding * 2
			visible: active

			ShaderEffectSource {
				id: contentBlurSource
				sourceItem: content
				sourceRect: Qt.rect(preview.x + backgroundBorder, preview.y + keyboardOverlay.y + backgroundBorder, buttonContent.width * 2, buttonContent.height * 2)
			}

			FastBlur {
				source: contentBlurSource
				anchors.fill: parent
				anchors.margins: backgroundBorder
				radius: 32
			}

			ShaderEffectSource {
				id: keyboardBlurSource
				sourceItem: keyboard
				sourceRect: Qt.rect(preview.x + backgroundBorder, preview.y + backgroundBorder, buttonContent.width + padding * 2, buttonContent.height + padding * 2)
			}

			FastBlur {
				source: keyboardBlurSource
				anchors.fill: parent
				anchors.margins: backgroundBorder
				radius: 32
			}

			BorderImage {
				property int borderSize: backgroundBorder + 1

				anchors.fill: parent
				source: "qrc:/gfx/keyboard/preview_bg.png"
				border { left: borderSize; top: borderSize; right: borderSize; bottom: borderSize }
			}

			Item {
				id: buttonContent
				x: backgroundBorder + padding; y: backgroundBorder + padding
				height: labelPreview.height; width: Math.max(labelPreview.width, height)
				Text {
					id: labelPreview
					text: label
					color: "white"
					font.pixelSize: btn.height
					font.weight: Font.Bold
					anchors.horizontalCenter: parent.horizontalCenter
					style: Text.Raised; styleColor: "#000000"
				}
			}
		}
	}

	onActiveChanged: {
		if (active) {
			buttonPreview = buttonPreviewComponent.createObject(keyboardOverlay, {"btn": btn, "content": content, "keyboard": keyboard});
		}
		else {
			buttonPreview.destroy();
		}
	}

	Timer {
		interval: 800
		running: active
		onTriggered: console.log(btn.GridLayout.layout)
	}
}
