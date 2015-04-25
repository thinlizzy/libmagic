// this file is only included by generated.h

#include <string>
#include "../ArtifactType.h"

namespace mtg {

ArtifactType parseArtifactType(std::string const & value);
std::string ArtifactTypeStr(ArtifactType value);

template<>
struct TypeToStr<ArtifactType> {
	static std::string toString(ArtifactType value) { return ArtifactTypeStr(value); }
};

template<>
struct StrToType<ArtifactType> {
	static ArtifactType toType(std::string const & value) { return parseArtifactType(value); }
};

}

