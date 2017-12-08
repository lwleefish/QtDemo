#include "ScreenShot.h"

ScreenShot::ScreenShot()
{
	setWindowState(Qt::WindowFullScreen);
	
	//setCursor(Qt::CrossCursor);
	//this->setAttribute(Qt::WA_TranslucentBackground, true);
}

void ScreenShot::mousePressEvent(QMouseEvent *e)
{
	if (e->buttons() == Qt::RightButton) {
		this->close();
	}
}

ScreenShot::~ScreenShot()
{

}