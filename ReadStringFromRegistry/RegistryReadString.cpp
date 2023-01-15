#include "RegistryReadString.h"     // Module header
#include <Windows.h>                // Win32 SDK
#include <atldef.h>                 // Some ATL stuff

namespace win32
{
	CString RegistryGetStringW(
		_In_		HKEY		hKey,
		_In_opt_	LPCWSTR		lpSubKey,
		_In_opt_	LPCWSTR		lpValue
	)
	{
		// Try getting the size of the string value to read,
		// to properly allocate a buffer for the string
		DWORD keyType = 0;
		DWORD dataSize = 0;

		const DWORD flags = RRF_RT_REG_SZ;		// Only read strings (REG_SZ)
		LONG result = ::RegGetValueW(
			hKey,
			lpSubKey,
			lpValue,
			flags,
			&keyType,
			nullptr,							// pvData == nullptr --> Request buffer size for string
			&dataSize
		);

		// Error: throw an exception to signal if
		if (result != ERROR_SUCCESS) AtlThrow(HRESULT_FROM_WIN32(result));

		// Make sure we are reading a REG_SZ
		ATLASSERT(keyType == REG_SZ);

		// Allocate enough memory to store the text
		CString text;
		const DWORD bufferLength = dataSize / sizeof(WCHAR);		// length in WCHAR's
		WCHAR* const textBuffer = text.GetBuffer(bufferLength);
		ATLASSERT(textBuffer != nullptr);

		// Read that string value text from the Windows registry
		result = ::RegGetValueW(
			hKey,
			lpSubKey,
			lpValue,
			flags,
			nullptr,
			textBuffer,
			&dataSize
		);

		if (result != ERROR_SUCCESS) AtlThrow(HRESULT_FROM_WIN32(result));

		ATLASSERT(keyType == REG_SZ);

		// Recalculate string buffer length, since it seems in the second call
		// to RegGetValue() (when a valid buffer pointer is passed to 
		// that function), the returned dataSize is *different* (smaller) 
		// than in the previous call.
		//
		// See this question on Stack Overflow:
		//  http://stackoverflow.com/q/29223180/1629821

		const DWORD actualStringLength = dataSize / sizeof(WCHAR);
		text.ReleaseBufferSetLength(actualStringLength - 1);

		return text;
	};
} // namespace win32

