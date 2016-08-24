#pragma once
#include <functional>
#include <type_traits>
#include <utility>

namespace callback {

template <typename T>
struct Callback;

template <typename Ret, typename... Params>
struct Callback<Ret (*) (Params...)>
{
	template <typename... Args>
	static Ret callback(Args... args)
	{
		return func(args...);
	}
	static std::function<Ret(Params...)> func;
};

template <typename Ret, typename... Params>
std::function<Ret(Params...)> Callback<Ret (*)(Params...)>::func;

template<int I>
struct Placeholder{};

template <std::size_t... Is>
struct Indices {};

template <std::size_t N, std::size_t... Is>
struct BuildIndices: BuildIndices<N-1, N-1, Is...> {};

template <std::size_t... Is>
struct BuildIndices<0, Is...> : Indices<Is...> {};

namespace detail {

template<std::size_t... Is, class Func, class... Args>
auto PlaceholderInsertingBind(Indices<Is...>, Func func, Args&&... args)
{
	return std::bind(func, std::forward<Args>(args)..., Placeholder<Is + 1>{}...);
}

} // namespace detail

template<class R, class C, class... FArgs, class... Args>
auto PlaceholderInsertingBind(R (C::*func) (FArgs...), Args&&... args)
{
	return detail::PlaceholderInsertingBind(BuildIndices<sizeof...(FArgs)>{}, func, std::forward<Args>(args)...);
}

template<class Caller, class Ret, class... FArgs>
auto MakeCallback(Ret (Caller::* caller_member) (FArgs ...), Caller* caller)
{
	using CallbackType = Ret (*) (FArgs ...);
	Callback<CallbackType>::func = PlaceholderInsertingBind(caller_member, caller);
	return static_cast<CallbackType>(Callback<CallbackType>::callback);
}

} //namespace callback

namespace std {

template<int I>
struct is_placeholder<callback::Placeholder<I>> : std::integral_constant<int, I>{};

} // namespace std
