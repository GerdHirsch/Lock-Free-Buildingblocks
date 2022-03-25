/*
 * experiment mit named parameters for templates
 * & type factory
 */

#include <BasicBuildingBlocks/TypeBuilder.h>

#include <iostream>
#include <type_traits>


using namespace std;

void demoTypeBuilder(){
	cout << __PRETTY_FUNCTION__ << endl;

	using DefaultTypeBuilder = TypeBuilder2<>;
	using MMQueue = DefaultTypeBuilder::getQueue<int, 5>;
	MMQueue queue;
	queue.print();
	using SMBuilder = DefaultTypeBuilder::setProducer<Single>;
	using SMQueue = SMBuilder::getQueue<int, 5>;
	SMQueue smQueue;
	smQueue.print();

	using DefaultTypeFactory = TypeBuilder<>;
	cout << "=== Multi Multi" << endl;
	{
		using MyTypeFactory = DefaultTypeFactory;
		MyTypeFactory::Producer::print();
		MyTypeFactory::Consumer::print();
	}
	cout << "=== Single Multi" << endl;
	{
		using MyTypeFactory = DefaultTypeFactory
				::setProducer<Single>
		;

		MyTypeFactory::Producer::print();
		MyTypeFactory::Consumer::print();
	}
	cout << "=== Single Single" << endl;
	{
		using MyTypeFactory = DefaultTypeFactory
				::setConsumer<Single>
				::setProducer<Single>
		;

		MyTypeFactory::Producer::print();
		MyTypeFactory::Consumer::print();
	}
	cout << "=== Multi Single" << endl;
	{
		using MyTypeFactory = DefaultTypeFactory
				::setConsumer<Single>
				::setProducer<Multi>
		;

		MyTypeFactory::Producer::print();
		MyTypeFactory::Consumer::print();
	}
	cout << "=== Multi Single - Single Multi" << endl;
	{
		using MyTypeFactory = DefaultTypeFactory
				::setConsumer<Single>
				::setProducer<Multi>
		;
		using AnotherFactory =  MyTypeFactory
				::setProducer<Single>
				::setConsumer<Multi>
		;

		MyTypeFactory::Producer::print();
		MyTypeFactory::Consumer::print();
		AnotherFactory::Producer::print();
		AnotherFactory::Consumer::print();
	}
}
