#include "master_include.hpp"

std::mutex marketLock;
std::condition_variable isPriceSatisfied;
Bazaar globalMarket;
std::vector<std::string> products = {"Underpants", "Hamburger", "Giant Lizard", "Toilet Paper", "Mystery Meat", "Vuvuzela", "Pikachu"};

//{ THREAD FUNCTIONS

void personThread() {
	Person myPerson( RNG::nextName(), RNG::nextInt(100,500), 0.0, RNG::nextInt(1,10)*0.1 );
	std::cout << myPerson.getName() << " has entered the market with $" << myPerson.getBalance() << ".\n" << std::endl;
	{
		std::string nextProduct = products.at(RNG::nextInt(0,products.size()-1));
		std::lock_guard<std::mutex> lock(marketLock);
		do {} while(myPerson.buyOrder(globalMarket.getProduct(nextProduct),RNG::nextInt(1,5)));
		std::cout << "=== " << myPerson.getName() << " bought " << nextProduct << " for $" << globalMarket.getValue(nextProduct) << "!!! ===\n";
	}
	std::cout << myPerson << std::endl;
	for(int i = 0; i < 30; i++) {
		if(myPerson.getOrders().empty()) break;
		std::chrono::milliseconds waitTime(RNG::nextInt(100,500));
		std::this_thread::sleep_for(waitTime);
		{
			std::lock_guard<std::mutex> lock(marketLock);			
			for(auto& order: myPerson.getOrders()) {
				if(myPerson.willSell(globalMarket.getProduct(order.first))) {
					myPerson.sellOrder(globalMarket.getProduct(order.first));
					std::cout << "=== " << myPerson.getName() << " sold " << order.first.name << "!!! ===\n";
				}
				else {
					//std::cout << "??? " << myPerson.getName() << " wanted to sell " << order.first.name << ", but they wanted it for $" << myPerson.calculateSellThreshold(order.first) << " vs. $" << globalMarket.getValue(order.first) << " ???\n"; 
				}
			}
		}
	} 
	std::cout << myPerson.getName() << " left the market with $" << myPerson.getBalance() << std::endl;		
}

void changePricing() {
	std::chrono::milliseconds waitTime(RNG::nextInt(100,2000));
	std::this_thread::sleep_for(waitTime);
	std::lock_guard<std::mutex> lock(marketLock);
	std::string nextProduct = products.at(RNG::nextInt(0,products.size()-1));
	double nextPrice = RNG::nextInt(200,1200) * 0.01;
	globalMarket.setValue(nextProduct,nextPrice);
	std::cout << "=== The price for " << nextProduct << " has changed to $" << nextPrice << "!!! ===\n";
	
}

//}

//{ TEST DRIVERS

void testDriver2();
void testDriver1();

void threadTest() {
	std::array<std::thread, 4> peopleThreadPool;
	std::thread marketThread;
	
	testDriver2();
	
	for(auto& p: peopleThreadPool) {
		p = std::thread(personThread);
	}
	
	for(int i = 0; i < 20; i++) {
		marketThread = std::thread(changePricing);
		marketThread.join();
	}
	
	for(auto& p: peopleThreadPool) {
		p.join();
	}
	
	globalMarket.printGoods();
	
}

//}

int main() {
	threadTest();
	return 0;
}

void testDriver2() {
	globalMarket.addProduct(product("Underpants",4.32));
	globalMarket.addProduct(product("Hamburger", 4.99));
	globalMarket.addProduct(product("Giant Lizard",12.31));
	globalMarket.addProduct(product("Toilet Paper",1.80));
	globalMarket.addProduct(product("Mystery Meat", 7.34));
	globalMarket.addProduct(product("Vuvuzela", 3.35));
	globalMarket.addProduct(product("Pikachu", 9.99));
	std::cout << "WELCOME" << std::endl;
	globalMarket.printGoods();
	std::cout << RNG::nextInt(14, 23) << std::endl;
}

void testDriver1() {
	product foo;
	foo.name = "Rutabaga";
	foo.value = 4.69;
	product baz;
	baz.name = "Turnip";
	baz.value = 9.24;
	Bazaar market;
	market.addProduct(foo);
	market.addProduct(baz);
	market.printGoods();
	Person qux("Billy Big Boy", 500);
	qux.buyOrder(foo, 4);
	qux.buyOrder(baz, 8);
	market.setValue("Rutabaga",10.94);
	market.printGoods();
	std::cout << qux << std::endl;
	std::cout << "He wants to sell Rutabaga at " << qux.calculateSellThreshold(market.getProduct(foo)) << std::endl;
}
