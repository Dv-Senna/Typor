#pragma once

#include <expected>
#include <format>
#include <iostream>
#include <optional>
#include <source_location>
#include <stack>
#include <string>

#include "Typor/utils.hpp"


namespace Typor {
	enum class ErrorCode : std::uint32_t {

	};

	struct ErrorFrame {
		const std::source_location location;
		const std::optional<ErrorCode> code {std::nullopt};
		const std::optional<std::string> message {std::nullopt};
	};


	class ErrorStack {
		ErrorStack(const ErrorStack&) = delete;
		auto operator=(const ErrorStack&) -> ErrorStack& = delete;

		public:
			constexpr ErrorStack() noexcept = default;
			constexpr ~ErrorStack() = default;
			constexpr ErrorStack(ErrorStack&&) noexcept = default;
			constexpr auto operator=(ErrorStack&&) noexcept -> ErrorStack& = default;

			inline auto push(ErrorFrame&& frame) noexcept -> void {m_frames.push(frame);}
			inline auto pop() noexcept -> ErrorFrame {
				ErrorFrame frame {std::move(m_frames.top())};
				m_frames.pop();
				return frame;
			}
			inline auto empty() const noexcept -> bool {return m_frames.empty();}


		private:
			std::stack<ErrorFrame> m_frames;
	};


	template <typename T>
	using Failable = std::expected<T, ErrorStack>;


	template <typename ...Args>
	class MakeErrorStack {
		public:
			constexpr MakeErrorStack(
				const std::source_location& location = std::source_location::current()
			) noexcept :
				m_stack {}
			{
				m_stack.push(ErrorFrame{
					.location = location,
					.code = std::nullopt,
					.message = std::nullopt
				});
			}

			constexpr MakeErrorStack(
				ErrorCode code,
				const std::source_location& location = std::source_location::current()
			) noexcept :
				m_stack {}
			{
				m_stack.push(ErrorFrame{
					.location = location,
					.code = code,
					.message = std::nullopt
				});
			}

			constexpr MakeErrorStack(
				std::format_string<Args...> fmt,
				Args&&... args,
				const std::source_location& location = std::source_location::current()
			) noexcept :
				m_stack {}
			{
				m_stack.push(ErrorFrame{
					.location = location,
					.code = std::nullopt,
					.message = std::format(fmt, std::forward<Args> (args)...)
				});
			}

			constexpr MakeErrorStack(
				ErrorCode code,
				std::format_string<Args...> fmt,
				Args&&... args,
				const std::source_location& location = std::source_location::current()
			) noexcept :
				m_stack {}
			{
				m_stack.push(ErrorFrame{
					.location = location,
					.code = code,
					.message = std::format(fmt, std::forward<Args> (args)...)
				});
			}

			template <typename T>
			constexpr operator Failable<T> () noexcept {
				return std::unexpected{std::move(m_stack)};
			}

		private:
			ErrorStack m_stack;
	};


	MakeErrorStack() -> MakeErrorStack<>;
	MakeErrorStack(ErrorCode) -> MakeErrorStack<>;
	template <typename ...Args>
	MakeErrorStack(
		std::format_string<Args...>,
		Args&&...
	) -> MakeErrorStack<Args...>;
	template <typename ...Args>
	MakeErrorStack(
		ErrorCode,
		std::format_string<Args...>,
		Args&&...
	) -> MakeErrorStack<Args...>;



	template <typename T, typename ...Args>
	class AddToErrorStack {
		public:
			AddToErrorStack(
				Failable<T>& stack,
				const std::source_location& location = std::source_location::current()
			) noexcept :
				m_stack {std::move(stack.error())}
			{
				m_stack.push(ErrorFrame{
					.location = location,
					.code = std::nullopt,
					.message = std::nullopt
				});
			}

			AddToErrorStack(
				Failable<T>& stack,
				ErrorCode code,
				const std::source_location& location = std::source_location::current()
			) noexcept :
				m_stack {std::move(stack.error())}
			{
				m_stack.push(ErrorFrame{
					.location = location,
					.code = code,
					.message = std::nullopt
				});
			}

			AddToErrorStack(
				Failable<T>& stack,
				std::format_string<Args...> fmt,
				Args&&... args,
				const std::source_location& location = std::source_location::current()
			) noexcept :
				m_stack {std::move(stack.error())}
			{
				m_stack.push(ErrorFrame{
					.location = location,
					.code = std::nullopt,
					.message = std::format(fmt, std::forward<Args> (args)...)
				});
			}

			AddToErrorStack(
				Failable<T>& stack,
				ErrorCode code,
				std::format_string<Args...> fmt,
				Args&&... args,
				const std::source_location& location = std::source_location::current()
			) noexcept :
				m_stack {std::move(stack.error())}
			{
				m_stack.push(ErrorFrame{
					.location = location,
					.code = code,
					.message = std::format(fmt, std::forward<Args> (args)...)
				});
			}

			template <typename U>
			constexpr operator Failable<U> () noexcept {
				return std::unexpected{std::move(m_stack)};
			}

		private:
			ErrorStack m_stack;
	};


	template <typename T>
	AddToErrorStack(Failable<T>&) -> AddToErrorStack<T>;
	template <typename T>
	AddToErrorStack(Failable<T>&, ErrorCode) -> AddToErrorStack<T>;
	template <typename T, typename ...Args>
	AddToErrorStack(Failable<T>&, std::format_string<Args...>, Args&&...) -> AddToErrorStack<T, Args...>;
	template <typename T, typename ...Args>
	AddToErrorStack(Failable<T>&, ErrorCode, std::format_string<Args...>, Args&&...)
		-> AddToErrorStack<T, Args...>;


	inline auto logErrorStack(ErrorStack &stack, std::ostream &stream = std::cerr) noexcept {
		std::println(stream, "Error stack :");
		while (!stack.empty()) {
			auto error {stack.pop()};
			std::println("\t-{} in {} ({}:{}) > {}",
				error.code ? Typor::utils::toString(*error.code).value_or("<invalid>") : "",
				error.location.function_name(),
				error.location.file_name(), error.location.line(),
				error.message.value_or("<no message>")
			);
		}
	}


	template <typename T>
	struct is_failable : std::false_type {};

	template <typename T>
	struct is_failable<Failable<T>> : std::true_type {};

	template <typename T>
	concept failable = is_failable<T>::value;
}
