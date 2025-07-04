#pragma once

#include <filesystem>
#include <string_view>


namespace Typor::backend {
	class Database {
		Database(const Database&) = delete;
		auto operator=(const Database&) -> Database& = delete;

		public:
			struct CreateInfos {
				std::string_view name;
				std::filesystem::path directory;
			};

			constexpr Database() noexcept = default;
			constexpr virtual ~Database() = default;
			constexpr Database(Database&&) noexcept = default;
			constexpr auto operator=(Database&&) noexcept -> Database& = default;
	};
}
