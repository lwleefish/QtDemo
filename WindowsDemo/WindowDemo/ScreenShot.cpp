#include "ScreenShot.h"

ScreenShot::ScreenShot(QPixmap pixMap)
{
	this->backgroundPixMap = pixMap;
	setWindowState(Qt::WindowFullScreen);
	
	setCursor(Qt::CrossCursor);
	setMouseTracking(true);
	//this->setAttribute(Qt::WA_TranslucentBackground, true);
}

void ScreenShot::loadBackground()
{
}
void ScreenShot::beginDrag(QPoint& P)
{
	AtRectPos pos = getPosAtRect(P);
	switch (pos)
	{
	case AtNone:
		break;
	case AtLeftTop:
	{
		currentState = BeginCapture;
		selectedRect = QRect(selectedRect.bottomRight(), selectedRect.bottomRight());
		beginScreenShotPoint = selectedRect.bottomRight();
	}
	break;
	case AtTop:
		break;
	case AtRightTop:
	{
		currentState = BeginCapture;
		selectedRect = QRect(selectedRect.bottomLeft(), selectedRect.bottomLeft());
		beginScreenShotPoint = selectedRect.bottomLeft();
	}
		break;
	case AtRight:
		break;
	case AtRightBottom:
	{
		currentState = BeginCapture;
		selectedRect = QRect(selectedRect.topLeft(), selectedRect.topLeft());
		beginScreenShotPoint = selectedRect.topLeft();
	}
		break;
	case AtBottom:
		break;
	case AtLeftBottom:
	{
		currentState = BeginCapture;
		selectedRect = QRect(selectedRect.topRight(), selectedRect.topRight());
		beginScreenShotPoint = selectedRect.topRight();
	}
		break;
	case AtLeft:
		break;
	default:
		break;
	}
}
/************************************************************************/
/* 鼠标事件                                                             */
/************************************************************************/
void ScreenShot::mousePressEvent(QMouseEvent *e)
{
	if (e->buttons() == Qt::RightButton)
	{
		if (currentState == Init)
		{
			this->close();
		}
		else 
		{
			currentState = Init;
			selectedRect = QRect(0, 0, 0, 0);
			update();
			return;
		}
	}
	if (e->buttons() == Qt::LeftButton)
	{
		switch (currentState)
		{
		case Init:
			currentState = BeginCapture;
			selectedRect = QRect(e->pos(), e->pos());
			beginScreenShotPoint = e->pos();
			break;
		case BeginCapture:
			break;
		case FinishCapture:
			if (selectedRect.contains(e->pos()))
			{
				currentState = BeginMove;
				beginMovePoint = e->pos();
			}
			else {
				beginDrag(e->pos());
			}
			break;
		case BeginMove:
			break;
		case BeginDrag:
			break;
		default:
			break;
		}
	}
}
void ScreenShot::mouseDoubleClickEvent(QMouseEvent * event)
{
	this->close();
}
void ScreenShot::mouseReleaseEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		switch (currentState)
		{
		case Init:
			break;
		case BeginCapture:
			currentState = FinishCapture;
			break;
		case FinishCapture:
			break;
		case BeginMove:
			currentState = FinishCapture;
			break;
		case BeginDrag:
			break;
		default:
			break;
		}
	}
}
void ScreenShot::mouseMoveEvent(QMouseEvent * event)
{
	if (event->buttons() == Qt::LeftButton)
	{
		switch (currentState)
		{
		case Init:
			break;
		case BeginCapture: {
			QPoint topL, bottomR;
			if (beginScreenShotPoint.x() <= event->x() && beginScreenShotPoint.y() <= event->y())
			{
				topL = beginScreenShotPoint;
				bottomR = event->pos();
			}
			else if (beginScreenShotPoint.x() <= event->x() && beginScreenShotPoint.y() > event->y())
			{
				topL = QPoint(beginScreenShotPoint.x(), event->y());
				bottomR = QPoint(event->x(), beginScreenShotPoint.y());
			}
			else if (beginScreenShotPoint.x() > event->x() && beginScreenShotPoint.y() <= event->y())
			{
				topL = QPoint(event->x(), beginScreenShotPoint.y());
				bottomR = QPoint(beginScreenShotPoint.x(), event->y());
			}
			else
			{
				topL = event->pos();
				bottomR = beginScreenShotPoint;
			}
			selectedRect = QRect(topL, bottomR);
		}
			break;
		case FinishCapture:
			break;
		case BeginMove:{
			int delta_x = 0, delta_y = 0;
			delta_x = event->x() - beginMovePoint.x();
			delta_y = event->y() - beginMovePoint.y();
			selectedRect = QRect(selectedRect.left() + delta_x, selectedRect.top() + delta_y, selectedRect.width(), +selectedRect.height());
			beginMovePoint = event->pos();
		}
			break;
		case BeginDrag:
			break;
		default:
			break;
		}
		update();
	}
	else if (event->button() == Qt::NoButton && currentState == FinishCapture)
	{
		if (selectedRect.contains(event->pos()))
		{
			this->setCursor(Qt::SizeAllCursor);
		}
		else {
			this->setCursor(Qt::CrossCursor);
			getPosAtRect(event->pos());
		}
	}
}
AtRectPos ScreenShot::getPosAtRect(QPoint& P)
{
	AtRectPos pos;
	int wid = 2;
	if (qAbs(P.x() - selectedRect.left()) <= wid)
	{
		pos = AtLeft;
		this->setCursor(Qt::SizeHorCursor);
		if (qAbs(P.y() - selectedRect.top()) <= wid)
		{
			pos = AtLeftTop;
			this->setCursor(Qt::SizeFDiagCursor);
		}
		if (qAbs(P.y() - selectedRect.bottom()) <= wid)
		{
			pos = AtLeftBottom;
			this->setCursor(Qt::SizeBDiagCursor);
		}
	}
	else if (qAbs(P.x() - selectedRect.right()) <= wid)
	{
		pos = AtRight;
		this->setCursor(Qt::SizeHorCursor);
		if (qAbs(P.y() - selectedRect.top()) <= wid)
		{
			pos = AtRightTop;
			this->setCursor(Qt::SizeBDiagCursor);
		}
		if (qAbs(P.y() - selectedRect.bottom()) <= wid)
		{
			pos = AtRightBottom;
			this->setCursor(Qt::SizeFDiagCursor);
		}
	}
	else if (qAbs(P.y() - selectedRect.top()) <= wid)
	{
		pos = AtTop;
		this->setCursor(Qt::SizeVerCursor);
	}
	else if (qAbs(P.y() - selectedRect.bottom()) <= wid)
	{
		pos = AtBottom;
		this->setCursor(Qt::SizeVerCursor);
	}
	return pos;
}
void ScreenShot::paintEvent(QPaintEvent * event)
{
	QColor color(0, 157, 217);  //选区边框
	QColor shadowColor(0, 0, 0, 100);  //阴影颜色设置
	//QPainter painter(this);
	painter.begin(this);
	painter.setPen(QPen(color, 2, Qt::SolidLine, Qt::FlatCap));
	painter.drawPixmap(0, 0, backgroundPixMap);
	/*******选区外阴影***********/
	if (selectedRect.left() > 0) {
		painter.fillRect(0, 0, selectedRect.left(), this->height(), shadowColor); //左
	}
	if (selectedRect.right() < this->width()) {
		painter.fillRect(selectedRect.right() + 1, 0, (this->width() - selectedRect.right()), this->height(), shadowColor); //右
	}
	if (selectedRect.top() > 0) {
		painter.fillRect(selectedRect.left(), 0, selectedRect.width(), selectedRect.top(), shadowColor); //上
	}
	if (selectedRect.bottom() < this->height()) {
		painter.fillRect(selectedRect.left(), selectedRect.bottom(), selectedRect.width(), (this->height() - selectedRect.bottom()), shadowColor); //下
	}
	//painter.fillRect(_x, _y, 0, 0, shadowColor); //画影罩效果
	painter.drawRect(QRect(selectedRect.left(), selectedRect.top(), selectedRect.width() - 1, selectedRect.height() - 1));
	painter.end();
}

ScreenShot::~ScreenShot()
{
}