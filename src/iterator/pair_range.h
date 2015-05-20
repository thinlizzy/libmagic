#ifndef PAIR_RANGE_H_LIBMAGIC_2015_05_19
#define PAIR_RANGE_H_LIBMAGIC_2015_05_19

template<typename T, typename IT>
struct PairRange {
	using Iterator = IT;
	std::pair<T,T> itPair;
	IT begin() { return IT{itPair.first}; }
	IT end() { return IT{itPair.second}; }
	bool empty() const { return itPair.first == itPair.second; }
};

#endif /* PAIR_RANGE_H_ */
