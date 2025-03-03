
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WindowsRegistryReadLibrary.generated.h"

/**
 * 
 */
UCLASS()
class WINDOWSREGISTRYREADPLUGIN_API UWindowsRegistryReadLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
    /** Reads a registry key value from Windows Registry.
     * @param RegistryPath - The full registry path (e.g., "SOFTWARE\Microsoft\Windows\CurrentVersion").
     * @param ValueName - The name of the value to retrieve (leave empty for default).
     * @param bIs64BitKey - If true, reads from the 64-bit registry.
     * @return The registry value as a string. (returns the error instead of registry value on fail)
     * @param bSuccess - Output boolean indicating if the function was successful.
     */
    UFUNCTION(BlueprintCallable, Category = "Windows Registry")
    static FString ReadRegistryValue(const FString& RegistryPath, const FString& ValueName, bool bIs64BitKey, bool& bSuccess);
};
