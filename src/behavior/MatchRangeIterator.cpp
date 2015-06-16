#include "MatchRangeIterator.h"
#include "../board/Mana.h"

namespace mtg {

namespace matcher {

MatchRangeIterator::MatchRangeIterator(MatchRangeIterator const & mri):
	s(mri.s ? mri.s->clone() : nullptr)
{}

MatchRangeIterator::MatchRangeIterator(std::unique_ptr<MatchRangeIteratorStrategy> s_):
	s(std::move(s_))
{
	if( s && ! s->hasNext() ) {
		s.reset(); // return to sentinel if no more elements
	}
}

typename MatchRangeIterator::value_type MatchRangeIterator::operator*()
{
	return s->value();
}

MatchRangeIterator & MatchRangeIterator::operator++()
{
	s->next();
	if( ! s->hasNext() ) {
		s.reset();
	}
	return *this;
}

bool MatchRangeIterator::operator==(MatchRangeIterator const & it) const
{
	return s.get() == it.s.get(); // will only compare with a sentinel
}

bool MatchRangeIterator::operator!=(MatchRangeIterator const & it) const
{
	return ! (*this == it);
}

//

class MatchRangeIteratorSnow: public MatchRangeIteratorStrategy {
	ManaPool::SourceRange snowRange;
	decltype(snowRange)::Iterator pos;
	ManaPool::ManaSet const & visited;
	ManaFilter manaFilter;
public:
	MatchRangeIteratorSnow(ManaPool const & manaPool, ManaPool::ManaSet const & visited, ManaFilter manaFilter):
		snowRange(manaPool.getBySource(Mana::snow)),
		pos(snowRange.begin()),
		visited(visited),
		manaFilter(manaFilter)
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
		while( hasNext() && (visited.count(*pos) || manaFilter(*pos)) ) {
			++pos;
		}
	}
};

class MatchRangeIteratorColor: public MatchRangeIteratorStrategy {
	ManaPool::ColorRange colorRange;
	decltype(colorRange)::Iterator pos;
	ManaPool::ManaSet const & visited;
	ManaFilter manaFilter;
public:
	MatchRangeIteratorColor(ManaPool const & manaPool, ManaPool::ManaSet const & visited, ManaFilter manaFilter, Color color):
		colorRange(manaPool.getByColor(color)),
		pos(colorRange.begin()),
		visited(visited),
		manaFilter(manaFilter)
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
		while( hasNext() && (visited.count(*pos) || manaFilter(*pos)) ) {
			++pos;
		}
	}
};

class MatchRangeIteratorGeneric: public MatchRangeIteratorStrategy {
	ManaPool::ManaCRef pos,end;
	ManaPool::ManaSet const & visited;
	ManaFilter manaFilter;
public:
	MatchRangeIteratorGeneric(ManaPool const & manaPool, ManaPool::ManaSet const & visited, ManaFilter manaFilter):
		pos(manaPool.mana().begin()),
		end(manaPool.mana().end()),
		visited(visited),
		manaFilter(manaFilter)
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
		while( hasNext() && (visited.count(pos) || manaFilter(pos)) ) {
			++pos;
		}
	}
};

std::unique_ptr<MatchRangeIteratorStrategy> matchRangeIteratorFactory(ManaPool const & manaPool,
		ManaPool::ManaSet const & visited, CostSymbol symbol, ManaFilter manaFilter)
{
	// phyrexian was already dealt with and X, Y and Z will be ignored for simplicity, so only snow matters for specific mana.
	if( symbol.specific == CostSymbol::snow ) {
		return std::make_unique<MatchRangeIteratorSnow>(manaPool,visited,manaFilter);
	}
	if( symbol.generic > 0 ) {
		return std::make_unique<MatchRangeIteratorGeneric>(manaPool,visited,manaFilter);
	}
	return std::make_unique<MatchRangeIteratorColor>(manaPool,visited,manaFilter,symbol.firstColor());
}

//

MatchRange::MatchRange(ManaPool const & manaPool, ManaPool::ManaSet const & visited,
		CostSymbol symbol, ManaFilter manaFilter):
	beg(matchRangeIteratorFactory(manaPool,visited,symbol,manaFilter))
{}

MatchRangeIterator MatchRange::begin()
{
	return beg;
}

MatchRangeIterator MatchRange::end()
{
	return MatchRangeIterator{};
}

} /* namespace matcher */

}
