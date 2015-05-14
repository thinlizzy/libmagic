#ifndef MANAPOOL_H_LIBMAGIC_2015_05_05
#define MANAPOOL_H_LIBMAGIC_2015_05_05

#include <unordered_map>
#include <string>
#include <list>
#include <initializer_list>
#include <iterator>
#include "../cards/types/Color.h"
#include "../cards/Cost.h"

namespace mtg {

struct Mana {
	enum Source { snow = 1, };
	enum Annotation : unsigned {
		spells = 1, abilities = 2,
		upkeep = 4,
		artifact = 128, creature = 256,
		burnsOnlyAtEot = 1024,
	};
	using Annotations = unsigned;

	Color color;
	Source source;
	Annotations annotations;
	bool operator==(Mana const & mana) const {
		return color == mana.color && source == mana.source && annotations == mana.annotations;
	}
};

class ManaPool {
public:
	using ManaList = std::list<Mana>;
	using ManaRef = ManaList::iterator;
	using ManaCRef = ManaList::const_iterator;
private:
	// really need a multi index container
	ManaList pool;
    std::unordered_multimap<Color, ManaRef, std::hash<int>> byColor;
    std::unordered_multimap<Mana::Source, ManaRef, std::hash<int>> bySource;
    std::unordered_multimap<Mana::Annotation, ManaRef, std::hash<unsigned>> byAnnotation;

    using ByColorCIt = decltype(byColor)::const_iterator;
    using BySourceCIt = decltype(bySource)::const_iterator;
    using ByAnnotationCIt = decltype(byAnnotation)::const_iterator;

    template<typename CIT>
    class ByIterator: public std::iterator<std::forward_iterator_tag, typename CIT::value_type::second_type> {
    	CIT pos;
    public:
    	ByIterator(CIT pos): pos(pos) {}
    	typename ByIterator::value_type operator*() { return pos->second; }
    	ByIterator & operator++() { ++pos; return *this; }
    	ByIterator operator++(int) { auto result = *this; ++*this; return result; }
        bool operator==(ByIterator const & it) const { return pos == it.pos; }
        bool operator!=(ByIterator const & it) const { return ! (*this == it); }
    };

    template<typename CIT>
    struct Range {
    	std::pair<CIT,CIT> itPair;
    	using Iterator = ByIterator<CIT>;
    	Iterator begin() { return Iterator{itPair.first}; }
    	Iterator end() { return Iterator{itPair.second}; }
    	bool empty() const { return itPair.first == itPair.second; }
    };
public:
	ManaPool() = default;

	ManaList const & mana() const { return pool; }
	Range<ByColorCIt> getByColor(Color color) const;
	Range<BySourceCIt> getBySource(Mana::Source source) const;
	Range<ByAnnotationCIt> getByAnnotation(Mana::Annotation annotation) const;

	void clear();

	void add(Color color);
	void add(Color color, Mana::Source source, std::initializer_list<Mana::Annotation> annotations);

	void remove(ManaCRef manaRef);

	bool canCast(Cost const & cost, Mana::Annotations annotations = 0) const;
};

}

#endif
