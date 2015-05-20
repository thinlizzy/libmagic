#ifndef ITERATOR_SECOND_H_LIBMAGIC_2015_05_19
#define ITERATOR_SECOND_H_LIBMAGIC_2015_05_19

#include <iterator>

template<typename IT>
class IteratorSecond: public std::iterator<std::forward_iterator_tag, typename IT::value_type::second_type> {
	IT pos;
public:
	IteratorSecond(IT pos): pos(pos) {}
	typename IteratorSecond::value_type operator*() { return pos->second; }
	IteratorSecond & operator++() { ++pos; return *this; }
	IteratorSecond operator++(int) { auto result = *this; ++*this; return result; }
	bool operator==(IteratorSecond const & it) const { return pos == it.pos; }
	bool operator!=(IteratorSecond const & it) const { return ! (*this == it); }
};

#endif /* ITERATOR_SECOND_H_ */
