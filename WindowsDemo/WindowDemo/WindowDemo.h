#pragma once

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include "titlebar.h"
#include "MProfile.h"
#include "QCheckBox"
//typedef void (WindowDemo::*FUNC)(int);
//struct  ITEM_FUNC
//{
//	int  code;
//	FUNC pFun;
//	int  param;
//};
class WindowDemo : public QWidget
{
    Q_OBJECT

public:
    WindowDemo(QWidget *parent = Q_NULLPTR);
	~WindowDemo();
	int keydown = 0;
	int keypress = 0;
	int keyup = 0;
	//static LRESULT CALLBACK KeyboardProc(int code, WPARAM wparam, LPARAM lparam);
	//HOOKPROC hookproc;
	//×¢²á¹³×Ó  
	//void register_key_hook();
	//ÊÍ·Å¹³×Ó  
	//void unregister_key_hook();
	//void select_main_card(int) {};
	//void select_next_card(int) {};
	/*void excute_function(FUNC fun, int param)
	{
		(this->*fun)(param);
	}*/
protected:
	virtual void paintEvent(QPaintEvent*);
	void initLayout();
private slots:
	void closeWindow();
	void maxWindow();
	void minWindow();
	void moveWindow(QMouseEvent *e);
	void mouseClick(QMouseEvent *e);
	void capture();
	void reghref();
	void findpwdhref();
	void openKeyBoard(bool);
private:
	QVBoxLayout* main_layout_v;
	QHBoxLayout main_layout_h;
	QHBoxLayout *check_layout_h;
	QGridLayout* grid_layout;
	TitleBar *titlebar;
	QPoint point_old;
	QPushButton* qcapture;
	QComboBox *cbx_username;
	QLineEdit *te_password;
	QPushButton *reg;
	QPushButton *findpwd;
	MProfile *profile;
	QCheckBox *rememberpwd;
	QCheckBox *autologin;
	QPushButton *login;

	QAction *pTrailingAction;
	//HHOOK key_keep = NULL;
	
	

};
