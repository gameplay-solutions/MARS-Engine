#pragma once

#ifndef DELEGATE_IMPL_INCLUDED
	static_assert(false, "You must include Delegate.hpp before DelegateDefines.hpp");
#endif

#define DECLARE_DELEGATE(Object, Function, Instance) ConstructDelegate(&##Object::##Function, Instance);
#define DECLARE_DELEGATE_PARAMS(Object, Function, Instance, ...) ConstructDelegate(&##Object::##Function, Instance, __VA_ARGS__);

#define DECLARE_FREE_DELEGATE(Object, Function) ConstructDelegate(&##Object::##Function);