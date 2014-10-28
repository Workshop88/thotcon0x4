#include "Arduino.h"
#include "TcbTile.h"

#ifndef FontScroll_h
#define FontScroll_h

// the #include statment and code go here...

class FontScroll {
 public:
	void setMessage(const char* m);
	byte* scrollLeft(); // Scroll left if there's any text left to scroll, otherwise ignore
	const char* _m;
	const char* _m_index; // where are we in _m; next char to process

	int _currentCol; // index into _colBuffer, points to first col to display
					 // increment at end of handling
	byte _colBuffer[5];
	FontScroll();
};

void scrollMessage(const char* msg);

extern byte font5x8[256-0x20][5];

#endif
