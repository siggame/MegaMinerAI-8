#include "lib/timeline/avl.h"
#include <iostream>

int main(int argc, char *argv[])
{
	Avl<int> avl;
	
	avl.insert(10,10);
	std::cout << *avl.get(10) << '\n';
	//test erase
	avl.erase(10);
	if (avl.get(10))
		std::cout << *avl.get(10) << '\n';
	
	//test reinserting after erasure
	avl.insert(10,15);
	std::cout << *avl.get(10) << '\n';
	if (avl.get(15))
		std::cout << *avl.get(15) << '\n';
	
	//test overwrite
	avl.insert(10,14);
	std::cout << *avl.get(10) << '\n';
	
	//test multi insert
	avl.insert(20,31);
	avl.insert(12,3255);
	avl.insert(1,912730);
	
	std::cout << *avl.get(1) << '\n';
	std::cout << *avl.get(20) << '\n';
	std::cout << *avl.get(12) << '\n';
	
	//test multi delete (ish)
	avl.erase(10); // root?
	std::cout << *avl.get(1) << '\n';
	std::cout << *avl.get(20) << '\n';
	std::cout << *avl.get(12) << '\n';
	
	avl.erase(20);
	std::cout << *avl.get(1) << '\n';
	std::cout << *avl.get(12) << '\n';
	
	if (!avl.get(20) &&	!avl.get(10))
	{
		std::cout << "Yay\n";
	}

	return 0;
}
