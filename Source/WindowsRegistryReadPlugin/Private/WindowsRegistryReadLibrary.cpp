
#include "WindowsRegistryReadLibrary.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include <windows.h>

FString UWindowsRegistryReadLibrary::ReadRegistryValue(const FString& RegistryPath, const FString& ValueName, bool bIs64BitKey, bool& bSuccess)
{
#if PLATFORM_WINDOWS
    HKEY hKey;
    DWORD dwType = REG_SZ;
    TCHAR Data[1024]; //Should be plenty for most situations
    DWORD dwSize = sizeof(Data);
    bSuccess = false; //Success is not default

    // Define registry access mode
    REGSAM samDesired = KEY_READ;
    if (bIs64BitKey)
    {
        samDesired |= KEY_WOW64_64KEY;
    }
    else
    {
        samDesired |= KEY_WOW64_32KEY;
    }

    // Open the registry key
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, *RegistryPath, 0, samDesired, &hKey) != ERROR_SUCCESS)
    {
        return TEXT("ERROR: Cannot open registry key.");
    }

    // Query the value
    LONG result = RegQueryValueEx(hKey, ValueName.IsEmpty() ? nullptr : *ValueName, nullptr, &dwType, (LPBYTE)&Data, &dwSize);

    // Close the key
    RegCloseKey(hKey);

    // Return result
    if (result == ERROR_SUCCESS)
    {
        bSuccess = true;
        return FString(Data);
    }
    else
    {
        return TEXT("ERROR: Cannot read registry value.");
    }

#else
    bSuccess = false;
    return TEXT("ERROR: Unsupported platform.");
#endif
}
