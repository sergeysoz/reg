#include "RegistryReadString.h"
#include <stdio.h>
#include <iostream>

#define pause system("pause");

int main()
{
	static const int kExitOk = 0;
	static const int kExitError = 1;

	try
	{
		// Read some test string from the registry
		CString str = win32::RegistryGetStringW(
			HKEY_LOCAL_MACHINE,
			L"SOFTWARE\\ODBC\\ODBCINST.INI\\ODBC Drivers",
			L"SQL Server");

		// Print the read string
		wprintf(L"UTM Connector has started\n");
		wprintf(L"String read from registry:\n\n");
		wprintf(L"  \"%s\"\n", str.GetString());

		// Make sure that the string length is correct
		const CString underline(L'*', str.GetLength());
		wprintf(L"   %s\n\n", underline.GetString());
		wprintf(L"(Length = %d)\n\n", str.GetLength());

		system("pause");
		return kExitOk;
	}
	catch (const CAtlException& e)
	{
		wprintf(L"\n*** ERROR: HResult=0x%08X\n", static_cast<HRESULT>(e));

		system("pause");
		return kExitError;
	}


}

