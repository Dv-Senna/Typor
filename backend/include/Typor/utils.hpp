#pragma once

#include <meta>
#include <optional>
#include <string_view>
#include <type_traits>


namespace Typor::utils {
	template <typename Enum>
	requires std::is_enum_v<Enum>
	constexpr auto toString(Enum value) noexcept -> std::optional<std::string_view> {
		constexpr auto enumerators {std::define_static_array(enumerators_of(^^Enum))};
		template for (constexpr auto e : enumerators) {
			if ([:e:] == value)
				return identifier_of(e);
		}
		return std::nullopt;
	}
}
