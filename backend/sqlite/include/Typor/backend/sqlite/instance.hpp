#pragma once

#include "Typor/backend/instance.hpp"
#include "Typor/backend/sqlite/database.hpp"


namespace Typor::backend::sqlite {
	class Instance final : public Typor::backend::Instance {
		public:
			constexpr Instance() noexcept = default;
			constexpr ~Instance() override = default;
			constexpr Instance(Instance&&) noexcept = default;
			constexpr auto operator=(Instance&&) noexcept -> Instance& = default;

			static inline auto create() noexcept -> Typor::Failable<Typor::backend::sqlite::Instance> {
				return Instance{};
			}


			inline auto makeDatabase(Typor::backend::Database::CreateInfos&& createInfos) noexcept
				-> Typor::Failable<std::unique_ptr<Typor::backend::Database>> override
			{
				Typor::Failable db {Typor::backend::sqlite::Database::create(std::move(createInfos))};
				if (!db)
					return std::unexpected(std::move(db.error()));
				return std::make_unique<Typor::backend::sqlite::Database> (std::move(*db));
			}
	};
}
