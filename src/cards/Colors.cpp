#include "Colors.h"
#include <algorithm>

namespace mtg {

singleton<Colors> colors;

char const * COLORS[] = {"Green","Blue","Red","White","Black"};

Colors::Colors():
	colorText("GURWB")
{
	using namespace std;
	copy(begin(COLORS),end(COLORS),begin(colors_c));
	for(Color col = Color(0); col < nColors; col = Color(col+1)) {
		colorChars[colorText[col]] = col;
		colorDesc.set(col,colors_c[col]);
	}
}

Color Colors::charToColor(char c)
{
	auto c_i = colorChars.find(c);
	if( c_i == colorChars.end() ) throw false;

	return c_i->second;
}

}