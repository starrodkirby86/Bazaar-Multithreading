/*
 * rng.hpp
 * An easily accessible RNG class.
 */

#include "master_include.hpp"

class RNG {
	private:
	public:
		static int nextInt(int lo, int hi);
		static std::string nextName();
};
