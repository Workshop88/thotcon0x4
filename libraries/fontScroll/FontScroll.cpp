#include "fontScroll.h"
#include "font5x8.ino"

FontScroll::FontScroll() {
	_m = "";
	_currentCol = 4;
	_m_index = _m;
};

byte* FontScroll::scrollLeft() { // Scroll left if there's any text left to scroll, otherwise ignore
	int currentLetter = *_m_index;
	int edge = _currentCol;
	boolean interchar = false;

	if (edge < 0)
	{
		interchar = true;
	}

	for(int col = 4; col >= 0; col--) 
	{
		if (interchar)
		{
			_colBuffer[col] = font5x8[' '-0x20][0];
			edge = 4;
			currentLetter = *(_m_index+1) ? *(_m_index+1) : ' ';
			interchar = false;
		}
		else
		{
			_colBuffer[col] = font5x8[currentLetter-0x20][edge];
			edge--;
		}

		if(edge < 0) {
			interchar = true;
		}
	}
	_currentCol--;
	if(_currentCol < -1) {
	  _currentCol = 4;
	  _m_index++;
	}
	return _colBuffer;
};

void FontScroll::setMessage(const char* m) {
	_m = m;
	_m_index = m;
	_currentCol = 4;
};

void scrollMessage(const char *msg)
{
	FontScroll fs;
	
	fs.setMessage(msg);

	for (int i=0; i<6*(strlen(fs._m));i++)
	{
		show_screen(fs.scrollLeft(), 30);
	}	
}
