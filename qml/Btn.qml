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

			property int centeredX: -width / 2 + btn.width / 2 + btn.x
			property int minX: - 25
			property int maxX: btn.parent.width - width + 25

			x: Math.max(Math.min(centeredX, maxX), minX)
			y: btn.y - height
			width: buttonContent.width + 60; height: buttonContent.height + 60
			visible: active

			ShaderEffectSource {
				id: contentBlurSource
				sourceItem: content
				sourceRect: Qt.rect(preview.x + 25, preview.y + keyboardOverlay.y + 25, preview.width - 50, preview.height - 50)
			}

			FastBlur {
				source: contentBlurSource
				anchors.fill: parent
				anchors.margins: 25
				radius: 32
			}

			ShaderEffectSource {
				id: keyboardBlurSource
				sourceItem: keyboard
				sourceRect: Qt.rect(preview.x + 25, preview.y + 25, preview.width - 50, preview.height - 50)
			}

			FastBlur {
				source: keyboardBlurSource
				anchors.fill: parent
				anchors.margins: 25
				radius: 32
			}

			BorderImage {
				anchors.fill: parent
				source: "qrc:/gfx/keyboard/preview_bg.png"
				border { left: 26; top: 26; right: 26; bottom: 26 }
			}

			Item {
				id: buttonContent
				x: 30; y: 30
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
