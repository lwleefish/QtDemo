#pragma once
#include "qwidget.h"
#include <QPushButton>
#include <QMenu>
class MProfile : public QWidget
{
	Q_OBJECT
public:
	void setProfile(QPixmap);
	MProfile(QWidget *parent = 0);
	~MProfile();
protected:
	void paintEvent(QPaintEvent *);
private slots:
	void showStateMemu();
private: 
	QPushButton *state;
	QMenu *menu;
	QPixmap profile = QPixmap("../WindowDemo/image/QQ.png");
};

