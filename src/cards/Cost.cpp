#include "Cost.h"
#include "Colors.h"
#include "../util/automata.h"

#include <numeric>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <functional>

namespace mtg {

using namespace automata;

class Parser {
	bool sameSymbol;
	ManaPattern acc;
	std::vector<ManaPattern> symbols;
	FiniteAutomata<Range<char>,MealyTransition<Range<char>>> parser;

	void clear() {
		if( sameSymbol ) return;
		acc = ManaPattern();
	}
	void emit() {
		if( sameSymbol ) return;
		symbols.push_back(acc);
	}
	void newDigit(char d) {
		clear();
		acc.generic = d-'0';
	}
	void newChar(char c) {
		clear();
		acc.setChar(c);
	}
	void emitAndNewChar(char c) {
		emit();
		newChar(c);
	}
	void emitAndNewDigit(char d) {
		emit();
		newDigit(d);
	}
	void newSnow() {
		newChar('S');
		acc.generic = 1;
	};
public:
	Parser()
	{
		using namespace std;
		using namespace std::placeholders;
		parser.setTrans("start",Range<char>('X','Z'),"XYZ").output = bind(&Parser::newChar,this,_1);
		parser.setTrans("XYZ",Range<char>('X','Z'),"XYZ").output = bind(&Parser::emitAndNewChar,this,_1);
		parser.setTrans("XYZ",Range<char>('0','9'),"digit").output = bind(&Parser::emitAndNewDigit,this,_1);

		parser.setTrans("start",Range<char>('0','9'),"digit").output = bind(&Parser::newDigit,this,_1);
		parser.setTrans("digit",Range<char>('0','9'),"digit").output = [&](char d) {
			acc.generic *= 10;
			acc.generic += d-'0';
		};
		parser.setTrans("P",' ',"space").output =
		parser.setTrans("digit",' ',"space").output = [&](char c) {
			emit();
		};
		parser.setTrans("space",' ',"space");
		parser.setTrans("space",Range<char>('0','9'),"digit").output = bind(&Parser::newDigit,this,_1);

		parser.setTrans("color",Range<char>('0','9'),"digit").output = bind(&Parser::emitAndNewDigit,this,_1);

		parser.setTrans("color",'/',"slash");
		parser.setTrans("digit",'/',"slash");

		parser.setTrans("slash",Range<char>('0','9'),"digit").output = [&](char d) {
			acc.generic = d-'0';
		};

		parser.setTrans("color",'P',"P").output =
		parser.setTrans("slash",'P',"P").output = [&](char d) {
			acc.setChar('P');
		};

		for( int ci = 0; ci < nColors; ++ci ) {
			parser.setTrans("start",colors->colorText[ci],"color").output = bind(&Parser::newChar,this,_1);
			parser.setTrans("digit",colors->colorText[ci],"color").output =
			parser.setTrans("color",colors->colorText[ci],"color").output =
			parser.setTrans("XYZ",colors->colorText[ci],"color").output = bind(&Parser::emitAndNewChar,this,_1);
			parser.setTrans("slash",colors->colorText[ci],"color").output = [&](char c) {
				acc.setChar(c);
			};
		}

		// S
		parser.setTrans("start",'S',"XYZ").output = [this](char d) {
			newSnow();
		};
		parser.setTrans("digit",'S',"XYZ").output =
		parser.setTrans("color",'S',"XYZ").output =
		parser.setTrans("XYZ",'S',"XYZ").output = [this](char d) {
			emit();
			newSnow();
		};

		// {}
		parser.setTrans("start",'{',"start").output = [&](char c) { sameSymbol = true; };
		parser.setTrans("digit",'}',"start").output =
		parser.setTrans("color",'}',"start").output =
		parser.setTrans("XYZ",'}',"start").output =
		parser.setTrans("P",'}',"start").output = 	[&](char c) {
			sameSymbol = false;
			emit();
			clear();
		};

		parser.setStart("start");
		parser.getNode("start").final = true;
		parser.getNode("color").final = true;
		parser.getNode("digit").final = true;
		parser.getNode("XYZ").final = true;
		parser.getNode("P").final = true;
	}

