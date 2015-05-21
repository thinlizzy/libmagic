#ifndef MANAPOOL_H_LIBMAGIC_2015_05_05
#define MANAPOOL_H_LIBMAGIC_2015_05_05

#include <unordered_map>
#include <string>
#include <list>
#include <initializer_list>
#include <iterator>
#include "../cards/Color.h"
#include "../iterator/iterator_second.h"
#include "../iterator/pair_range.h"
#include "Mana.h"

namespace mtg {

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
public:
	ManaPool() = default;

	ManaList const & mana() const { return pool; }
	using ColorRange = PairRange<ByColorCIt,IteratorSecond<ByColorCIt>>;
	using SourceRange = PairRange<BySourceCIt,IteratorSecond<BySourceCIt>>;
	ColorRange getByColor(Color color) const;
	SourceRange getBySource(Mana::Source source) const;
	PairRange<ByAnnotationCIt,IteratorSecond<ByAnnotationCIt>> getByAnnotation(Mana::Annotation annotation) const;

	void clear();

	void add(Color color);
	void add(Color color, Mana::Source source, std::initializer_list<Mana::Annotation> annotations);

	void remove(ManaCRef manaRef);
};

} // namespace mtg

namespace std {

template<>
struct hash<mtg::ManaPool::ManaCRef> {
    size_t operator()(mtg::ManaPool::ManaCRef const & mcr) const {
        return std::hash<decltype(mcr.operator->())>()(mcr.operator->());
    }
};

}

#endif
