<p align="center">
  <img src="https://raw.githubusercontent.com/redteamfortress/KillerLand/main/killerland.png" alt="KillerLand" width="700"/>
</p>

Over a year of reversing vulnerable signed kernel drivers that kill any process from kernel mode, PPL-protected or not. New killers get added as they get reversed.

All research by Jehad Abudagga ([@j3h4ck](https://github.com/j3h4ck)).

## Killers

| # | Name | Vendor | IOCTL | Signer | POC |
|---|------|--------|-------|--------|-----|
| 1 | PhantomKiller | Lenovo | `0x222014` | Lenovo | [repo](https://github.com/redteamfortress/PhantomKiller) |
| 2 | PoisonKiller | Microsoft | `0x22E010` | MSWHCP | [repo](https://github.com/redteamfortress/PoisonKiller) |
| 3 | PPLShade | OPSWAT | `0x2420031` | - | [repo](https://github.com/redteamfortress/CVE-2026-36425) |

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

Running:

```
killer_poc.exe <PID>
```

## See also

- [LOLDrivers](https://www.loldrivers.io/)
- [KDU (hfiref0x)](https://github.com/hfiref0x/KDU)
- [Microsoft Driver Block Rules](https://learn.microsoft.com/en-us/windows/security/application-security/application-control/app-control-for-business/design/microsoft-recommended-driver-block-rules)

## Disclaimer

Everything in this repository is published for educational and authorized security research purposes only. These tools and drivers exist to help defenders understand how BYOVD attacks work in practice so they can build better detections and block rules. Do not use any of this against systems you do not own or do not have explicit written authorization to test. The author takes no responsibility for misuse. If you use this to break something you shouldn't be touching, that's on you.

## Author

Jehad Abudagga / [@j3h4ck](https://github.com/j3h4ck) / [RedTeamFortress](https://github.com/redteamfortress)
