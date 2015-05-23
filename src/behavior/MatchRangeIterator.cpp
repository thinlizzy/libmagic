#include "MatchRangeIterator.h"
#include "../board/Mana.h"

namespace mtg {

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
	Mana::Annotations annotations;
public:
	MatchRangeIteratorSnow(ManaPool const & manaPool, ManaPool::ManaSet const & visited, Mana::Annotations annotations):
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
	ManaPool::ManaSet const & visited;
	Mana::Annotations annotations;
public:
	MatchRangeIteratorColor(ManaPool const & manaPool, ManaPool::ManaSet const & visited, Mana::Annotations annotations, Color color):
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
	ManaPool::ManaSet const & visited;
	Mana::Annotations annotations;
public:
	MatchRangeIteratorGeneric(ManaPool const & manaPool, ManaPool::ManaSet const & visited, Mana::Annotations annotations):
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

std::unique_ptr<MatchRangeIteratorStrategy> matchRangeIteratorFactory(ManaPool const & manaPool,
		ManaPool::ManaSet const & visited, CostSymbol symbol, Mana::Annotations annotations)
{
	// phyrexian was already dealt with and X, Y and Z will be ignored for simplicity, so only snow matters for specific mana.
	if( symbol.specific == CostSymbol::snow ) {
		return std::make_unique<MatchRangeIteratorSnow>(manaPool,visited,annotations);
	}
	if( symbol.generic > 0 ) {
		return std::make_unique<MatchRangeIteratorGeneric>(manaPool,visited,annotations);
	}
	return std::make_unique<MatchRangeIteratorColor>(manaPool,visited,annotations,symbol.firstColor());
}

//

MatchRange::MatchRange(ManaPool const & manaPool, ManaPool::ManaSet const & visited,
		CostSymbol symbol, Mana::Annotations annotations):
	beg(matchRangeIteratorFactory(manaPool,visited,symbol,annotations))
{}

MatchRangeIterator MatchRange::begin()
{
	return beg;
}

MatchRangeIterator MatchRange::end()
{
	return MatchRangeIterator{};
}

}
