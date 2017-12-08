//#include <Windows.h>
#include <QDebug>
#include "windowdemo.h"
#include "screenshot.h"
#define Str QStringLiteral

WindowDemo::WindowDemo(QWidget *parent)
	: QWidget(parent)
{
	titlebar = new TitleBar(this);
	main_layout_v.addWidget(titlebar, 0, Qt::AlignTop);
	main_layout_v.setSpacing(0);
	main_layout_v.setMargin(0);
	
	qcapture.setText(Str("Capture"));
	main_layout_v.addWidget(&qcapture, 0, Qt::AlignBottom);
	this->setLayout(&main_layout_v);
	this->setWindowFlags(Qt::FramelessWindowHint);//ȥ�������� 
	this->setGeometry(QRect(100, 700, 400, 200));//�����ô�����ʾ�ķ�λ���С  
	//QPalette pal(titlebar->palette());
	//���ñ�����ɫ
	//pal.setColor(QPalette::Background, Qt::blue);
	//titlebar->setAutoFillBackground(true);

	//titlebar->setPalette(pal);
	//this->setWindowOpacity(0.7);//����͸��1-ȫ��͸��  
	//this->setAttribute(Qt::WA_TranslucentBackground, true);//����͸��2-�����������͸��,����͸��  
	//this->resize(300, 300);//��ʾ��С 
	connect(titlebar, SIGNAL(minimizeButtonClick()), this, SLOT(minWindow()));
	connect(titlebar, SIGNAL(maximizeButtonClick()), this, SLOT(maxWindow()));
	connect(titlebar, SIGNAL(closeButtonclick()), this, SLOT(closeWindow()));
	connect(titlebar, SIGNAL(titleMouseDown(QMouseEvent *)), this, SLOT(mouseClick(QMouseEvent *)));
	connect(titlebar, SIGNAL(titleMouseMove(QMouseEvent *)), this, SLOT(moveWindow(QMouseEvent *)));
	connect(&qcapture, SIGNAL(clicked()), this, SLOT(capture()));
	//WId Hwnd = this->winId();
	//QString s = "{\"key1\":12345678901,\"key2\":\"value2\"}";
	////QJsonObject obj = ;
	//QByteArray qa = s.toUtf8();
	//QJsonParseError *er = new QJsonParseError();
	//QJsonDocument qs = QJsonDocument::fromJson(qa, er);
	//QJsonObject qo = qs.object();
	//QJsonValue sss = qo["key1"];
	//long long d = (long long)sss.toDouble();
}
void WindowDemo::closeWindow()
{
	this->close();
}
void WindowDemo::maxWindow()
{
	if (this->isMaximized()) {
		this->showNormal();
	}
	else {
		this->showMaximized();
	}
}
void WindowDemo::minWindow()
{
	this->showMinimized();
}



void WindowDemo::paintEvent(QPaintEvent *)
{
	int jg = 3;
	QColor color(0, 157, 217);
	QPainter painter(this);
	//QPainterPath path;
	painter.setPen(QPen(color, jg, Qt::SolidLine));
	painter.drawRect(QRect(0, 0, this->width() - 1, this->height() - 1));
}
void WindowDemo::moveWindow(QMouseEvent *e) 
{
	if (e->buttons() != Qt::LeftButton) {
		return;
	}
	else if (isMaximized()){
		int maxWidth = this->width();
		this->showNormal(); //����showNormal���������ƶ�������
		QSize s(400, 200);
		this->resize(s);    //����resizeλ�ò�������������
		int normalWidth = this->width();
		//this->move((maxWidth - normalWidth) * (e->x() * 1.0 / maxWidth), 0); ------------*----
		this->move(e->x() * (1 - normalWidth * 1.0 / maxWidth), 0);//		   .........---*-   
	}
	else {
		QPoint delta = e->globalPos() - point_old;
		move(x() + delta.x(), y() + delta.y());
		point_old = e->globalPos();
	}
}
void WindowDemo::mouseClick(QMouseEvent *e) 
{
	if (e->buttons() == Qt::LeftButton) {
		point_old = e->globalPos();
	}
}
/************************************************************************/
/*	��ͼ                                                                */
/************************************************************************/
void WindowDemo::capture()
{
	QScreen *capture = QGuiApplication::primaryScreen();
	QPixmap background = capture->grabWindow(0);//.save("123.jpg", "jpg");
	ScreenShot *screen = new ScreenShot();
	screen->show();
}
WindowDemo::~WindowDemo()
{
	delete titlebar;
}

