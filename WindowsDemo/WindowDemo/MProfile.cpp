#include <QPainter>
#include "MProfile.h"
#include "common.h"
MProfile::MProfile(QWidget *parent) : QWidget(parent)
{
	state = new QPushButton(this);
	state->setIcon(QIcon(QPixmap("../WindowDemo/image/status/inline.png")));
	//state->setText(QStringLiteral("�˵�"));
	state->setGeometry(QRect(105, 65, 15, 15));//background:rgb(247, 247, 247);
	state->setStyleSheet("QPushButton{background:transparent; border:none;}\
						  QPushButton:hover{ background:rgb(200, 200, 200); }\
						  QPushButton:pressed{ background:rgb(180, 180, 180); }");//background-image:url(../WindowDemo/image/status/Qme.png);

	menu = new QMenu;
	menu->addAction(QIcon(QPixmap("../WindowDemo/image/status/inline.png")), QString::fromLocal8Bit("��������"));
	menu->addAction(QIcon(QPixmap("../WindowDemo/image/status/Qme.png")), QString::fromLocal8Bit("Q�Ұ�"));
	menu->addSeparator();
	menu->addAction(QIcon(QPixmap("../WindowDemo/image/status/unline.png")), QString::fromLocal8Bit("�뿪"));
	menu->addAction(QIcon(QPixmap("../WindowDemo/image/status/busy.png")), QString::fromLocal8Bit("æµ"));
	menu->addAction(QIcon(QPixmap("../WindowDemo/image/status/disturb.png")), QStringLiteral("�������"));
	menu->addSeparator();
	menu->addAction(QIcon(QPixmap("../WindowDemo/image/status/Stealth.png")), QStringLiteral("����"));
	menu->setStyleSheet("QMenu{background:rgb(247, 247, 247);} \
						 QMenu::Item:selected{background:rgb(25, 172, 227);}");
	state->setMenu(menu);
	this->setFixedHeight(80);
	this->setMinimumWidth(130);
	this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	connect(state, SIGNAL(clicked()), this, SLOT(showStateMemu()));
	connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(changeState(QAction*)));
}
/**********************************************************/
/* ����ͷ��                                               */
/**********************************************************/
void MProfile::setProfile(QPixmap pic)
{
	profile = pic;
	repaint();
}
//�޸�״̬
void MProfile::changeState(QAction * action)
{
	state->setIcon(action->icon());
}
void MProfile::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.drawPixmap(40, 0, profile);
	QPixmap mask("../WindowDemo/image/mask.png");//��������ͼ�� :/IrregularForm/Resources/mask.png
	painter.drawPixmap(2, 0, mask);
}
void MProfile::showStateMemu() 
{
	//menu->show();
}
MProfile::~MProfile()
{

}
