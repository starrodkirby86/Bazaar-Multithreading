#include "master_include.hpp"

Person::Person(std::string name, double balance, double buyThreshold, double sellThreshold) {
	this->name = name;
	this->balance = balance;
	this->buyThreshold = buyThreshold;
	this->sellThreshold = sellThreshold;
}

double Person::calculateSellThreshold(product p) {
	auto findResult = std::find_if(std::begin(orders), std::end(orders),
	[=](const std::pair<product,int>& i){ return i.first == p; });
	if( findResult != std::end(orders) ) {
		return (findResult->first).value * (1+sellThreshold);
	}
	return -1;
}

bool Person::buyOrder(product p, int quantity) {
	if(!canAfford(p, quantity)) return false;
	auto findResult = std::find_if(std::begin(orders), std::end(orders),
	[=](const std::pair<product,int>& i){ return i.first == p; });
	if( findResult == std::end(orders) ) {
		balance -= p.value * quantity;
		orders.push_back(std::make_pair(p, quantity));
	}
	else return false;
	return true;
}

void Person::sellOrder(product p) {
	auto findResult = std::find_if(std::begin(orders), std::end(orders),
	[=](const std::pair<product,int>& i){ return i.first == p; });
	if( findResult != std::end(orders) ) {
		balance += findResult->second * p.value; // This is the value currently at market
		orders.erase(findResult);
	}
}

bool Person::canAfford(product productToCheck, int quantity) {
	return balance >= productToCheck.value * quantity;
}

bool Person::willSell(product productToCheck) {
	return calculateSellThreshold(productToCheck) <= productToCheck.value;
}
