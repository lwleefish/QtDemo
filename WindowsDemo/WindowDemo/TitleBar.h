#pragma once

#include <QPushButton>
#include <QHBoxLayout>
#include <QPainter>
#include <QLabel>
#include "qwidget.h"

class WindowDemo;
class TitleBar : public QWidget
{
	Q_OBJECT
public:
	//TitleBar(WindowDemo *parent);
	TitleBar(QWidget *parent);
	~TitleBar();

signals:
	void closeButtonclick();
	void minimizeButtonClick();
	void maximizeButtonClick();
	void titleMouseDown(QMouseEvent *e);
	void titleMouseMove(QMouseEvent *e);
protected:
	virtual void paintEvent(QPaintEvent *e);
	virtual void mousePressEvent(QMouseEvent *e) { emit titleMouseDown(e); }
	virtual void mouseMoveEvent(QMouseEvent *e) { emit titleMouseMove(e); }
private slots:
	void closeWindow();
	void clickMinimize() { emit minimizeButtonClick(); }
	void clickMaximize() { emit maximizeButtonClick(); }
private:
	QPushButton m_bar_minBtn;
	QPushButton m_bar_maxBtn;
	QPushButton m_bar_closeBtn;
	QLabel m_label;
	QHBoxLayout m_bar_btnLayout;
};

