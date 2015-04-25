#include "../TypeToStr.h"
#include <unordered_map>

namespace mtg {

ArtifactType parseArtifactType(std::string const & value) {
	static std::unordered_map<std::string,ArtifactType> map;
	if( map.empty() ) {
		map["equipment"] = equipment;
		map["fortification"] = fortification;
	}
	return map.at(value);
}

std::string ArtifactTypeStr(ArtifactType value) {
	switch(value) {
	case equipment:
		return "equipment";
	case fortification:
		return "fortification";
	default:
		return value == 0 ? "0" : "unknown";
	}
}

}
