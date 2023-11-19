#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
const tm* getLocalTime() {
	time_t now = time(0);
	const tm* LOCALTIME = localtime(&now);
	return LOCALTIME;
}