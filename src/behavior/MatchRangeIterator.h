#ifndef MATCHRANGEITERATOR_H_LIBMAGIC_2015_23_05
#define MATCHRANGEITERATOR_H_LIBMAGIC_2015_23_05

#include <memory>
#include <iterator>
#include "../board/ManaPool.h"
#include "../cards/CostSymbol.h"

namespace mtg {

class MatchRangeIteratorStrategy {
public:
	virtual ~MatchRangeIteratorStrategy() = default;
	virtual MatchRangeIteratorStrategy * clone() = 0;  // :(
	virtual bool hasNext() = 0;
	virtual void next() = 0;
	virtual ManaPool::ManaCRef value() = 0;
};

class MatchRangeIterator: public std::iterator<std::forward_iterator_tag, ManaPool::ManaCRef> {
	std::unique_ptr<MatchRangeIteratorStrategy> s;
public:
	MatchRangeIterator() = default;
	MatchRangeIterator(MatchRangeIterator &&) = default;
	MatchRangeIterator(MatchRangeIterator const & mri);
	MatchRangeIterator(std::unique_ptr<MatchRangeIteratorStrategy> s_);
	typename MatchRangeIterator::value_type operator*();
	MatchRangeIterator & operator++();
	bool operator==(MatchRangeIterator const & it) const;
	bool operator!=(MatchRangeIterator const & it) const;
};

class MatchRange {
	MatchRangeIterator beg;
public:
	MatchRange(ManaPool const & manaPool, ManaPool::ManaSet const & visited,
			CostSymbol symbol, Mana::Annotations annotations);
	MatchRangeIterator begin();
	MatchRangeIterator end();
};

}

#endif /* MATCHRANGEITERATOR_H_ */
