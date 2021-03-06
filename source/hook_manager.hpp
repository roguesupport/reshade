/**
 * Copyright (C) 2014 Patrick Mours. All rights reserved.
 * License: https://github.com/crosire/reshade#license
 */

#pragma once

#include "hook.hpp"
#include "filesystem.hpp"

#define HOOK_EXPORT extern "C"
#define VTABLE(object) (*reinterpret_cast<reshade::hook::address **>(object))

namespace reshade::hooks
{
	/// <summary>
	/// Install hook for the specified target function.
	/// </summary>
	/// <param name="target">The address of the target function.</param>
	/// <param name="replacement">The address of the hook function.</param>
	/// <returns>The status of the hook installation.</returns>
	bool install(hook::address target, hook::address replacement);
	/// <summary>
	/// Install hook for the specified virtual function table entry.
	/// </summary>
	/// <param name="vtable">The virtual function table pointer of the object to targeted object.</param>
	/// <param name="offset">The index of the target function in the virtual function table.</param>
	/// <param name="replacement">The address of the hook function.</param>
	/// <returns>The status of the hook installation.</returns>
	bool install(hook::address vtable[], unsigned int offset, hook::address replacement);
	/// <summary>
	/// Uninstall all previously installed hooks.
	/// </summary>
	void uninstall();
	/// <summary>
	/// Register the matching exports in the specified module and install or delay their hooking.
	/// </summary>
	/// <param name="path">The file path to the target module.</param>
	void register_module(const filesystem::path &path);

	/// <summary>
	/// Call the original/trampoline function for the specified hook.
	/// </summary>
	/// <param name="replacement">The address of the hook function which was previously used to install a hook.</param>
	/// <returns>The address of original/trampoline function.</returns>
	hook::address call(hook::address replacement);
	template <typename T>
	inline T call(T replacement)
	{
		return reinterpret_cast<T>(call(reinterpret_cast<hook::address>(replacement)));
	}
}
