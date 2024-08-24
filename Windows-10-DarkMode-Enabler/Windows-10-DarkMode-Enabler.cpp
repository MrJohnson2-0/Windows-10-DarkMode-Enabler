#include <iostream>
#include <Windows.h>

bool IsDarkModeEnabled() {
    HKEY hKey;
    DWORD value = 0;
    DWORD valueSize = sizeof(value);

    // Open the registry key for the current user.
    if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS) {
        // Read the current AppsUseLightTheme value.
        if (RegQueryValueEx(hKey, L"AppsUseLightTheme", nullptr, nullptr, reinterpret_cast<LPBYTE>(&value), &valueSize) == ERROR_SUCCESS) {
            RegCloseKey(hKey);
            // Return false if AppsUseLightTheme is 0 (dark mode), true otherwise.
            return value == 0;
        }
        RegCloseKey(hKey);
    }
    std::cerr << "Failed to read registry value." << std::endl;
    return false; // Default to light mode if there is an error.
}

int main()
{
    std::cout << "Hit F5 to Toggle DarkMode\n";

    int times = 0;

    while (true)
    {
        if (GetAsyncKeyState(VK_F5))
        {

            HKEY hKey;
            LONG result;

            result = RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 0, KEY_SET_VALUE, &hKey);

            DWORD DarkMode = 0;

            if (IsDarkModeEnabled())
            {
                DarkMode = 1;
            }
            else
            {
                DarkMode = 0;
            }

            result = RegSetValueEx(hKey, L"AppsUseLightTheme", 0, REG_DWORD, (const BYTE*)DarkMode, sizeof(DarkMode));


            result = RegSetValueEx(hKey, L"SystemUsesLightTheme", 0, REG_DWORD, reinterpret_cast<const BYTE*>(&DarkMode), sizeof(DarkMode));

            RegCloseKey(hKey);
        }
    }

    return 0;
}