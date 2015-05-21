#include "ManaMatcher.h"
#include <vector>
#include <memory>
#include <iterator>
#include <algorithm>

namespace mtg {

// TODO after implementation, consider removing indices for annotated mana (and also the burns at EOT thing). they seem useless

// return all (non-visited) mana pool units for a symbol - use the indices (color,snow,etc)
// generic mana and even colored mana can match a lot of combinations
// for each tested group, it needs to match mana.allowsRestrictions(annotations)

class MatchRangeIteratorStrategy {
public:
	virtual ~MatchRangeIteratorStrategy() = default;
	virtual MatchRangeIteratorStrategy * clone() = 0;  // :(
	virtual bool hasNext() = 0;
	virtual void next() = 0;
	virtual ManaPool::ManaCRef value() = 0;
};

class MatchRangeIteratorSnow: public MatchRangeIteratorStrategy {
	ManaPool::SourceRange snowRange;
	decltype(snowRange)::Iterator pos;
	ManaMatcher::Visited const & visited;
	Mana::Annotations annotations;
public:
	MatchRangeIteratorSnow(ManaPool const & manaPool, ManaMatcher::Visited const & visited, Mana::Annotations annotations):
		snowRange(manaPool.getBySource(Mana::snow)),
		pos(snowRange.begin()),
		visited(visited),
		annotations(annotations)
	{
		doNext();
	}
	MatchRangeIteratorSnow * clone() override { return new MatchRangeIteratorSnow(*this); }
	bool hasNext() override {
		return pos != snowRange.end();
	}
	void next() override {
		++pos;
		doNext();
	}
	ManaPool::ManaCRef value() override {
		return *pos;
	}
private:
	void doNext() {
		while( hasNext() && (visited.count(*pos) || ! (**pos).allowsRestrictions(annotations)) ) {
			++pos;
		}
	}
};

class MatchRangeIteratorColor: public MatchRangeIteratorStrategy {
	ManaPool::ColorRange colorRange;
	decltype(colorRange)::Iterator pos;
	ManaMatcher::Visited const & visited;
	Mana::Annotations annotations;
public:
	MatchRangeIteratorColor(ManaPool const & manaPool, ManaMatcher::Visited const & visited, Mana::Annotations annotations, Color color):
		colorRange(manaPool.getByColor(color)),
		pos(colorRange.begin()),
		visited(visited),
		annotations(annotations)
	{
		doNext();
	}
	MatchRangeIteratorColor * clone() override { return new MatchRangeIteratorColor(*this); }
	bool hasNext() override {
		return pos != colorRange.end();
	}
	void next() override {
		++pos;
		doNext();
	}
	ManaPool::ManaCRef value() override {
		return *pos;
	}
private:
	void doNext() {
		while( hasNext() && (visited.count(*pos) || ! (**pos).allowsRestrictions(annotations)) ) {
			++pos;
		}
	}
};

class MatchRangeIteratorGeneric: public MatchRangeIteratorStrategy {
	ManaPool::ManaCRef pos,end;
	ManaMatcher::Visited const & visited;
	Mana::Annotations annotations;
public:
	MatchRangeIteratorGeneric(ManaPool const & manaPool, ManaMatcher::Visited const & visited, Mana::Annotations annotations):
		pos(manaPool.mana().begin()),
		end(manaPool.mana().end()),
		visited(visited),
		annotations(annotations)
	{
		doNext();
	}
	MatchRangeIteratorGeneric * clone() override { return new MatchRangeIteratorGeneric(*this); }
	bool hasNext() override {
		return pos != end;
	}
	void next() override {
		++pos;
		doNext();
	}
	ManaPool::ManaCRef value() override {
		return pos;
	}
private:
	void doNext() {
		while( hasNext() && (visited.count(pos) || ! (*pos).allowsRestrictions(annotations)) ) {
			++pos;
		}
	}
};

class MatchRangeIterator: public std::iterator<std::forward_iterator_tag, ManaPool::ManaCRef> {
	std::unique_ptr<MatchRangeIteratorStrategy> s;
public:
	MatchRangeIterator() = default;
	MatchRangeIterator(MatchRangeIterator &&) = default;
	MatchRangeIterator(MatchRangeIterator const & mri):
		s(mri.s ? mri.s->clone() : nullptr)
	{}
	MatchRangeIterator(std::unique_ptr<MatchRangeIteratorStrategy> s):
		s(std::move(s))
	{
		if( s && ! s->hasNext() ) s.reset(); // return to sentinel if no more elements
	}
	typename MatchRangeIterator::value_type operator*() { return s->value(); }
	MatchRangeIterator & operator++() { s->next(); if( ! s->hasNext() ) s.reset(); return *this; }
	bool operator==(MatchRangeIterator const & it) const { return s.get() == it.s.get(); } // will only compare with a sentinel
	bool operator!=(MatchRangeIterator const & it) const { return ! (*this == it); }
};

struct SymbolMatcher {
	ManaSymbol::Generic generic = 0;
	bool snow;
	bool phyrexian;
	Color color;
	SymbolMatcher & setColor(Color color) { this->color = color; return *this; }
	SymbolMatcher & setGeneric(ManaSymbol::Generic generic) { this->generic = generic; return *this; }
	SymbolMatcher & setPhyrexian() { this->phyrexian = true; return *this; }
	SymbolMatcher & setSnow() { this->snow = true; return *this; }
};

class MatchRange {
	MatchRangeIterator beg;
public:
	static std::unique_ptr<MatchRangeIteratorStrategy> matchRangeIteratorFactory(ManaPool const & manaPool,
			ManaMatcher::Visited const & visited, SymbolMatcher symbolMatcher, Mana::Annotations annotations) {
		// phyrexian was already dealt with and X, Y and Z will be ignored for simplicity, so only snow matters now for specific mana.
		if( symbolMatcher.snow ) {
			return std::make_unique<MatchRangeIteratorSnow>(manaPool,visited,annotations);
		}
		if( symbolMatcher.generic > 0 ) {
			return std::make_unique<MatchRangeIteratorGeneric>(manaPool,visited,annotations);
		}
		return std::make_unique<MatchRangeIteratorColor>(manaPool,visited,annotations,symbolMatcher.color);
	}

