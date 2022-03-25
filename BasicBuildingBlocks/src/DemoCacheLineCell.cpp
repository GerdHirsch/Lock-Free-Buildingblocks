

#include <BasicBuildingBlocks/CacheLineCell.h>

#include <iostream>
#include <array>
using namespace std;

struct
//alignas(2)
MyType{
	static constexpr std::size_t MAX=1;
	char bytes[MAX];

	std::ostream& print(std::ostream& out){
		cout << "[";
		for(std::size_t i = 0; i<MAX-1; ++i)
			out << static_cast<int>(bytes[i]) <<", ";
		out << static_cast<int>(bytes[MAX-1]) << "]";
		out << endl;
		return out;
	}
};


void demoCacheLineCell(){
	cout << "demoCacheLineCell" << endl << endl;
//	using ElementType = int;
	using ElementType = MyType;

//	MyType myType = { 1, 2, 3};
	MyType myType = { 1 };

	constexpr std::size_t elementsPerCacheLine = 64;
	constexpr std::size_t numElements = 20;

	using Cell = CacheLineCell<ElementType, elementsPerCacheLine>;

	Cell cells[numElements];
	std::array<Cell, numElements> aCells;

	cells[0].emplace(std::move(myType));
//	cells[0].emplace(myType);
//	MyType obj(std::move(cells[0]));
	MyType obj(cells[0]);
	obj.print(cout);


	cout << "alignof(ElementType): " << alignof(ElementType) << endl;
	cout << "alignof(Cell): " << alignof(Cell) << endl;
	cout << endl;
	cout << "sizeof(ElementType): " << sizeof(ElementType) << endl;
	cout << "sizeof(Cell): " << sizeof(Cell) << endl;
	cout << "sizeof(cells): " << sizeof(cells) << endl;
	cout << "sizeof(aCells): " << sizeof(aCells) << endl;
}
