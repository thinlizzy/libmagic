#include "ManaPool.h"
#include <iterator>
#include <algorithm>

namespace mtg {

void ManaPool::clear()
{
	byColor.clear();
	bySource.clear();
	byAnnotation.clear();
	pool.clear();
}

void ManaPool::add(Color color)
{
	pool.push_back({color});
	byColor.insert({color,std::prev(pool.end())});
}

void ManaPool::add(Color color, Mana::Source source, std::initializer_list<Mana::Annotation> annotations)
{
	pool.push_back({color,source});
	auto manaIt = std::prev(pool.end());
	byColor.insert({color,manaIt});
	if( source != 0 ) {
		bySource.insert({source,manaIt});
	}
	for( auto annotation : annotations ) {
		manaIt->annotations |= annotation;
		byAnnotation.insert({annotation,manaIt});
	}
}

auto ManaPool::getByColor(Color color) const -> Range<ByColorCIt>
{
	return Range<ByColorCIt>{byColor.equal_range(color)};
}

auto ManaPool::getBySource(Mana::Source source) const -> Range<BySourceCIt>
{
	return Range<BySourceCIt>{bySource.equal_range(source)};
}

auto ManaPool::getByAnnotation(Mana::Annotation annotation) const -> Range<ByAnnotationCIt>
{
	return Range<ByAnnotationCIt>{byAnnotation.equal_range(annotation)};
}

bool ManaPool::canCast(Cost const & cost, Mana::Annotations annotations = 0) const
{
	 // TODO: implement
	return false;
}

void ManaPool::remove(ManaCRef it)
{
	 // TODO: implement
}

/*
		auto it = std::find_if(colored.first, colored.second, [](auto e) {
			return e.second->source == 0 && e.second->annotations == 0;
		});
		if( it == colored.second ) {
			fufu
		} else {
			eeee
		}
	}
 */


} /* namespace mtg */
