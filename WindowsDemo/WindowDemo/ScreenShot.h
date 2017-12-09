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
	QPoint beginScreenShotPoint;
	QPoint beginMovePoint;
	QLabel lbe_pos;
	//int _x = 0; //ѡ�����X
	//int _y = 0; //Y

private:
	void loadBackground();
	void beginDrag(QPoint&);
	AtRectPos getPosAtRect(QPoint&);
	/*********�¼�*******************/
	void mousePressEvent(QMouseEvent*);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
};


