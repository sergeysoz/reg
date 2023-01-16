#include ".\RegistryCreateKey.h"
#include <Windows.h>                // Win32 SDK
#include <atldef.h>                 // Some ATL stuff

namespace win32
{
	typedef DWORD SECURITY_INFORMATION, * PSECURITY_INFORMATION;

	int RegistryCreateKey(
		_In_		HKEY	hKey,
		_In_opt_	LPCSTR	lpSubKey,
		_Out_		PHKEY	phkResult
	)
	{
		LONG result = ::RegGetKeySecurity(
			hKey,
			ATTRIBUTE_SECURITY_INFORMATION,
			nullptr,
			nullptr
		);

		if (result != 0) return 1;
		return 0;
	}
}