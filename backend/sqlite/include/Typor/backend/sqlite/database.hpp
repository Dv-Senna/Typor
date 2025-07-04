#pragma once

#include <memory>

#include <sqlite3.h>

#include "Typor/backend/database.hpp"
#include "Typor/error.hpp"


namespace Typor::backend::sqlite {
	class Database final {
		Database(const Database&) = delete;
		auto operator=(const Database&) = delete;

		public:
			constexpr Database() noexcept : m_db {nullptr} {}
			~Database();

			constexpr Database(Database&& db) noexcept : m_db {db.m_db} {db.m_db = nullptr;}
			constexpr auto operator=(Database&& db) noexcept -> Database& {
				m_db = db.m_db;
				db.m_db = nullptr;
				return *this;
			}

			using CreateInfos = Typor::backend::DatabaseDescription;

			static auto create(CreateInfos&& createInfos) noexcept
				-> Typor::Failable<Database>;


		private:
			sqlite3 *m_db;
	};

	static_assert(Typor::backend::database<Database>);
}
