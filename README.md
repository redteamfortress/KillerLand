<p align="center">
  <img src="https://raw.githubusercontent.com/redteamfortress/KillerLand/main/killerland.png" alt="KillerLand" width="1400"/>
</p>


This repo is the result of hunting and reversing vulnerable signed kernel drivers for over a year. Every killer here abuses a legitimate driver to terminate any process from kernel mode, PPL-protected or not. Works on EDR/AV protected processes.

Each POC does a simple process kill by PID, you just customize it to whatever EDR process you want dead and it handles the rest from kernel. New ones get dropped as they get reversed.

All research by Jehad Abudagga ([@j3h4ck](https://x.com/j3h4ck)).

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

## Driver Hashes

| # | Driver | SHA256 |
|---|--------|--------|
| 1 | BootRepair.sys | `5ab36c116767eaae53a466fbc2dae7cfd608ed77721f65e83312037fbd57c946` |
| 2 | PoisonX.sys | `TODO` |
| 3 | ardrv.sys | `07c5209bf83065fe760f4fee4ed2308b0c523671f68ca73a3854c2c8c28c0541` |

## Disclaimer

Everything in this repository is published for educational and authorized security research purposes only. These tools and drivers exist to help defenders understand how BYOVD attacks work in practice so they can build better detections and block rules. Do not use any of this against systems you do not own or do not have explicit written authorization to test. The author takes no responsibility for misuse. If you use this to break something you shouldn't be touching, that's on you.

## Author

Jehad Abudagga / [Medium](https://medium.com/@jehadbudagga) / [LinkedIn](https://www.linkedin.com/in/jehadabudagga/) / [X](https://x.com/j3h4ck) / [Telegram](http://t.me/j3h4ck)
