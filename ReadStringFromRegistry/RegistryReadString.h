#pragma once

#include <atlstr.h>     // For CString

namespace win32
{
	// Read a string value (REG_SZ) from the registry.
	// Throws a CAtlException on errors.
	// This is a convenient wrapper around the RegGetValueW() Win32 function.
	//
	// RegGetValueW:
	// https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-reggetvaluew

	CString RegistryGetStringW(
		// A handle to an open registry key.
		// The key must have been opened with the KEY_QUERY_VALUE access right.
		// This corresponds the to hKey parameter in the RegGetValue() function.
		_In_		HKEY		hKey,

		// The name of the registry sub-key. 
		// This key must be a sub-key of the key specified by the "key" parameter.
		_In_opt_	LPCWSTR		lpSubKey,

		// The name of the registry string value.
		// If valueName is nullptr or an empty string, 
		// the function retrieves the type and data for the key's unnamed or 
		// default value, if any.
		_In_opt_	LPCWSTR		lpValue
	);
} // namespace win32

