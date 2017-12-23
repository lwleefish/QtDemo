#include <QGuiApplication>
#include <QScreen>
#include <QDebug>
#include <kernelspecs.h>
#include "windowdemo.h"
#include "screenshot.h"
#include "common.h"
#include "QDesktopServices"
#include <stdio.h>
#include <windows.h>

#define HEAD_BM  0x4D42
#define HEAD_PNG 0x5089
#define HEAD_GFT1 0x4754
#define HEAD_GFT2 0x0046
#define Str QStringLiteral

bool isEndWith(char *path, char* ext)
{
	return !stricmp(path + strlen(path) - strlen(ext), ext);
}
void ChangeExt(char *path, char* ext)
{
	int i = strlen(path);
	int j = strlen(ext);
	for (; j > 0; j--)
	{
		path[i--] = ext[j];
	}
}
WindowDemo::WindowDemo(QWidget *parent)
	: QWidget(parent)
{
	initLayout();
	this->setLayout(main_layout_v);
	this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏 
	this->setGeometry(QRect(100, 700, Common::window_width, Common::window_height));//可设置窗口显示的方位与大小  
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
	connect(qcapture, SIGNAL(clicked()), this, SLOT(capture()));
	connect(reg, SIGNAL(clicked()), this, SLOT(reghref()));
	connect(findpwd, SIGNAL(clicked()), this, SLOT(findpwdhref()));
	connect(pTrailingAction, SIGNAL(triggered(bool)), this, SLOT(openKeyBoard(bool)));
	connect(autologin, SIGNAL(stateChanged(int)), this, SLOT(checkedChange(int)));
	connect(rememberpwd, SIGNAL(stateChanged(int)), this, SLOT(checkedChange(int)));
	connect(login, SIGNAL(clicked()), this, SLOT(checkPassword()));
	//register_key_hook();
	//QMap<int, QString> map;
	
}
//密码确认
void WindowDemo::checkPassword()
{
	if (te_password->text() == "123546" && cbx_username->currentText() == "666666") {
		qDebug() << Str("登陆成功");
		return;
	}
	qDebug() << Str("密码错误");
}
void WindowDemo::checkedChange(int state)
{
	QCheckBox *cb = qobject_cast<QCheckBox *>(sender());
	if (cb->property("distinguish") == "rememberpwd" && !cb->isChecked()) {
		autologin->setChecked(false);
	}
	else if (cb->property("distinguish") == "autologin"  &&autologin->checkState() == Qt::Checked){
		rememberpwd->setCheckState(Qt::Checked);
	}
}
void WindowDemo::openKeyBoard(bool checked)
{
	QString strText = te_password->text();
	qcapture->setText(QString::fromLocal8Bit("输入内容为：%1").arg(strText));
}

//用默认浏览器打开注册链接
void WindowDemo::reghref()
{
	QString url = "https://ssl.zc.qq.com/v3/index-chs.html";
	QDesktopServices::openUrl(QUrl(url.toLatin1()));
}

void WindowDemo::findpwdhref()
{
	QString url = "https://aq.qq.com/v2/uv_aq/html/reset_pwd/pc_reset_pwd_input_account.html";
	QDesktopServices::openUrl(QUrl(url.toLatin1()));
}

