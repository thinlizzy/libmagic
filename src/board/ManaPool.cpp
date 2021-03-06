#include "ManaPool.h"
#include <iterator>
#include <algorithm>

namespace mtg {

void ManaPool::clear()
{
	byColor.clear();
	bySource.clear();
	pool.clear();
}

auto ManaPool::add(Color color, Mana::Source source) -> ManaRef
{
	pool.push_back({color,source});
	auto manaRef = std::prev(pool.end());
	byColor.insert({color,manaRef});
	if( source != 0 ) {
		bySource.insert({source,manaRef});
	}
	return manaRef;
}

auto ManaPool::getByColor(Color color) const -> ColorRange
{
	return ColorRange{byColor.equal_range(color)};
}

auto ManaPool::getBySource(Mana::Source source) const -> SourceRange
{
	return SourceRange{bySource.equal_range(source)};
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

	pool.erase(manaRef);
}

} /* namespace mtg */
