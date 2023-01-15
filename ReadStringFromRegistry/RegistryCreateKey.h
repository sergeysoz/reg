#pragma once
#include <Windows.h> 

typedef LONG LSTATUS;

namespace win32
{
	LSTATUS RegistryCreateKey(
		_In_		HKEY	hKey,
		_In_opt_	LPCSTR	lpSubKey,
		_Out_		PHKEY	phkResult
	);
}

