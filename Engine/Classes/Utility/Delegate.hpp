#pragma once

#include "CoreMinimal.h"

#define FUNC_CONCAT(...) __VA_ARGS__

template<typename ClassType>
class VariadicDelegate;

/*
 *	Member function Impl for a single bind delegate
 *	
 *	@Param ClassType: The type of the calling class.
 *	@Param Ret: The return type of the captured function.
 *	@Param Params: Variadic function signature.
 *	
 *	Callable == A pointer to a function
 *	Callee	 == The containing class of the member function
 *	
 *	Example:
 *	Callee.*Callable(Args...) == Math::Clamp(X, Min, Max)
 **/
template<typename ClassType, typename Ret, typename... Params>
class VariadicDelegate<Ret (ClassType::*)(Params...)>
{
public:

	using TypePtr = Ret (ClassType::*)(Params...);

	VariadicDelegate(TypePtr InCallable, ClassType& InCallee)
		: Callable(InCallable), Callee(InCallee)
	{}

	Ret operator()(Params... Args) const
	{
		return (Callee.*Callable)(Args...);
	}

	bool operator==(const VariadicDelegate& Other) const
	{
		return	(&Callee  == &Other.Callee) &&
				(Callable == Other.Callable);
	}

	bool operator!=(const VariadicDelegate& Other) const
	{
		return !((*this) == Other);
	}

private:

	TypePtr Callable;
	ClassType& Callee;
};

/*
 *	const member function impl of a single bind delegate
 **/
template<typename ClassType, typename Ret, typename... Params>
class VariadicDelegate<Ret(ClassType::*)(Params...) const>
{
public:

	using TypePtr = Ret (ClassType::*)(Params...) const;

	VariadicDelegate(TypePtr InCallable, ClassType& InCallee)
		: Callable(InCallable), Callee(InCallee)
	{}

	Ret operator()(Params... Args) const
	{
		return (Callee.*Callable)(Args...) const;
	}

	bool operator==(const VariadicDelegate& Other) const
	{
		return	(&this->Callee		== &Other.Callee) &&
				( this->Callable	== Other.Callable);
	}

	bool operator!=(const VariadicDelegate& Other) const
	{
		return !((*this) == Other);
	}

private:

	const ClassType& Callee;
	TypePtr Callable;
};

/*
 *	Free function impl of a single bind delegate
 **/
template<typename Ret, typename ...Params>
class VariadicDelegate<Ret(*)(Params...)>
{
public:

	using TypePtr = Ret (*)(Params...);

	VariadicDelegate(TypePtr InCallable)
		: Callable(InCallable)
	{}

	Ret operator()(Params... Args) const
	{
		return (*Callable)(Args...);
	}

	bool operator==(const VariadicDelegate& Other) const
	{
		return this->Callable == Other.Callable;
	}

	bool operator!=(const VariadicDelegate& Other) const
	{
		!((*this) == Other);
	}

private:

	TypePtr Callable;
};

template<typename Function, typename Class>
VariadicDelegate<Function> ConstructDelegate(Function InFunction, Class InClass)
{
	return VariadicDelegate<Function>(InFunction, InClass);
}

template<typename Function>
VariadicDelegate<Function> ConstructDelegate(Function InFunction)
{
	return VariadicDelegate<Function>(InFunction);
}

#define DELEGATE_IMPL_INCLUDED