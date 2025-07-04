#pragma once

#include <filesystem>
#include <string_view>

#include "Typor/error.hpp"


namespace Typor::backend {
	struct DatabaseDescription {
		std::string_view name;
		std::filesystem::path directory;
	};

	template <typename T>
	concept database = requires(T database, typename T::CreateInfos createInfos) {
		typename T::CreateInfos;
		{T::create(std::move(createInfos))} -> std::same_as<Typor::Failable<T>>;
	}
		&& std::movable<T>
		&& !std::copyable<T>
		&& std::is_aggregate_v<typename T::CreateInfos>
		&& std::constructible_from<typename T::CreateInfos, DatabaseDescription>;
}
