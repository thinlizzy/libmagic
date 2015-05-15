#include "Cost.h"
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
			parser.setTrans("start",colorText[ci],"color").output = bind(&Parser::newChar,this,_1);
			parser.setTrans("digit",colorText[ci],"color").output =
			parser.setTrans("color",colorText[ci],"color").output =
			parser.setTrans("XYZ",colorText[ci],"color").output = bind(&Parser::emitAndNewChar,this,_1);
			parser.setTrans("slash",colorText[ci],"color").output = [&](char c) {
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

//

thread_local Parser parser;

Cost::Cost(char const * cost):
	symbols(parser.parse(std::string(cost)))
{
	sortSymbols();
}

Cost::Cost(std::string const & cost):
	symbols(parser.parse(cost))
{
	sortSymbols();
}

// put all colorless mana to the end
void Cost::sortSymbols()
{
	std::sort(symbols.begin(),symbols.end(),[](auto s1, auto s2) {
		return s1.colorless() > s2.colorless();
	});
}

bool Cost::operator==(Cost const & cost) const
{
	return symbols == cost.symbols;
}

bool Cost::operator!=(Cost const & cost) const { return ! (*this == cost); }

unsigned Cost::convertedManaCost() const
{
	return std::accumulate(symbols.begin(),symbols.end(),0,[](unsigned t, ManaPattern symbol) {
		return t+symbol.cmc();
	});
}

bool Cost::hasColor(Color c) const
{
	return std::find_if(symbols.begin(),symbols.end(),[c](auto symbol){
		return symbol.hasColor(c);
	}) != symbols.end();
}

bool Cost::colorless() const
{
	return std::find_if_not(symbols.begin(),symbols.end(),[](auto symbol){
		return symbol.colorless();
	}) == symbols.end();
}

ColorSet Cost::colors() const
{
	return std::accumulate(symbols.begin(),symbols.end(),ColorSet{},[](ColorSet t, auto symbol) {
		return t |= symbol.colors;
	});
}

//

ManaPattern::ManaPattern():
	generic(0)
{}

ManaPattern::ManaPattern(Generic generic):
	generic(generic)
{
}

ManaPattern::ManaPattern(Generic generic, Color c):
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
	if( colors.any() ) return 1;
	return 0;
}

ManaPattern & ManaPattern::setChar(char c)
{
	switch(c) {
        case 'G': colors.set(green); break;
        case 'U': colors.set(blue); break;
        case 'R': colors.set(red); break;
        case 'W': colors.set(white); break;
        case 'B': colors.set(black); break;
        case 'X': specific.set(0); break;
        case 'Y': specific.set(1); break;
        case 'Z': specific.set(2); break;
        case 'P': specific.set(3); break;
        case 'S': specific.set(4); break;
        default: throw std::invalid_argument(c + std::string(" is a invalid char to set mana pattern"));
	}
	return *this;
}

bool ManaPattern::hasColor(Color c) const
{
	return colors[c];
}

bool ManaPattern::colorless() const
{
	return ! colors.any();
}

bool ManaPattern::monoColored() const
{
    return colors.count() == 1;
}

bool ManaPattern::empty() const
{
	return ! colors.any() && ! specific.any() && generic == 0;
}

bool ManaPattern::operator==(ManaPattern const & mp) const
{
	return colors == mp.colors && specific == mp.specific && generic == mp.generic;
}

}
