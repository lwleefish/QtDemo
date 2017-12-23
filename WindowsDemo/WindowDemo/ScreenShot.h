#pragma once
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QMouseEvent>
enum CaptureState
{
	Init,
	BeginCapture,
	FinishCapture,
	BeginMove,
	BeginDrag
};
enum AtRectPos //�ھ��ε�λ��
{
	AtNone,
	AtLeftTop,
	AtTop,
	AtRightTop,
	AtRight,
	AtRightBottom,
	AtBottom,
	AtLeftBottom,
	AtLeft
};
class ScreenShot : public QWidget
{
public:
	ScreenShot(QPixmap);
	virtual ~ScreenShot();

private:
	QPainter painter;
	QPixmap backgroundPixMap; //����ͼ
	QRect selectedRect = QRect(0, 0, 0, 0); //ѡ��
	CaptureState currentState = Init;
	QPoint fixedPoint;
	QPoint beginMovePoint;
	QLabel* lbe_pos;
	AtRectPos DragDirection;
	void loadBackground();
	void beginDrag(QPoint&);
	AtRectPos getPosAtRect(QPoint&);
	//int _x = 0; //ѡ�����X
	//int _y = 0; //Y

protected:
	void dragEvent(QPoint&);
	void mousePressEvent(QMouseEvent*);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
};


