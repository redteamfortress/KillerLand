<p align="center">
  <img src="https://raw.githubusercontent.com/redteamfortress/KillerLand/main/killerland.png" alt="KillerLand" width="1400"/>
</p>


This repo is the result of hunting and reversing vulnerable signed kernel drivers for over a year. Every killer here abuses a legitimate driver to terminate any process from kernel mode, PPL-protected or not. Works on EDR/AV protected processes.

Each POC does a simple process kill by PID, you just customize it to whatever EDR process you want dead and it handles the rest from kernel. New ones get dropped as they get reversed.

All research by Jehad Abudagga ([@j3h4ck](https://x.com/j3h4ck)).

## Killers

| # | Name | Vendor | SymLink | IOCTL | Signer | POC | Date |
|---|------|--------|-------|-------|--------|-----|-----|
| 1 | libwasys.sys | OPSWAT | \\\\.\WasysControl | `0x22E00C` | Microsoft | [repo](https://github.com/redteamfortress/KillerLand/tree/main/1.%20Libwasys) | 18/10/2026 |
| 2 | MonProcessControl.sys | HONOR | \\\\.\MonProcessControl | `0x22400C` | Microsoft | [repo](https://github.com/redteamfortress/KillerLand/tree/main/2.%20MonProcessControl) | 18/10/2026 |

## Loading

```
sc create DriverName type= kernel binPath= C:\path\to\driver.sys
sc start DriverName
```

Running:

```
killer_poc.exe <PID>
```
Cleanup:

```
sc stop DriverName
sc delete DriverName
```


## Driver Hashes

| # | Driver | SHA256 |
|---|--------|--------|
| 1 | libwasys.sys | `04fda396f42384d9295fe306336ee4a685a0c341debdc27ddf9169f0336b46a6` |
| 2 | MonProcessControl.sys | `0e1cc4f205ddc6b78578de2da209ba3ba1f16fac482f4042bbd02036fc470f04` |

## Disclaimer

Everything in this repository is published for educational and authorized security research purposes only. These tools and drivers exist to help defenders understand how BYOVD attacks work in practice so they can build better detections and block rules. Do not use any of this against systems you do not own or do not have explicit written authorization to test. The author takes no responsibility for misuse. If you use this to break something you shouldn't be touching, that's on you.

## Author

Jehad Abudagga / [Medium](https://medium.com/@jehadbudagga) / [LinkedIn](https://www.linkedin.com/in/jehadabudagga/) / [X](https://x.com/j3h4ck) / [Telegram](http://t.me/j3h4ck)
