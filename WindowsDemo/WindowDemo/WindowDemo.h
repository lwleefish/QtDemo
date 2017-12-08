#pragma once

#include <QtWidgets>
#include <QVBoxLayout>
#include "titlebar.h"

class WindowDemo : public QWidget
{
    Q_OBJECT

public:
    WindowDemo(QWidget *parent = Q_NULLPTR);
	~WindowDemo();

protected:
	virtual void paintEvent(QPaintEvent*);
private slots:
	void closeWindow();
	void maxWindow();
	void minWindow();
	void moveWindow(QMouseEvent *e);
	void mouseClick(QMouseEvent *e);
	void capture();
private:
	QVBoxLayout main_layout_v;
	TitleBar *titlebar;
	QPoint point_old;
	QPushButton qcapture;
};
