#pragma once

#include "Typor/backend/database.hpp"
#include "Typor/error.hpp"


namespace Typor::backend {
	template <typename T, typename DB>
	concept instance = requires(
		T instance,
		typename T::CreateInfos createInfos,
		typename DB::CreateInfos dbCreateInfos
	) {
		typename T::CreateInfos;
		{T::create(std::move(createInfos))} -> std::same_as<Typor::Failable<T>>;
		{instance.makeDatabase(std::move(dbCreateInfos))} -> Typor::failable;
	}
		&& Typor::backend::database<DB>
		&& std::movable<T>
		&& !std::copyable<T>
		&& std::is_aggregate_v<typename T::CreateInfos>;
}
