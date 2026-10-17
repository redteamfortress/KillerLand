# KillerLand

Over a year of reversing vulnerable signed kernel drivers that kill any process from kernel mode, PPL-protected or not. New killers get added as they get reversed.

All research by Jehad Abudagga (@j3h4ck).

## Killers

| # | Name | Vendor | IOCTL | Signer | VT | CVE | Writeup | POC |
|---|------|--------|--------|-------|--------|-----|-----|---------|
| 1 | [PhantomKiller](#1--phantomkiller) | Lenovo | `0x222014` | Lenovo | 0/71 | - | [link](https://example.com) | [repo](https://github.com/redteamfortress/PhantomKiller) |
| 2 | [PoisonKiller](#2--poisonkiller) | Microsoft | `0x22E010` | MSWHCP | 0/71 | - | [link](https://example.com) | [repo](https://github.com/redteamfortress/PoisonKiller) |
| 3 | [PPLShade](#3--pplshade) | OPSWAT | `0x2420031` | - | - | CVE-2026-36425 | [link](https://example.com) | [repo](https://github.com/redteamfortress/CVE-2026-36425) |

<!-- copy this row for new entries:
| N | [Name](#n--name) | driver.sys | Vendor | `0xIOCTL` | Signer | 0/xx | CVE-XXXX-XXXXX | [link](url) | [repo](url) |
-->

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

## Disclaimer

For educational and authorized security research only.

## Author

[@j3h4ck](https://github.com/j3h4ck) / [RedTeamFortress](https://github.com/redteamfortress)
