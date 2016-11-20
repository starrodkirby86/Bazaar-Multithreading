/*
 * person.hpp
 * These are lowly customers. They have a buy/sell threshold
 * that they'll behave on when it comes to buying and selling.
 */
 
 #include "master_include.hpp"

class Person {
	private:
		std::string name;
		double balance;
		double buyThreshold;
		double sellThreshold;
		std::vector<std::pair<product, int>> orders;
	public:
		Person(std::string name="John Doe", double balance = 100, double buyThreshold = 0.1, double sellThreshold=0.5);
		std::string getName() const { return name; }
		double const getBalance() const { return balance; }
		double calculateSellThreshold(product p);
		std::vector<std::pair<product, int>> getOrders() const { return orders; }
		bool buyOrder(product p, int quantity);
		void sellOrder(product p);
		bool canAfford(product productToCheck, int quantity);
		bool willSell(product productToCheck);
	
	friend inline std::ostream& operator<<(std::ostream& os, const Person& obj)
	{
		auto myOrders = obj.getOrders();
		os << obj.getName() << ": $" << obj.getBalance() << "\n[ ";
		std::for_each(std::begin(myOrders), std::end(myOrders), [&](const std::pair<product,int>& i){ os << (i.first).name << ": " << i.second << " "; });
		os << "]";
		return os;
	} 
};
