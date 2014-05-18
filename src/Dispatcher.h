#ifndef DISPATCHER_H_4JJ7SBUO
#define DISPATCHER_H_4JJ7SBUO

#include <QObject>

class Dispatcher: public QObject
{
Q_OBJECT
public:
	explicit Dispatcher(QObject *parent = 0);
	~Dispatcher();
	QObject *focusObject() const;

public slots:
	void setFocusObject(QObject *focusObject);
	virtual void sendSymbol(const QString &symbol);

private:
	QObject *m_focusObject;
}; /* -----  end of class Dispatcher  ----- */

#endif /* end of include guard: DISPATCHER_H_4JJ7SBUO */

