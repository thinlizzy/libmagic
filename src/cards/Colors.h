#ifndef COLORS_H_jj433332jkfdg
#define COLORS_H_jj433332jkfdg

#include "types/Color.h"
#include "../util/singleton.h"
#include "../util/bimap.h"
#include <unordered_map>
#include <string>

namespace mtg {

class Colors {
	std::unordered_map<char,Color> colorChars;
public:
	char const * colorText;
	char const * colors_c[nColors];
	bimap<Color,std::string,std::hash<int>> colorDesc;
	Colors();
	Color charToColor(char c);
};

extern singleton<Colors> colors;

}

#endif
