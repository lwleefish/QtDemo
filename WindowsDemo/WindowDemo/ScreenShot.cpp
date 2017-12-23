#include "ScreenShot.h"
#define Min(X,Y) (X < Y ? X : Y)
ScreenShot::ScreenShot(QPixmap pixMap)
{
	this->backgroundPixMap = pixMap;
	lbe_pos = new QLabel(this);
	lbe_pos->setStyleSheet("color: white");
	setWindowState(Qt::WindowFullScreen);
	setCursor(Qt::CrossCursor);
	setMouseTracking(true);
	//this->setAttribute(Qt::WA_TranslucentBackground, true);
	//auto s = selectedRect.width() + "123";
	//QRect()
	
}

void ScreenShot::loadBackground()
{
}
void ScreenShot::beginDrag(QPoint& P)
{
	DragDirection = getPosAtRect(P);
	switch (DragDirection)
	{
	case AtNone:
		break;
	case AtLeftTop:
	{
		currentState = BeginCapture;
		selectedRect = QRect(selectedRect.bottomRight(), selectedRect.bottomRight());
		fixedPoint = selectedRect.bottomRight();
		break;
	}
	case AtTop:
	{
		currentState = BeginDrag;
		fixedPoint = selectedRect.bottomLeft();
		break;
	}
	case AtRightTop:
	{
		currentState = BeginCapture;
		selectedRect = QRect(selectedRect.bottomLeft(), selectedRect.bottomLeft());
		fixedPoint = selectedRect.bottomLeft();
		break;
	}
	case AtRight:
	{
		currentState = BeginDrag;
		fixedPoint = selectedRect.topLeft();
		break;
	}
	case AtRightBottom:
	{
		currentState = BeginCapture;
		selectedRect = QRect(selectedRect.topLeft(), selectedRect.topLeft());
		fixedPoint = selectedRect.topLeft();
		break;
	}
	case AtBottom:
	{
		currentState = BeginDrag;
		fixedPoint = selectedRect.topLeft();
		break;
	}
	case AtLeftBottom:
	{
		currentState = BeginCapture;
		selectedRect = QRect(selectedRect.topRight(), selectedRect.topRight());
		fixedPoint = selectedRect.topRight();
		break;
	}
	case AtLeft:
	{
		currentState = BeginDrag;
		fixedPoint = selectedRect.topRight();
		break;
	}
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
			lbe_pos->hide();
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
			fixedPoint = e->pos();
			lbe_pos->show();
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
		case BeginDrag: {
			currentState = FinishCapture;
			DragDirection = AtNone;
			break;
		}
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
			//int left_ = qMin(fixedPoint.x(), event->x());
			//int top_ = Min(fixedPoint.y(), event->y());
			//int width_ = qAbs(fixedPoint.x() - event->x());
			//int heigth_ = qAbs(fixedPoint.y() - event->y());
			//selectedRect = QRect(left_, top_, width_, heigth_);
			QPoint topL, bottomR;
			if (fixedPoint.x() <= event->x() && fixedPoint.y() <= event->y())
			{
				topL = fixedPoint;
				bottomR = event->pos();
			}
			else if (fixedPoint.x() <= event->x() && fixedPoint.y() > event->y())
			{
				topL = QPoint(fixedPoint.x(), event->y());
				bottomR = QPoint(event->x(), fixedPoint.y());
			}
			else if (fixedPoint.x() > event->x() && fixedPoint.y() <= event->y())
			{
				topL = QPoint(event->x(), fixedPoint.y());
				bottomR = QPoint(fixedPoint.x(), event->y());
			}
			else
			{
				topL = event->pos();
				bottomR = fixedPoint;
			}
			selectedRect = QRect(topL, bottomR);
			break;

		}
		case FinishCapture:
			break;
		case BeginMove: {
			int delta_x = 0, delta_y = 0;
			delta_x = event->x() - beginMovePoint.x();
			delta_y = event->y() - beginMovePoint.y();
			selectedRect = QRect(selectedRect.left() + delta_x, selectedRect.top() + delta_y, selectedRect.width(), +selectedRect.height());
			beginMovePoint = event->pos();
			break;
		}
		case BeginDrag:
			dragEvent(event->pos());
			break;
		default:
			break;
		}
		lbe_pos->setText(QString("%1,%2").arg(selectedRect.width()).arg(selectedRect.height()));
		lbe_pos->setGeometry(QRect(selectedRect.left(), selectedRect.top() - 15 > 0 ? selectedRect.top() - 15 : 0, 60, 15));
		//repaint();
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
void ScreenShot::dragEvent(QPoint& P)
{
	if (DragDirection == AtRight || DragDirection == AtLeft) {
		if (P.x() >= fixedPoint.x()){
			selectedRect = QRect(fixedPoint.x(), fixedPoint.y(), P.x() - fixedPoint.x(), selectedRect.height());
		} 
		else{
			selectedRect = QRect(P.x(), fixedPoint.y(),  fixedPoint.x() - P.x(), selectedRect.height());
		}
	}
	else if (DragDirection == AtTop || DragDirection == AtBottom) {
		if (P.y() >= fixedPoint.y()){
			selectedRect = QRect(fixedPoint.x(), fixedPoint.y(), selectedRect.width(), P.y() - fixedPoint.y());
		} 
		else{
			selectedRect = QRect(fixedPoint.x(), P.y(), selectedRect.width(), fixedPoint.y() - P.y());
		}
	}
}
AtRectPos ScreenShot::getPosAtRect(QPoint& P)
{
	AtRectPos pos = AtNone;
	int wid = 2;
	int left_ = selectedRect.left() - wid;
	int top_ = selectedRect.top() - wid;
	int width_ = selectedRect.width() + 2 * wid;
	int height_ = selectedRect.height() + 2 * wid;
	if (!QRect(left_, top_, width_, height_).contains(P)) {
		return pos;
	}
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
	QColor shadowColor(0, 0, 0, 120);  //阴影颜色设置
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
	delete lbe_pos;
}