	std::vector<ManaPattern> & parse(std::string const & cost)
	{
		sameSymbol = false;
		clear();
		symbols.clear();
		if( ! parser.consume(cost) ) throw std::invalid_argument("invalid cost string");
		if( ! acc.empty() ) {
			emit();
		}
		return symbols;
	}
};

thread_local Parser parser;

Cost::Cost()
{
}

Cost::Cost(char const * cost):
	symbols(parser.parse(std::string(cost)))
{
}

Cost::Cost(std::string const & cost):
	symbols(parser.parse(cost))
{
}

bool Cost::operator==(Cost const & cost) const
{
	return symbols == cost.symbols;
}

bool Cost::operator!=(Cost const & cost) const { return ! (*this == cost); }


ManaPattern::Specific allColors(0x1F);

ManaPattern::ManaPattern():
	generic(0)
{}

ManaPattern::ManaPattern(unsigned char generic):
	generic(generic)
{
}

ManaPattern::ManaPattern(unsigned char generic, Color c):
	generic(generic)
{
	colors.set(c);
}

ManaPattern::ManaPattern(Color c, Color c2):
	generic(0)
{
	colors.set(c);
	colors.set(c2);
}

unsigned ManaPattern::cmc() const
{
	if( generic > 0 ) return generic;
	if( (colors & allColors).any() ) return 1;
	return 0;
}

ManaPattern & ManaPattern::setChar(char c)
{
	int bit;
	switch(c) {
        case 'G': bit = green; break;
        case 'U': bit = blue; break;
        case 'R': bit = red; break;
        case 'W': bit = white; break;
        case 'B': bit = black; break;
        case 'X': bit = black+1; break;
        case 'Y': bit = black+2; break;
        case 'Z': bit = black+3; break;
        case 'P': bit = black+4; break;
        case 'S': bit = black+5; break;
        default: throw std::invalid_argument(c + std::string(" is a invalid char to set mana pattern"));
	}
	colors.set(bit);
	return *this;
}

bool ManaPattern::hasColor(Color c) const
{
	return colors[c];
}

bool ManaPattern::empty() const
{
	return colorless() && generic == 0;
}

bool ManaPattern::colorless() const
{
	return ! colors.any();
}

bool ManaPattern::monoColored() const
{
    return colors.count() == 1;
}

bool ManaPattern::operator==(ManaPattern const & mp) const
{
	return colors == mp.colors && generic == mp.generic;
}




unsigned Cost::convertedManaCost() const
{
	return std::accumulate(symbols.begin(),symbols.end(),0,[](unsigned t, ManaPattern symbol) { return t+symbol.cmc(); });
}

ManaPattern Cost::getColors() const
{
	ManaPattern result;
	result.colors = std::accumulate(symbols.begin(),symbols.end(),ManaPattern::Specific(),[](ManaPattern::Specific t, ManaPattern symbol) {
		return t | symbol.colors;
	});
	return result;
}



inline int showcolors_i() { 
    static int i = std::ios_base::xalloc();
    return i;
}

std::ostream & showcolors(std::ostream & os) {
    os.iword(showcolors_i()) = 1;
    return os;
}

std::ostream & operator<<(std::ostream & os, mtg::ManaPattern const & mp) {
    bool printed = false;
    if( os.iword(showcolors_i()) ) {
        for( Color c = Color(0); c != mtg::nColors; c = Color(c+1) ) {
            if( mp.colors[c] ) {
                if( printed ) os << '/';
                os << mtg::colors->colorDesc.getLeft()[c];
                printed = true;
            }
        }
        os.iword(showcolors_i()) = 0;
    } else {
        char const other[] = "XYZ";
        if( mp.generic > 0 ) {
            os << mp.generic;
            printed = true;
        }
        for( unsigned c = mtg::nColors+3; c-->mtg::nColors;  ) {
            if( mp.colors[c] ) {
                if( printed ) os << '/';
                os << other[c-mtg::nColors];
                printed = true;
            }
        }
        for( unsigned c = mtg::nColors; c-->0;  ) {
            if( mp.colors[c] ) {
                if( printed ) os << '/';
                os << mtg::colors->colorText[c];
                printed = true;
            }
        }
        if( ! printed ) {
            os << '0';
        }
    }
    return os;
}

std::ostream & operator<<(std::ostream & os, mtg::Cost const & cost) {
    std::copy(cost.getSymbols().begin(),cost.getSymbols().end(),std::ostream_iterator<mtg::ManaPattern>(os));
    return os;
}


}
