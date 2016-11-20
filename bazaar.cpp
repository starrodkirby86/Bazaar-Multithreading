#include "master_include.hpp"
 
std::ostream& operator<<(std::ostream& os, const product& obj)
{
	os << "[" << obj.name << " | " << obj.value << "]";
	return os;
} 

Bazaar::Bazaar() {
	
}
 
void Bazaar::addProduct(product p) {
	auto findResult = std::find_if(std::begin(goods), std::end(goods),
	[=](const product& i){ return i == p; });
	if( findResult == std::end(goods) )
		goods.push_back(p);
}

void Bazaar::removeProduct(product p) {
	goods.erase(std::remove_if(std::begin(goods), std::end(goods),
	[=](const product& i){ return i == p; }));
}

product Bazaar::getProduct(product p) {
	auto findResult = std::find_if(std::begin(goods), std::end(goods),
	[=](const product& i){ return i == p; });
	if( findResult != std::end(goods) ) {
		return *findResult;
	}
	return product();	
}

product Bazaar::getProduct(std::string name) {
	auto findResult = std::find_if(std::begin(goods), std::end(goods),
	[=](const product& i){ return i.name == name; });
	if( findResult != std::end(goods) ) {
		return *findResult;
	}
	return product();	
}

double Bazaar::getValue(product p) {
	auto findResult = std::find_if(std::begin(goods), std::end(goods),
	[=](const product& i){ return i == p; });
	if( findResult != std::end(goods) ) {
		product myProduct = *findResult;
		return myProduct.value;
	}
	return -1;
}

double Bazaar::getValue(std::string name) {
	auto findResult = std::find_if(std::begin(goods), std::end(goods),
	[=](const product& i){ return i.name == name; });
	if( findResult != std::end(goods) ) {
		product myProduct = *findResult;
		return myProduct.value;
	}
	return -1;
}

void Bazaar::setValue(product p, double newValue) {
	auto findResult = std::find_if(std::begin(goods), std::end(goods),
	[=](product& i){ return i == p; });
	if( findResult != std::end(goods) )
		findResult->value = newValue;
}

void Bazaar::setValue(std::string name, double newValue) {
	auto findResult = std::find_if(std::begin(goods), std::end(goods),
	[=](product& i){ return i.name == name; });
	if( findResult != std::end(goods) )
		findResult->value = newValue;
}


void Bazaar::printGoods() {
	std::for_each(std::begin(goods), std::end(goods),
	[](const product& p){ std::cout << p << std::endl; });
}
