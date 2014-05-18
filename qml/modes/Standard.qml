import QtQuick 2.0
import QuickKeyboard 1.0
import ".."

Mode {
	signal symbolsModeSwitched

	layout: GridLayout{ rows: 8; cols: 20 }
	Btn { col:  0; row: 0; label: "Q";
		symbols: shift.pressed ?
			["Q", "Ω"] :
			["q", "\\"]
	}
	Btn { col:  2; row: 0; label: "W";
		symbols: shift.pressed ?
			acute.pressed ? ["Ẃ"] : ["W", "Ŵ", "Ẁ", "Ẇ", "Ẃ", "Ẅ", "Ł"] :
			acute.pressed ? ["ẃ"] : ["w", "ŵ", "ẘ", "ẁ", "ẇ", "ẃ", "ẅ", "|"]
	}
	Btn { col:  4; row: 0; label: "E";
		symbols: shift.pressed ?
			acute.pressed ? ["É"] : (caron.pressed ? ["Ě"] : ["E", "Ẽ", "Ě", "Ê", "Ĕ", "Ę", "È", "Ė", "É", "Ë", "Ȩ"]) :
			acute.pressed ? ["é"] : (caron.pressed ? ["ě"] : ["e", "ě", "ê", "ĕ", "ę", "è", "ė", "é", "ë", "ȩ", "€"])
	}
	Btn { col:  6; row: 0; label: "R";
		symbols: shift.pressed ?
			acute.pressed ? ["Ŕ"] : (caron.pressed ? ["Ř"] : ["R", "Ř", "Ṙ", "Ŕ", "Ŗ", "®"]) :
			acute.pressed ? ["ŕ"] : (caron.pressed ? ["ř"] : ["r", "ř", "ṙ", "ŕ", "ŗ", "¶"])
	}
	Btn { col:  8; row: 0; label: "T"
		symbols: shift.pressed ?
			caron.pressed ? ["Ť"] : ["T", "Ť", "Ṫ", "Ţ", "Ŧ"] :
			caron.pressed ? ["ť"] : ["ť", "ṫ", "ẗ", "ţ", "ŧ"]
	}
	Btn { col: 10; row: 0; label: "Y";
		symbols: shift.pressed ?
			acute.pressed ? ["Ý"] : ["Y", "Ỹ", "Ŷ", "Ỳ", "Ẏ", "Ý", "Ÿ", "¥"] :
			acute.pressed ? ["ý"] : ["y", "ỹ", "ŷ", "ẙ", "ỳ", "ẏ", "ý", "ÿ", "←"]
	}
	Btn { col: 12; row: 0; label: "U";
		symbols: shift.pressed ?
			acute.pressed ? ["Ú"] : (caron.pressed ? ["Ǔ"] : ["U", "Ũ", "Ǔ", "Û", "Ŭ", "Ů", "Ų", "Ù", "Ú", "Ű", "Ü", "Ǚ", "Ǜ", "Ǘ", "↑"]) :
			acute.pressed ? ["ú"] : (caron.pressed ? ["ǔ"] : ["u", "ũ", "ǔ", "û", "ŭ", "ů", "ų", "ù", "ú", "ű", "ü", "ǚ", "ǜ", "ǘ", "↓"])
	}
	Btn { col: 14; row: 0; label: "I";
		symbols: shift.pressed ?
			acute.pressed ? ["Í"] : (caron.pressed ? ["Ǐ"] : ["I", "Ĩ", "Ǐ", "Î", "Ĭ", "Į", "Ì", "İ", "Í", "Ï", "ı"]) :
			acute.pressed ? ["í"] : (caron.pressed ? ["ǐ"] : ["i", "ĩ", "ǐ", "î", "ĭ", "į", "ì", "ı", "í", "ï", "→"])
	}
	Btn { col: 16; row: 0; label: "O";
		symbols: shift.pressed ?
			acute.pressed ? ["Ó"] : (caron.pressed ? ["Ǒ"] : ["O", "Õ", "Ǒ", "Ô", "Ŏ", "Ǫ", "Ò", "Ȯ", "Ó", "Ő", "Ö", "Ø"]) :
			acute.pressed ? ["ó"] : (caron.pressed ? ["ǒ"] : ["o", "õ", "ǒ", "ô", "ŏ", "ǫ", "ò", "ȯ", "ó", "ő", "ö", "ø"])
	}
	Btn { col: 18; row: 0; label: "P";
		symbols: shift.pressed ?
			acute.pressed ? ["Ṕ"] : ["P", "Ṗ", "Ṕ", "Þ"] :
			acute.pressed ? ["ṕ"] : ["p", "ṗ", "ṕ", "þ"]
	}
	Btn { col:  0; row: 2; label: "A";
		symbols: shift.pressed ?
			acute.pressed ? ["Á"] : (caron.pressed ? ["Ǎ"] : ["A", "Ã", "Ǎ", "Â", "Ă", "Å", "Ą", "À", "Ȧ", "Á", "Ä", "Æ"]) :
			acute.pressed ? ["á"] : (caron.pressed ? ["Ǎ"] : ["a", "ã", "ǎ", "â", "ă", "å", "ą", "à", "ȧ", "á", "ä", "~"])
	}
	Btn { col:  2; row: 2; label: "S";
		symbols: shift.pressed ?
			acute.pressed ? ["Ś"] : (caron.pressed ? ["Š"] : ["S", "Š", "Ŝ", "Ṡ", "Ś", "Ş", "§"]) :
			acute.pressed ? ["ś"] : (caron.pressed ? ["š"] : ["s", "š", "ŝ", "ṡ", "ś", "ş", "đ"])
	}
	Btn { col:  4; row: 2; label: "D";
		symbols: shift.pressed ?
			caron.pressed ? ["Ď"] : ["D", "Ď", "Ḋ", "Ḑ", "Đ"] :
			caron.pressed ? ["ď"] : ["d", "ď", "ḋ", "ḑ", "đ"]
	}
	Btn { col:  6; row: 2; label: "F";
		symbols: shift.pressed ?
			["F", "Ḟ", "ª"] : ["f", "ḟ", "["]
	}
	Btn { col:  8; row: 2; label: "G";
		symbols: shift.pressed ?
			acute.pressed ? ["Ǵ"] : (caron.pressed ? ["Ǧ"] : ["G", "Ǧ", "Ĝ", "Ğ", "Ġ", "Ǵ", "Ģ", "Ŋ"]) :
			acute.pressed ? ["ǵ"] : (caron.pressed ? ["ǧ"] : ["g", "ǧ", "ĝ", "ğ", "ġ", "ǵ", "ģ", "]"])
	}
	Btn { col: 10; row: 2; label: "H";
		symbols: shift.pressed ?
			caron.pressed ? ["Ȟ"] : ["H", "Ȟ", "Ĥ", "Ḣ", "Ḧ", "Ḩ", "Ħ"] :
			caron.pressed ? ["ȟ"] : ["h", "ȟ", "ĥ", "ḣ", "ḧ", "ḩ", "`"]
	}
	Btn { col: 12; row: 2; label: "J";
		symbols: shift.pressed ?
			["J", "Ĵ", "J́", "'"] :
			caron.pressed ? ["ǰ"] : ["j", "ǰ", "ĵ", "ȷ", " ̛"]
	}
	Btn { col: 14; row: 2; label: "K";
		symbols: shift.pressed ?
			acute.pressed ? ["Ḱ"] : (caron.pressed ? ["Ǩ"] : ["K", "Ǩ", "Ḱ", "Ķ", "&"]) :
			acute.pressed ? ["ḱ"] : (caron.pressed ? ["ǩ"] : ["k", "ǩ", "ḱ", "ķ", "ł"])
	}
	Btn { col: 16; row: 2; label: "L";
		symbols: shift.pressed ?
			acute.pressed ? ["Ĺ"] : (caron.pressed ? ["Ľ"] : ["L", "Ľ", "Ŀ", "Ĺ", "Ļ", "Ł"]) :
			acute.pressed ? ["ĺ"] : (caron.pressed ? ["ľ"] : ["l", "ľ", "ŀ", "ĺ", "ļ", "Ł"])
	}
	Btn { col: 18; row: 2; label: "⇦"; hasPreview: false }

	Btn { col:  0; row: 4; label: "⇧"; id: shift; modifier: true; hasPreview: false }
	Btn { col:  2; row: 4; label: "Z";
		symbols: shift.pressed ?
			acute.pressed ? ["Ź"] : (caron.pressed ? ["Ž"] : ["Z", "Ž", "Ẑ", "Ż", "Ź", "<"]) :
			acute.pressed ? ["ź"] : (caron.pressed ? ["ž"] : ["z", "ž", "ẑ", "ż", "ź", "°"])
	}
	Btn { col:  4; row: 4; label: "X";
		symbols: shift.pressed ?
			["X", "Ẋ", "Ẍ", ">"] : ["x", "ẋ", "ẍ", "#"]
	}
	Btn { col:  6; row: 4; label: "C";
		symbols: shift.pressed ?
			acute.pressed ? ["Ć"] : (caron.pressed ? ["Č"] : ["C", "Č", "Ĉ", "Ċ", "Ć", "Ç", "©"]) :
			acute.pressed ? ["ć"] : (caron.pressed ? ["č"] : ["c", "č", "ĉ", "ċ", "ć", "ç", "&"])
	}
	Btn { col:  8; row: 4; label: "V";
		symbols: shift.pressed ?
			["V", "Ṽ", "‘"] : ["v", "ṽ", "@"]
	}
	Btn { col: 10; row: 4; label: "B";
		symbols: shift.pressed ?
			["B", "Ḃ", "’"] : ["b", "ḃ", "{"]
	}
	Btn { col: 12; row: 4; label: "N";
		symbols: shift.pressed ?
			acute.pressed ? ["Ń"] : (caron.pressed ? ["Ň"] : ["N", "Ñ", "Ň", "Ǹ", "Ṅ", "Ń", "Ņ"]) :
			acute.pressed ? ["ń"] : (caron.pressed ? ["ň"] : ["n", "ñ", "ň", "ǹ", "ṅ", "ń", "ņ", "}"])
	}
	Btn { col: 14; row: 4; label: "M";
		symbols: shift.pressed ?
			acute.pressed ? ["Ḿ"] : ["M", "Ṁ", "Ḿ", "º"] :
			acute.pressed ? ["ḿ"] : ["m", "ṁ", "ḿ", "^"]
	}
	Btn { col: 16; row: 4; label: "´"; id: acute; modifier: true; hasPreview: false; onActiveChanged: if (active) caron.active = false }
	Btn { col: 18; row: 4; label: "ˇ"; id: caron; modifier: true; hasPreview: false; onActiveChanged: if (active) acute.active = false }

	Btn { col:  0; row: 6; GridLayout.colSpan: 5; label: "12#"; onTriggered: symbolsModeSwitched(); hasPreview: false }
	Btn { col:  5; row: 6; GridLayout.colSpan: 10; label: "Space"; hasPreview: false }
	Btn { col: 15; row: 6; label: shift.pressed ? "," : ".";
		symbols: shift.pressed ?
			[",", ".", ":", ";", "!", "?"] : [".", ",", ":", ";", "!", "?"]
	}
	Btn { col: 17; row: 6; GridLayout.colSpan: 3; label: "⏎"; hasPreview: false }
}
