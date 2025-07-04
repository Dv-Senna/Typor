#pragma once

#include <memory>

#include <sqlite3.h>

#include "Typor/backend/database.hpp"
#include "Typor/error.hpp"


namespace Typor::backend::sqlite {
	class Database final : public Typor::backend::Database {
		public:
			constexpr Database() noexcept : m_db {nullptr} {}
			~Database() override;

			constexpr Database(Database&& db) noexcept : m_db {db.m_db} {db.m_db = nullptr;}
			constexpr auto operator=(Database&& db) noexcept -> Database& {
				m_db = db.m_db;
				db.m_db = nullptr;
				return *this;
			}

			static auto create(Typor::backend::Database::CreateInfos &&createInfos) noexcept
				-> Typor::Failable<Database>;


		private:
			sqlite3 *m_db;
	};
}
