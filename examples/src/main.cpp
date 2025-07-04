#include <Typor/frontend.hpp>
#include <Typor/backend/sqlite/instance.hpp>
#include <Typor/error.hpp>


int main(int, char**) {
	Typor::Failable instanceWithError {Typor::backend::sqlite::Instance::create({})};
	if (!instanceWithError)
		return Typor::logErrorStack(instanceWithError.error()), EXIT_FAILURE;
	auto instance {std::move(*instanceWithError)};

	Typor::Failable databaseWithError {instance.makeDatabase(Typor::backend::sqlite::Database::CreateInfos{
		.name = "database",
		.directory = "./build"
	})};
	if (!databaseWithError)
		return Typor::logErrorStack(databaseWithError.error()), EXIT_FAILURE;
	auto database {std::move(*databaseWithError)};

	std::println("Open database");
	return EXIT_SUCCESS;
}