void WindowDemo::initLayout()
{
	main_layout_v = new QVBoxLayout;
	titlebar = new TitleBar(this); //title
	profile = new MProfile();
	grid_layout = new QGridLayout;
	cbx_username = new QComboBox;
	cbx_username->addItem("123456");
	cbx_username->addItem("666666");
	cbx_username->setEditable(true);
	cbx_username->setFixedWidth(190);
	cbx_username->setFixedHeight(30);
	cbx_username->setStyleSheet("QComboBox{font-size: 15px;} ");
	
	te_password = new QLineEdit;
	te_password->setEchoMode(QLineEdit::Password);
	te_password->setFixedWidth(190);
	te_password->setFixedHeight(30);
	//te_password->setStyleSheet("QLineEdit{icon-size: 28px;}");//QLineEdit{border: 1px solid blue}
	te_password->setPlaceholderText(Str("密码"));
	pTrailingAction = te_password->addAction(QIcon("../WindowDemo/image/keyboard3.png"), QLineEdit::TrailingPosition);
	
	reg = new QPushButton;
	reg->setText(Str("注册账号"));
	reg->setFixedWidth(60);
	reg->setFixedHeight(30);
	reg->setStyleSheet("QPushButton{ background: transparent; border: none; color: rgb(0, 109, 176);}\
						QPushButton:hover{ background: rgb(230, 237, 244); color: rgb(31, 141, 231);}\
						QPushButton:pressed{background:transparent; color: rgb(0, 109, 176);}");//235, 242, 249

	findpwd = new QPushButton;
	findpwd->setText(Str("找回密码"));
	findpwd->setFixedWidth(60);
	findpwd->setFixedHeight(30);
	findpwd->setWindowState(Qt::WindowState::WindowNoState);
	findpwd->setStyleSheet("QPushButton{background: transparent;border:none; color: rgb(0, 109, 176);}\
						QPushButton:hover{background:rgb(230, 237, 244); color: rgb(31, 141, 231);}\
						QPushButton:pressed{background:transparent; color: rgb(0, 109, 176);}");
	rememberpwd = new QCheckBox;
	rememberpwd->setMinimumHeight(30);
	rememberpwd->setText(QStringLiteral("记住密码"));
	rememberpwd->setStyleSheet("QCheckBox{color:rgb(101, 101, 101);}");
	rememberpwd->setProperty("distinguish", "rememberpwd");

	autologin = new QCheckBox;
	autologin->setText(QStringLiteral("自动登录"));
	autologin->setStyleSheet("QCheckBox{color:rgb(101, 101, 101);}");
	autologin->setProperty("distinguish", "autologin");

	check_layout_h = new QHBoxLayout;
	check_layout_h->addWidget(rememberpwd, 0, Qt::AlignLeft);
	check_layout_h->addWidget(autologin, 0, Qt::AlignRight);
	
	login = new QPushButton;
	login->setText(Str("登录"));
	login->setFixedSize(QSize(195, 30));
	login->setStyleSheet("QPushButton{background:rgb(25, 172, 227);border:none;color:white;border-radius: 3px;}\
						  QPushButton:hover{background: rgb(55, 202, 255);border:none;}\
						  QPushButton:pressed{background:rgb(25, 172, 227);}");//rgb(55, 202, 257)
	main_layout_v->addWidget(titlebar, 0, Qt::AlignTop);
	main_layout_v->setSpacing(0);
	main_layout_v->setMargin(0);
	grid_layout->setMargin(10);
	grid_layout->addWidget(profile, 0, 0, 3, 1, Qt::AlignLeft);
	grid_layout->addWidget(cbx_username, 0, 1, Qt::AlignLeft);
	grid_layout->addWidget(reg, 0, 2, Qt::AlignLeft);
	grid_layout->addWidget(te_password, 1, 1, Qt::AlignLeft);
	grid_layout->addWidget(findpwd, 1, 2, Qt::AlignLeft);
	grid_layout->addLayout(check_layout_h, 2, 1);
	grid_layout->addWidget(login, 3, 1);
	//grid_layout->addWidget(autologin, 2, 2, Qt::AlignLeft);
	
	//main_layout_h.addWidget(&lbe_pic, 0, Qt::AlignLeft);
	//main_layout_h.addLayout(&login_layout_v, 0);
	//main_layout_h.addWidget(&);
	//main_layout_h.addWidget();
	
	main_layout_v->addLayout(grid_layout);
	qcapture = new QPushButton;
	qcapture->setText(Str("Capture"));
	main_layout_v->addWidget(qcapture, 0, Qt::AlignBottom);
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

/*************************************************
  重绘边框                                                             
*************************************************/
void WindowDemo::paintEvent(QPaintEvent *)
{
	int jg = 3;
	QColor color(0, 157, 217);
	QPainter painter(this);
	//painter.setPen(QPen(OUT_Of_CIRCLE_COLOR, 2, Qt::SolidLine, Qt::FlatCap));
	painter.fillRect(0, 0, Common::window_width, Common::window_height, OUT_Of_CIRCLE_COLOR);
	//painter.setBackground(QBrush)
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
		QSize s(Common::window_width, Common::window_height);
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
	ScreenShot *screen = new ScreenShot(background);
	screen->show();
}
//int translate(int argc, char *argv[])
//{
//	if (argc == 1)
//	{
//		//MessageBox(0, "请将要转换的图片拖动到本程序上。", "提示", MB_OK + MB_ICONINFORMATION);
//		return 0;
//	}
//
//	for (int index = 1; index < argc; index++)
//	{
//		FILE *fp, *out;
//		fp = fopen(argv[index], "rb");
//		if (fp != NULL)
//		{
//			if (isEndWith(argv[index], ".gft"))
//			{
//				fseek(fp, 0, SEEK_END);
//				long length = ftell(fp);
//				fseek(fp, 0x10, SEEK_SET);
//				int offset = fgetc(fp);
//				fseek(fp, offset, SEEK_SET);
//				switch (fgetwc(fp))
//				{
//				case HEAD_BM:
//					ChangeExt(argv[index], ".bmp");
//					break;
//				case HEAD_PNG:
//					ChangeExt(argv[index], ".png");
//					break;
//				}
//				fseek(fp, offset, SEEK_SET);
//				out = fopen(argv[index], "wb");
//				while (ftell(fp) != length)
//				{
//					fputc(fgetc(fp), out);
//				}
//				fclose(out);
//			}
//			else
//			{
//				fseek(fp, 0, SEEK_END);
//				long length = ftell(fp);
//				fseek(fp, 0, SEEK_SET);
//
//				ChangeExt(argv[index], ".gft");
//				out = fopen(argv[index], "wb");
//				fputwc(HEAD_GFT1, out);
//				fputwc(HEAD_GFT2, out);
//				for (int fill = 0; fill < 6; fill++)
//				{
//					fputwc(0, out);
//				}
//				fputwc(20, out);
//				fputwc(0, out);
//				while (ftell(fp) != length)
//				{
//					fputc(fgetc(fp), out);
//				}
//				fclose(out);
//			}
//		}
//		fclose(fp);
//	}
//	//MessageBox(0, "恭喜你，全部图片转换完成。", "提示", MB_OK + MB_ICONINFORMATION);
//}
WindowDemo::~WindowDemo()
{
	delete titlebar;
	delete profile;
	//unregister_key_hook();
}


