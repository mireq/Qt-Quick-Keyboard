import QtQuick 2.0

Item {
	property color bgColor: "#d4d0c8"
	property color glossColor: "#ffffff"
	property color shadowLightColor: "#808080"
	property color shadowDarkColor: "#404040"
	property string borderStyle: "raised"
	property bool thin: false

	width: 16
	height: 16
	Canvas {
		id: canvas
		contextType: "2d"
		antialiasing: false
		anchors.fill: parent
		onPaint: {
			var glossLight;
			var glossDark;
			var shadowLight;
			var shadowDark;

			if (borderStyle == "raised") {
				glossLight = glossColor;
				glossDark = bgColor;
				shadowLight = shadowLightColor;
				shadowDark = shadowDarkColor;
			}
			else if (borderStyle == "sunken") {
				glossLight = shadowDarkColor;
				glossDark = shadowLightColor;
				shadowLight = glossColor;
				shadowDark = bgColor;
			}

			context.reset();
			context.globalCompositeOperation = "source-over";
			context.fillStyle = bgColor;
			context.fillRect(0, 0, width, height);

			context.lineWidth = 1;

			context.beginPath();
			if (thin) {
				context.strokeStyle = glossLight;
			}
			else {
				context.strokeStyle = glossDark;
			}
			context.moveTo(0.5, height - 1);
			context.lineTo(0.5, 0);
			context.moveTo(0, 0.5);
			context.lineTo(width - 1, 0.5);
			context.stroke();

			context.beginPath();
			if (thin) {
				context.strokeStyle = bgColor;
			}
			else {
				context.strokeStyle = glossLight;
			}
			context.moveTo(1.5, height - 2);
			context.lineTo(1.5, 1);
			context.moveTo(1, 1.5);
			context.lineTo(width - 2, 1.5);
			context.stroke();

			context.beginPath();
			context.strokeStyle = shadowDark;
			context.moveTo(0, height - 0.5);
			context.lineTo(width, height - 0.5);
			context.moveTo(width - 0.5, height);
			context.lineTo(width - 0.5, 0);
			context.stroke();

			context.beginPath();
			context.strokeStyle = shadowLight;
			context.moveTo(1, height - 1.5);
			context.lineTo(width - 1, height - 1.5);
			context.moveTo(width - 1.5, height - 1);
			context.lineTo(width - 1.5, 1);
			context.stroke();
		}
		onWidthChanged: requestPaint()
		onHeightChanged: requestPaint()
	}

	onBgColorChanged: canvas.requestPaint()
	onGlossColorChanged: canvas.requestPaint()
	onShadowLightColorChanged: canvas.requestPaint()
	onShadowDarkColorChanged: canvas.requestPaint()
	onBorderStyleChanged: canvas.requestPaint()
	onThinChanged: canvas.requestPaint()
}
