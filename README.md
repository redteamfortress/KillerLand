# KillerLand

Reversed BYOVD process killers. Each one abuses a legitimate signed kernel driver to terminate arbitrary processes from kernel mode, including PPL-protected EDR/AV.

Every driver here was reversed independently. Writeups cover the full IDA analysis and weaponization.

## Killers

| # | Name | Driver | Vendor | IOCTL | Signer | VT | CVE | Writeup | POC |
|---|------|--------|--------|-------|--------|-----|-----|---------|-----|
| 1 | [PhantomKiller](#1--phantomkiller) | BootRepair.sys | Lenovo | `0x222014` | Lenovo | 0/71 | - | [link](https://example.com) | [repo](https://github.com/redteamfortress/PhantomKiller) |
| 2 | [PoisonKiller](#2--poisonkiller) | PoisonX.sys | Microsoft | `0x22E010` | MSWHCP | 0/71 | - | [link](https://example.com) | [repo](https://github.com/redteamfortress/PoisonKiller) |
| 3 | [PPLShade](#3--pplshade) | ardrv.sys | OPSWAT | `0x2420031` | - | - | CVE-2026-36425 | [link](https://example.com) | [repo](https://github.com/redteamfortress/CVE-2026-36425) |

<!-- copy this row for new entries:
| N | [Name](#n--name) | driver.sys | Vendor | `0xIOCTL` | Signer | 0/xx | CVE-XXXX-XXXXX | [link](url) | [repo](url) |
-->

---

## 1 . PhantomKiller

Abuses `BootRepair.sys` from Lenovo PC Manager. The driver creates its device object without a DACL, and the IOCTL handler calls `ZwTerminateProcess` on whatever PID you pass in. No access checks, no caller validation.

| | |
|-------|-------|
| Driver | `BootRepair.sys` |
| SHA256 | `5ab36c116767eaae53a466fbc2dae7cfd608ed77721f65e83312037fbd57c946` |
| Vendor | Lenovo |
| Software | Lenovo PC Manager |
| Signer | Lenovo (Symantec Class 3 SHA256 Code Signing CA) |
| Compiled | 2018-01-03 |
| Arch | x64 |
| Device | `\\.\BootRepair` |
| IOCTL | `0x222014` |
| Input | 4-byte DWORD, target PID |
| Kill chain | `PsLookupProcessByProcessId` > `ObOpenObjectByPointer` > `ZwTerminateProcess` |
| VT | 0/71 at time of discovery |
| Blocklisted | No |

Writeup: [Phantom Killer: Reverse Engineering and Weaponizing a Lenovo Driver to Terminate EDR Processes](https://example.com)

---

## 2 . PoisonKiller

Signed Microsoft driver (`PoisonX.sys`) with an IOCTL interface that kills any process, PPL or not. Works against CrowdStrike Falcon.

| | |
|-------|-------|
| Driver | `PoisonX.sys` |
| SHA256 | `TODO` |
| Vendor | Microsoft |
| Signer | Microsoft Windows Hardware Compatibility Publisher |
| Sign date | 2025-03-25 |
| Arch | x64 |
| Device | `\\.\{F8284233-48F4-4680-ADDD-F8284233}` |
| IOCTL | `0x22E010` |
| Input | Target PID |
| VT | 0/71 |
| Blocklisted | No |

Writeup: [Reverse Engineering a 0day used Against CrowdStrike EDR](https://example.com)

---

## 3 . PPLShade

OPSWAT AppRemover driver (`ardrv.sys`). Published as CVE-2026-36425.

| | |
|-------|-------|
| Driver | `ardrv.sys` |
| SHA256 | `07c5209bf83065fe760f4fee4ed2308b0c523671f68ca73a3854c2c8c28c0541` |
| Vendor | OPSWAT |
| Software | AppRemover |
| IOCTL | `0x2420031` |
| CVE | CVE-2026-36425 |

Writeup: [TODO](https://example.com)

---

## Loading

```
sc create DriverName type= kernel binPath= C:\path\to\driver.sys
sc start DriverName
```

Cleanup:

```
sc stop DriverName
sc delete DriverName
```

## See also

- [LOLDrivers](https://www.loldrivers.io/)
- [KDU (hfiref0x)](https://github.com/hfiref0x/KDU)
- [Microsoft Driver Block Rules](https://learn.microsoft.com/en-us/windows/security/application-security/application-control/app-control-for-business/design/microsoft-recommended-driver-block-rules)

## Disclaimer

For educational and authorized security research only.

## Author

[@j3h4ck](https://github.com/j3h4ck) / [RedTeamFortress](https://github.com/redteamfortress)
