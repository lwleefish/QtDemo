#include "WindowDemo.h"
#include <windows.h>
#include <QtWidgets/QApplication>
#include <QDebug>
HHOOK key_keep = NULL;

LRESULT CALLBACK KeyboardProc(int code, WPARAM wparam, LPARAM lparam);

void register_key_hook();
void unregister_key_hook();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	register_key_hook();
    WindowDemo w;
    w.show();
	int ret = a.exec();
	unregister_key_hook();
    return ret;
}
void register_key_hook()
{
	if (key_keep)return;
	QString s = "";
	HINSTANCE hi = GetModuleHandle(NULL);
	key_keep = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, hi, 0);
}
void unregister_key_hook()
{
	UnhookWindowsHookEx(key_keep); key_keep = NULL;
}
LRESULT CALLBACK KeyboardProc(int code, WPARAM wparam, LPARAM lparam)
{
	if (code >= 0) {
		//PKBDLLHOOKSTRUCT MyKeyboardHookStruct = (PKBDLLHOOKSTRUCT)lparam;
		//在WH_KEYBOARD_LL模式下lParam 是指向KBDLLHOOKSTRUCT类型地址  
		KBDLLHOOKSTRUCT *pkbhs = (KBDLLHOOKSTRUCT *)lparam;

		if ((wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN) && pkbhs->vkCode == VK_ESCAPE && GetAsyncKeyState(VK_CONTROL) & 0x8000 && GetAsyncKeyState(VK_SHIFT) & 0x8000) {
			qDebug() << "Ctrl+Shift+Esc";
		}
		else if ((wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN) && pkbhs->vkCode == VK_ESCAPE && GetAsyncKeyState(VK_CONTROL) & 0x8000) {
			qDebug() << "Ctrl+Esc";
		}
		else if ((wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN) && pkbhs->vkCode == VK_TAB && pkbhs->flags & LLKHF_ALTDOWN) {
			qDebug() << "Alt+Tab";
		}
		else if ((wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN) && pkbhs->vkCode == VK_ESCAPE && pkbhs->flags &LLKHF_ALTDOWN) {
			qDebug() << "Alt+Esc";
		}
		else if ((wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN) && pkbhs->vkCode == VK_LWIN || pkbhs->vkCode == VK_RWIN) {
			qDebug() << "LWIN/RWIN";
		}
		else if ((wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN) && pkbhs->vkCode == VK_F4 && pkbhs->flags & LLKHF_ALTDOWN) {
			qDebug() << "Alt+F4";
		}
		if ((wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN) && pkbhs->vkCode == VK_F4)
		{
		}
	}

	return CallNextHookEx(key_keep, code, wparam, lparam);
}


