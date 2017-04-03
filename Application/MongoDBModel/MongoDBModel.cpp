#include "pch.h"
#include "MongoDBModel.h"

void MongoDBModel::run()
{
	mongocxx::instance inst{};
	mongocxx::client conn{ mongocxx::uri{} };

	bsoncxx::builder::stream::document document{};

	auto collection = conn["testdb"]["testcollection"];
	document << "Hello" << "from UWP";

	collection.insert_one(document.view());
	auto cursor = collection.find({});
	/*
	for (auto&& doc : cursor) {
	std::cout << bsoncxx::to_json(doc) << std::endl;
	}*/
}
