#include <QPainter>
#include "MProfile.h"
#include "common.h"
MProfile::MProfile(QWidget *parent) : QWidget(parent)
{
	state = new QPushButton(this);
	state->setIcon(QIcon(QPixmap("../WindowDemo/image/status/inline.png")));
	//state->setText(QStringLiteral("菜单"));
	state->setGeometry(QRect(105, 65, 15, 15));//background:rgb(247, 247, 247);
	state->setStyleSheet("QPushButton{background:transparent;}\
						QPushButton:hover{background-image:url(../WindowDemo/image/status/inline.png);}");//QPushButton::menu-indicator { \
						subcontrol-position: right center;\
						subcontrol-origin: padding;\
						padding-right: 3px;\
					    image: none;}
	menu = new QMenu;
	menu->addAction(QIcon(QPixmap("../WindowDemo/image/status/inline.png")), QString::fromLocal8Bit("我在线上"));
	menu->addAction(QIcon(QPixmap("../WindowDemo/image/status/Qme.png")), QString::fromLocal8Bit("Q我吧"));
	menu->addSeparator();
	menu->addAction(QIcon(QPixmap("../WindowDemo/image/status/unline.png")), QString::fromLocal8Bit("离开"));
	menu->addAction(QIcon(QPixmap("../WindowDemo/image/status/busy.png")), QString::fromLocal8Bit("忙碌"));
	menu->addAction(QIcon(QPixmap("../WindowDemo/image/status/disturb.png")), QStringLiteral("请勿打扰"));
	menu->addSeparator();
	menu->addAction(QIcon(QPixmap("../WindowDemo/image/status/Stealth.png")), QStringLiteral("隐身"));
	menu->setStyleSheet("QMenu{background:rgb(247, 247, 247);}");
	state->setMenu(menu);
	this->setFixedHeight(80);
	this->setMinimumWidth(130);
	this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	bool b = connect(state, SIGNAL(clicked()), this, SLOT(showStateMemu()));
}
/**********************************************************/
/* 设置头像                                               */
/**********************************************************/
void MProfile::setProfile(QPixmap pic)
{
	profile = pic;
	repaint();
}
void MProfile::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.drawPixmap(40, 0, profile);
	QPixmap mask("../WindowDemo/image/mask.png");//加载掩码图像 :/IrregularForm/Resources/mask.png
	painter.drawPixmap(2, 0, mask);

}
void MProfile::showStateMemu() 
{
	//menu->show();
}
MProfile::~MProfile()
{

}
