#include <Typor/frontend.hpp>
#include <Typor/backend/backend.hpp>
#include <Typor/backend/sqlite/sqlite.hpp>


int main(int, char**) {
	Typor::sayHello();
	Typor::backend::sayHello();
	Typor::backend::sqlite::sayHello();
	return 0;
}
