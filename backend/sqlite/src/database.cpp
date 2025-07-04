#include "Typor/backend/sqlite/database.hpp"


namespace Typor::backend::sqlite {
	Database::~Database() {
		if (m_db != nullptr)
			sqlite3_close(m_db);
		m_db = nullptr;
	}


	auto Database::create(CreateInfos&& createInfos) noexcept
		-> Typor::Failable<Database>
	{
		std::filesystem::path dbFile {createInfos.directory / createInfos.name};
		dbFile.replace_extension("db");

		Database db {};
		if (sqlite3_open(dbFile.c_str(), &db.m_db) != 0) {
			auto dbPointer {db.m_db};
			db.m_db = nullptr;
			return Typor::MakeErrorStack("Can't open SQLite database : {}", sqlite3_errmsg(dbPointer));
		}
		return db;
	}
}
