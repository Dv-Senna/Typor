#pragma once

#include "Typor/backend/instance.hpp"
#include "Typor/backend/sqlite/database.hpp"


namespace Typor::backend::sqlite {
	class Instance final {
		Instance(const Instance&) = delete;
		auto operator=(const Instance&) -> Instance& = delete;

		public:
			constexpr Instance() noexcept = default;
			constexpr ~Instance() = default;
			constexpr Instance(Instance&&) noexcept = default;
			constexpr auto operator=(Instance&&) noexcept -> Instance& = default;

			struct CreateInfos {};

			static inline auto create(CreateInfos&&) noexcept -> Typor::Failable<Typor::backend::sqlite::Instance> {
				return Instance{};
			}


			inline auto makeDatabase(Typor::backend::sqlite::Database::CreateInfos &&createInfos) noexcept
				-> Typor::Failable<std::unique_ptr<Typor::backend::sqlite::Database>>
			{
				Typor::Failable db {Typor::backend::sqlite::Database::create(std::move(createInfos))};
				if (!db)
					return std::unexpected(std::move(db.error()));
				return std::make_unique<Typor::backend::sqlite::Database> (std::move(*db));
			}
	};

	static_assert(Typor::backend::instance<Instance, Typor::backend::sqlite::Database>);
}
