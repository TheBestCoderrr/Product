#pragma once
#include <iostream>
using namespace std;
class String
{
private:
	char* str;
	static size_t CountStr;
public:
	String();
	String(size_t size);
	String(const char* str);
	String(const String& OtherString);
	~String();

	void SetStr(char* str);
	char* GetStr() const;

	static size_t GetCountStr();

	String& operator=(const String& OtherString) noexcept;
	String operator*(const String& OtherString) noexcept;
};

inline ostream& operator<<(ostream& out, const String& string) {
	out << string.GetStr() << endl;
	return out;
}

inline istream& operator>>(istream& in, String& string) {
	char Buffer[200];
	in.getline(Buffer, strlen(Buffer));
	string.SetStr(Buffer);
	return in;
}


