#include "master_include.hpp"

int RNG::nextInt(int lo, int hi) {
	auto const seed = std::random_device()();
	std::mt19937 rngFormula(seed);
	std::uniform_int_distribution<int> range(lo, hi);
	return range(rngFormula);
}

std::string RNG::nextName() {
	switch(nextInt(0, 11)) {
		case 0:
			return "Jonathan";
		case 1:
			return "Wallace";
		case 2:
			return "Bethany";
		case 3:
			return "Shigeru";
		case 4:
			return "Miku";
		case 5:
			return "Hassan";
		case 6:
			return "Mikhail";
		case 7:
			return "Priti";
		case 8:
			return "Shaka";
		case 9:
			return "Linus";
		case 10:
			return "Miranda";	
		default:
			return "Pollack";
	}
}
