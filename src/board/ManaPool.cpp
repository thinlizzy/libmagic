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

auto ManaPool::getByColor(Color color) const -> ColorRange
{
	return ColorRange{byColor.equal_range(color)};
}

auto ManaPool::getBySource(Mana::Source source) const -> SourceRange
{
	return SourceRange{bySource.equal_range(source)};
}

auto ManaPool::getByAnnotation(Mana::Annotation annotation) const -> PairRange<ByAnnotationCIt,IteratorSecond<ByAnnotationCIt>>
{
	return PairRange<ByAnnotationCIt,IteratorSecond<ByAnnotationCIt>>{byAnnotation.equal_range(annotation)};
}

template<typename C, typename T>
void removeFrom(C & container, T key, ManaPool::ManaCRef manaRef)
{
	auto it_pair = container.equal_range(key);
	auto it = std::find_if(it_pair.first, it_pair.second, [manaRef](auto e) {
		return e.second == manaRef;
	});
	if( it != it_pair.second ) {
		container.erase(it);
	}
}

void ManaPool::remove(ManaCRef manaRef)
{
	removeFrom(byColor,manaRef->color,manaRef);

	if( manaRef->source != 0 ) {
		removeFrom(bySource,manaRef->source,manaRef);
	}

	if( manaRef->annotations != 0 ) {
		for( unsigned a = 1; a <= Mana::lastAnnotation; a<<=1 ) {
			auto annotation = static_cast<Mana::Annotation>(manaRef->annotations & a);
			if( annotation != 0 ) {
				removeFrom(byAnnotation,annotation,manaRef);
			}
		}
	}

	pool.erase(manaRef);
}

} /* namespace mtg */
