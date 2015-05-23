#include "CostParser.h"
#include "automata.h"
#include <stdexcept>

namespace mtg {

using namespace automata;

class Parser {
	bool sameSymbol;
	bool pending;
	CostSymbol acc;
	Cost::Symbols symbols;
	FiniteAutomata<Range<char>,MealyTransition<Range<char>>> parser;

	void setChar(char c)
	{
		switch(c) {
	        case 'G': acc.colors.set(Color::green); break;
	        case 'U': acc.colors.set(Color::blue); break;
	        case 'R': acc.colors.set(Color::red); break;
	        case 'W': acc.colors.set(Color::white); break;
	        case 'B': acc.colors.set(Color::black); break;
	        case 'X': acc.specific = CostSymbol::X; break;
	        case 'Y': acc.specific = CostSymbol::Y; break;
	        case 'Z': acc.specific = CostSymbol::Z; break;
	        case 'P': acc.specific = CostSymbol::phyrexian; break;
	        case 'S': acc.specific = CostSymbol::snow; break;
	        default: throw std::invalid_argument(c + std::string(" is a invalid char to set mana pattern"));
		}
	}

	void clear() {
		if( sameSymbol ) return;
		acc = CostSymbol();
		pending = false;
	}
	void emit() {
		if( sameSymbol ) return;
		symbols.push_back(acc);
		pending = false;
	}
	void newDigit(char d) {
		clear();
		acc.generic = d-'0';
		pending = true;
	}
	void newChar(char c) {
		clear();
		setChar(c);
		pending = true;
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
			setChar('P');
		};

		for( auto color : ColorList() ) {
			parser.setTrans("start",colorText(color),"color").output = bind(&Parser::newChar,this,_1);
			parser.setTrans("digit",colorText(color),"color").output =
			parser.setTrans("color",colorText(color),"color").output =
			parser.setTrans("XYZ",colorText(color),"color").output = bind(&Parser::emitAndNewChar,this,_1);
			parser.setTrans("slash",colorText(color),"color").output = [&](char c) {
				setChar(c);
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

	std::vector<CostSymbol> & parse(std::string const & cost)
	{
		sameSymbol = false;
		clear();
		symbols.clear();
		if( ! parser.consume(cost) ) throw std::invalid_argument("invalid cost string");
		if( pending ) {
			emit();
		}
		return symbols;
	}
};

//

thread_local Parser parser;

Cost parseCost(char const * cost)
{
	return parseCost(std::string(cost));
}

Cost parseCost(std::string cost)
{
	return { parser.parse(cost) };
}

}
