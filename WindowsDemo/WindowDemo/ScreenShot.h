#pragma once
#include <QtWidgets>
class ScreenShot : public QWidget
{
public:
	ScreenShot();
	virtual ~ScreenShot();

private:
	void mousePressEvent(QMouseEvent*);
};

