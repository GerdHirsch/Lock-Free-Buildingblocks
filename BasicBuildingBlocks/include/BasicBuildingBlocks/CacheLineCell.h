#ifndef INCLUDE_BASICBUILDINGBLOCKS_CACHELINECELL_H_
#define INCLUDE_BASICBUILDINGBLOCKS_CACHELINECELL_H_

#include <cstddef>
#include <new>

template<class ElementType>
struct AlignmentCalculator{
	static constexpr size_t calculateAlignment(std::size_t elementsPerCacheLine){
//		using std::hardware_destructive_interference_size; // C++17
		constexpr std::size_t hardware_destructive_interference_size = 64; //Byte
		constexpr std::size_t cacheLineSize = hardware_destructive_interference_size;
		constexpr std::size_t elementAlignment = alignof(ElementType);

		constexpr std::size_t newAlignment = elementAlignment;
//		constexpr std::size_t newAlignment = cacheLineSize / elementsPerCacheLine;


		return newAlignment;
	}

};

template<class ElementType, std::size_t ElementsPerCacheLine>
class
CacheLineCell{
	using this_type = CacheLineCell<ElementType, ElementsPerCacheLine>;

	static constexpr size_t calculateAlignment(){
//		using std::hardware_destructive_interference_size; // C++17
		constexpr std::size_t hardware_destructive_interference_size = 64; //Byte

		constexpr std::size_t cacheLineSize = hardware_destructive_interference_size;
		constexpr std::size_t elementAlignment = alignof(ElementType);
		constexpr std::size_t alignmentForCacheLine = cacheLineSize / ElementsPerCacheLine;

		constexpr std::size_t newAlignment = elementAlignment > alignmentForCacheLine ?
				elementAlignment : alignmentForCacheLine;

		return newAlignment;
	}
	static constexpr std::size_t alignment = calculateAlignment();

	alignas(alignment) unsigned char elementBuffer[sizeof(ElementType)];


public:
	template<class... Args>
	CacheLineCell(Args&& ...args){
		new(&elementBuffer) ElementType(std::forward<Args>(args)...);
	}
	template<class... Args>
	void emplace(Args&& ...args){
		new(&elementBuffer) ElementType(std::forward<Args>(args)...);
	}
	operator ElementType&(){ return *reinterpret_cast<ElementType*>(elementBuffer); }
//	operator ElementType&&(){ return *reinterpret_cast<ElementType*>(elementBuffer); }
};



#endif /* INCLUDE_BASICBUILDINGBLOCKS_CACHELINECELL_H_ */
