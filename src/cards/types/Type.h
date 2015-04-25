#ifndef SUBTYPE_H_LIBMAGIC_2015_04_17
#define SUBTYPE_H_LIBMAGIC_2015_04_17

#include <string>

namespace mtg {

// TODO make sure all subtype enums don't use 0 value
// TODO make Card use this class for subtypes
template<typename E>
struct Type {
	E subtype;
	std::string original;
private:
	bool noEnum() const {
		return subtype == E{};
	}

public:
	bool unsupported() const {
		return noEnum() && ! original.empty();
	}

	bool operator==(Type const & st) const {
		if( noEnum() ) return original == st.original;
		return subtype == st.subtype;
	}
};

}
#endif