	MatchRange(ManaPool const & manaPool, ManaMatcher::Visited const & visited,
		SymbolMatcher symbolMatcher, Mana::Annotations annotations):
			beg(matchRangeIteratorFactory(manaPool,visited,symbolMatcher,annotations))
	{
	}

	MatchRangeIterator begin() { return beg; }

	MatchRangeIterator end() { return MatchRangeIterator{}; }
};

auto symbolMatchers(ManaSymbol symbol)
{
	std::vector<SymbolMatcher> result;
	if( symbol.colored() ) {
		for( auto color = firstColor; color != nColors; color = Color(color+1) ) {
			if( symbol.hasColor(color) ) {
				result.push_back(SymbolMatcher{}.setColor(color));
			}
		}
	}
	if( symbol.specific == ManaSymbol::phyrexian ) {
		result.push_back(SymbolMatcher{}.setPhyrexian());
	} else
	if( symbol.specific == ManaSymbol::snow ) {
		result.push_back(SymbolMatcher{}.setSnow());
	} else
	if( symbol.generic > 0 ) {
		result.push_back(SymbolMatcher{}.setGeneric(symbol.generic));
	}
	return result;
}

//

ManaMatcher::ManaMatcher(size_t maxSolutions):
	maxSolutions(maxSolutions)
{
	solutions.reserve(maxSolutions);
}

ManaMatcher & ManaMatcher::match(Cost const & cost, ManaPool const & manaPool, Mana::Annotations annotations)
{
	solutions.clear();

	// test the obvious solution
	if( cost.convertedManaCost() == 0 ) {
		Solution solution;
		solution.life = 0;
		solutions.push_back(std::move(solution));
		return *this;
	}

	// early bail out on impossible solutions
	if( manaPool.mana().size() < cost.minimumManaCost() ) return *this;

	visited.clear();
	life = 0;
	// symbols are sorted like X-generic-snow-colored, so iteration is done in reverse order to match colors first, then snow and finally generic
	doMatch(cost.symbols.rbegin(),cost.symbols.rend(),manaPool,annotations);
	return *this;
}

bool ManaMatcher::doMatch(Cost::Symbols::const_reverse_iterator costIt, Cost::Symbols::const_reverse_iterator costEnd,
		ManaPool const & manaPool, Mana::Annotations annotations)
{
	if( solutions.size() >= maxSolutions ) return true; // terminate early if all solutions were recorded
	if( costIt == costEnd ) {
		// all cost is consumed, so record a solution
		Solution solution;
		solution.life = life;
		solution.mana.assign(visited.begin(),visited.end());
		// sort mana to compare with previous solutions
		std::sort(solution.mana.begin(),solution.mana.end(),[](auto mr1, auto mr2) {
			return mr1->rank() < mr2->rank();
		});
		if( std::find(solutions.begin(),solutions.end(),solution) == solutions.end() ) {
			solutions.push_back(std::move(solution));
		}
		return true;
	}

	// decouple and serialize a symbol matcher (e.g: W/P = list with [W P]. 2/W = [W 1 1]). use colored first
	for( auto symbolMatcher : symbolMatchers(*costIt) ) {
		if( symbolMatcher.phyrexian ) {
			life += 2;
			if( doMatch(std::next(costIt),costEnd,manaPool,annotations) ) {
				return true;
			}
			life -= 2;
		} else
		if( symbolMatcher.generic > 0 ) {
			std::vector<ManaPool::ManaCRef> gen;
			for( auto match : MatchRange{manaPool,visited,symbolMatcher,annotations} ) {
				gen.push_back(match);
				if( gen.size() >= symbolMatcher.generic ) break;
			}
			if( gen.size() < symbolMatcher.generic ) return false; // not enough to match generic mana

			for( auto elem : gen ) {
				visited.insert(elem);
			}
			if( doMatch(std::next(costIt),costEnd,manaPool,annotations) ) {
				return true;
			}
			for( auto elem : gen ) {
				visited.erase(elem);
			}
		} else {
			for( auto match : MatchRange{manaPool,visited,symbolMatcher,annotations} ) {
				visited.insert(match);
				if( doMatch(std::next(costIt),costEnd,manaPool,annotations) ) {
					return true;
				}
				visited.erase(match);
			}
		}
	}

	return false;  // exhausted all matchers for a symbol, so give up on this iteration
}

} /* namespace mtg */
