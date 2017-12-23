#pragma once

#include <QWidget>
#include "ui_gui.h"

class gui : public QWidget
{
	Q_OBJECT

public:
	gui(QWidget *parent = Q_NULLPTR);
	~gui();

private:
	Ui::gui ui;
};
