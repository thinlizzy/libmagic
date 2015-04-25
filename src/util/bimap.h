#ifndef BIMAP_H_GUARD_djfsafdsif
#define BIMAP_H_GUARD_djfsafdsif

#include <unordered_map>
#include <type_traits>

template<typename T, typename U, class HashT = std::hash<T>, class HashU = std::hash<U>>
class bimap {
	typedef std::unordered_map<T,U,HashT> left_type;
	typedef std::unordered_map<U,T,HashU> right_type;
	left_type left;
	right_type right;
	typedef typename std::conditional<std::is_scalar<T>::value,T,T const &>::type PT;
	typedef typename std::conditional<std::is_scalar<U>::value,U,U const &>::type PU;
public:
	void set(PT v1, PU v2) {
		left[v1] = v2;
		right[v2] = v1;
	}
	left_type & getLeft() { return left; }
	left_type const & getLeft() const { return left; }
	right_type & getRight() { return right; }
	right_type const & getRight() const { return right; }

	// TODO iterators and erase
};

#endif
