#include <QFile>
#include "TitleBar.h"

TitleBar::TitleBar(QWidget *parent) : QWidget(parent)
{
	/*m_bar_minBtn->setText("min");
	m_bar_maxBtn->setText("mxn");
	m_bar_closeBtn->setText("close");*/
	
	m_bar_closeBtn.setIcon(QIcon(QPixmap("../WindowDemo/image/iconfont-guanbi.png")));
	m_bar_closeBtn.setIconSize(QSize(25, 25));
	m_bar_closeBtn.setFixedSize(QSize(25, 25));
	m_bar_closeBtn.setStyleSheet("QPushButton{background:transparent;border:none;}\
								  QPushButton:hover{background:red;}\
								  QPushButton:pressed{background:red}");
	m_bar_maxBtn.setIcon(QIcon(QPixmap("../WindowDemo/image/iconfont-zuidahua.png")));
	m_bar_maxBtn.setIconSize(QSize(25, 25));
	m_bar_maxBtn.setFixedSize(QSize(25, 25));
	m_bar_maxBtn.setStyleSheet("QPushButton{background:transparent;border:none;}\
								QPushButton:hover{background:lightblue;}\
								QPushButton:pressed{background:lightgreen}");

	m_bar_minBtn.setIcon(QIcon(QPixmap("../WindowDemo/image/iconfont-zuixiaohua.png")));
	m_bar_minBtn.setIconSize(QSize(25, 25));
	m_bar_minBtn.setFixedSize(QSize(25, 25));
	m_bar_minBtn.setStyleSheet("QPushButton{background:transparent;border:none; }\
								QPushButton:hover{color:lightgray;background:lightblue; }\
								QPushButton:pressed{background:lightgreen }");

	m_label.setText(QStringLiteral("´ïÄ¦"));
	m_label.setMargin(7);
	m_label.setStyleSheet("QLabel{font-style:italic;font-size:12px; color:lightblue}");

	m_bar_btnLayout.addWidget(&m_label, 0, Qt::AlignTop | Qt::AlignLeft);
	m_bar_btnLayout.addStretch();//Ìí¼ÓÀ©Õ¹
	m_bar_btnLayout.addWidget(&m_bar_minBtn, 0, Qt::AlignTop | Qt::AlignRight);
	m_bar_btnLayout.addWidget(&m_bar_maxBtn, 0, Qt::AlignTop | Qt::AlignRight);
	m_bar_btnLayout.addWidget(&m_bar_closeBtn, 0, Qt::AlignTop | Qt::AlignRight);
	m_bar_btnLayout.setContentsMargins(0, 0, 0, 0);
	
	
	this->setLayout(&m_bar_btnLayout);
	this->setFixedHeight(180);
	this->setMinimumWidth(400);
	this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	connect(&m_bar_closeBtn, SIGNAL(clicked()), this, SLOT(closeWindow()));
	connect(&m_bar_minBtn, SIGNAL(clicked()), this, SLOT(clickMinimize()));
	connect(&m_bar_maxBtn, SIGNAL(clicked()), this, SLOT(clickMaximize()));
}
void TitleBar::closeWindow()
{
	emit closeButtonclick(); 
}
void TitleBar::paintEvent(QPaintEvent *event)
{
	QFile file("../WindowDemo/image/u8_2.png");
	if (file.exists()) {
		QPainter painter(this);
		painter.drawPixmap(0, 0, width(), height(), QPixmap("../WindowDemo/image/u8_2.png"));
	}
	else {
		m_bar_closeBtn.setText("hello");
	}
}
TitleBar::~TitleBar()
{
}
