#ifndef BUTTONITEM_H_VNF1QLCU
#define BUTTONITEM_H_VNF1QLCU

#include <QQuickItem>
#include <QStringList>

class ButtonItem: public QQuickItem
{
Q_OBJECT
Q_PROPERTY(bool pressed MEMBER m_pressed NOTIFY pressedChanged DESIGNABLE false)
Q_PROPERTY(bool modifier MEMBER m_modifier NOTIFY modifierChanged DESIGNABLE false)
Q_PROPERTY(QString label MEMBER m_label NOTIFY labelChanged)
Q_PROPERTY(QStringList symbols MEMBER m_symbols NOTIFY symbolsChanged)

// position
Q_PROPERTY(int col MEMBER m_col NOTIFY colChanged)
Q_PROPERTY(int row MEMBER m_row NOTIFY rowChanged)
Q_PROPERTY(int colSpan MEMBER m_colSpan NOTIFY colSpanChanged)
Q_PROPERTY(int rowSpan MEMBER m_rowSpan NOTIFY rowSpanChanged)
public:
	explicit ButtonItem(QQuickItem *parent = 0);
	~ButtonItem();

signals:
	void pressedChanged(bool is_pressed);
	void modifierChanged(bool is_modifier);
	void labelChanged(const QString &label);
	void symbolsChanged(const QStringList &symbols);

	void colChanged(int col);
	void rowChanged(int row);
	void colSpanChanged(int colSpan);
	void rowSpanChanged(int rowSpan);

private:
	bool m_pressed;
	bool m_modifier;
	QString m_label;
	QStringList m_symbols;
	int m_col;
	int m_row;
	int m_colSpan;
	int m_rowSpan;
}; /* -----  end of class ButtonItem  ----- */

#endif /* end of include guard: BUTTONITEM_H_VNF1QLCU */

