#ifndef MANAPOOL_H_LIBMAGIC_2015_05_05
#define MANAPOOL_H_LIBMAGIC_2015_05_05

#include <unordered_map>
#include <string>
#include <list>
#include <initializer_list>
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
};

class ManaPool {
	using ManaList = std::list<Mana>;
	using ManaRef = ManaList::iterator;
	// really need a multi index
	ManaList pool;
    std::unordered_multimap<Color, ManaRef, std::hash<int>> byColor;
    std::unordered_multimap<Mana::Source, ManaRef, std::hash<int>> bySource;
    std::unordered_multimap<Mana::Annotation, ManaRef, std::hash<unsigned>> byAnnotation;
public:
	ManaPool() = default;

	void clear();
	unsigned count() const;
	void add(Color color);
	void add(Color color, Mana::Source source, std::initializer_list<Mana::Annotation> annotations);

	friend struct Iterator;
	struct Iterator { // TODO: forward iterator concept
		// TODO: hold a context to mana pool - iteration functions over the context
	};

	// returns an iterator that holds all matching possibilities
	// best fit comes first
	// some way to count (or not, just do a streaming approach)
	Iterator canCast(Cost const & cost, Mana::Annotations annotations = 0); // TODO: implement

	// removes from mana pool what is pointed by the iterator
	void remove(Iterator & it); // TODO: implement
private:
};

}

#endif
