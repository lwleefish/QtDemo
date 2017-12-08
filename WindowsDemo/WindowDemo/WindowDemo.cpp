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
	this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏 
	this->setGeometry(QRect(100, 700, 400, 200));//可设置窗口显示的方位与大小  
	//QPalette pal(titlebar->palette());
	//设置背景黑色
	//pal.setColor(QPalette::Background, Qt::blue);
	//titlebar->setAutoFillBackground(true);

	//titlebar->setPalette(pal);
	//this->setWindowOpacity(0.7);//设置透明1-全体透明  
	//this->setAttribute(Qt::WA_TranslucentBackground, true);//设置透明2-窗体标题栏不透明,背景透明  
	//this->resize(300, 300);//显示大小 
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
		this->showNormal(); //必须showNormal才能正常移动（？）
		QSize s(400, 200);
		this->resize(s);    //必须resize位置才能正常（？）
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
/*	截图                                                                */
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

