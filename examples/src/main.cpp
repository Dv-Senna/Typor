#include <Typor/frontend.hpp>
#include <Typor/backend/backend.hpp>
#include <Typor/backend/sqlite/sqlite.hpp>
#include <Typor/error.hpp>


auto bar() -> Typor::Failable<int> {
	if (true)
		return Typor::MakeErrorStack("ERROR : {}", 69);
	return 42;
}

auto foo() -> Typor::Failable<int> {
	Typor::Failable barResult {bar()};
	if (!barResult)
		return Typor::AddToErrorStack(barResult, "2nd error");
	return 12 + *barResult;
}


int main(int, char**) {
	Typor::sayHello();
	Typor::backend::sqlite::sayHello();

	Typor::Failable fooResult {foo()};
	if (!fooResult)
		return Typor::logErrorStack(fooResult.error()), EXIT_FAILURE;

	return EXIT_SUCCESS;
}
