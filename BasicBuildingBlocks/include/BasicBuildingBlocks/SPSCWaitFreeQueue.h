#ifndef INCLUDE_BASICBUILDINGBLOCKS_SPSCWAITFREEQUEUE_H_
#define INCLUDE_BASICBUILDINGBLOCKS_SPSCWAITFREEQUEUE_H_

#include <array>
#include <atomic>
#include <cstddef>
#include <iostream>

template<class ElementType, std::size_t MaxElements>
class SPSCWaitFreeQueue{
public:
	void print(){ std::cout << "SingleProducerSingleConsumerWaitFreeQueue" << std::endl; }

	bool push(ElementType const &newElement){
		auto oldWritePos = writePosition.load(std::memory_order_relaxed);
		auto newWritePos = getPositionAfter(oldWritePos);

		// Queue full
		if(newWritePos == readPosition.load(std::memory_order_relaxed))
			return false;

		ringBuffer[oldWritePos] = newElement;

		writePosition.store(newWritePos, std::memory_order_release);
		return true;
	}

	bool pop(ElementType& returnedElement){
		auto oldWritePos = writePosition.load(std::memory_order_acquire);
		auto oldReadPos  = readPosition.load(std::memory_order_relaxed);

		//Queue empty
		if(oldWritePos == oldReadPos)
			return false;

		returnedElement = std::move(ringBuffer[oldReadPos]);

		readPosition.store(getPositionAfter(oldReadPos), std::memory_order_relaxed);
		return true;

	}

private:
	static constexpr std::size_t getPositionAfter(std::size_t position){
		return ++position == ringBufferSize ? 0 : position;
	}
	std::atomic<size_t> writePosition{};
	std::atomic<size_t> readPosition{};
	static constexpr std::size_t ringBufferSize = MaxElements + 1;
	std::array<ElementType, ringBufferSize> ringBuffer;
};



#endif /* INCLUDE_BASICBUILDINGBLOCKS_SPSCWAITFREEQUEUE_H_ */
