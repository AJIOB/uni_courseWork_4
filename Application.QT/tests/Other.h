#pragma once
#include <gtest/gtest.h>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

TEST(CheckTestsToWork, Hello)
{
	EXPECT_EQ("Hello", "Hello");
}

TEST(DB_Simple, tutorial)
{
	//mongocxx::instance inst{};
	mongocxx::client conn{mongocxx::uri{"mongodb://localhost:27017"}};

	bsoncxx::builder::stream::document document{};

	auto collection = conn["Library"]["testcollection"];
	document << "helloAJIOB" << "world";

	collection.insert_one(document.view());
	auto cursor = collection.find({});

	for (auto&& doc : cursor)
	{
		//std::cout << bsoncxx::to_json(doc) << std::endl;
	}
}
