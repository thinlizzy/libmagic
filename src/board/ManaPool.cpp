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

unsigned ManaPool::count() const
{
	return pool.size();
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

/*
	auto colored = byColor.equal_range(color);
	if( colored.first == byColor.end() ) {
		doAdd(color);
	} else {
		auto it = std::find_if(colored.first, colored.second, [](auto e) {
			return e.second->source == 0 && e.second->annotations == 0;
		});
		if( it == colored.second ) {
			doAdd(color);
		} else {
			++it->second->quantity;
			++cmc;
		}
	}
 */


} /* namespace mtg */
