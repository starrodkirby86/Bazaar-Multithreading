/*
 * bazaar.hpp
 * This is the market bazaar that manages facilitation of
 * products and goods.
 */
 
 #include "master_include.hpp"
 
 struct product {
	 std::string name;
	 double value;
	 friend bool operator==(const product& l, const product& r) { return l.name == r.name; }
	 product(std::string name = "Dummy", double value = 1) { this->name = name; this->value = value; }
 };

class Bazaar {
	private:
		std::vector<product> goods;
	public:
		Bazaar();
		void addProduct(product p);
		void removeProduct(product p);
		product getProduct(product p);
		product getProduct(std::string name);
		double getValue(product p);
		double getValue(std::string name);
		void setValue(product p, double newValue);
		void setValue(std::string name, double newValue);
		void printGoods();
};
