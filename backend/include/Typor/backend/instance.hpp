#pragma once

#include <memory>

#include "Typor/backend/database.hpp"
#include "Typor/error.hpp"


namespace Typor::backend {
	class Instance {
		Instance(const Instance&) = delete;
		auto operator=(const Instance&) -> Instance& = delete;

		public:
			constexpr Instance() noexcept = default;
			constexpr virtual ~Instance() = default;
			constexpr Instance(Instance&&) noexcept = default;
			constexpr auto operator=(Instance&&) noexcept -> Instance& = default;

			virtual auto makeDatabase(Typor::backend::Database::CreateInfos&&) noexcept
				-> Typor::Failable<std::unique_ptr<Typor::backend::Database>> = 0;
	};
}
