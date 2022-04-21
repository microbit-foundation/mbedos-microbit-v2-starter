-----

⚠️ This branch has been left at an old commit with the last version of MbedOS that supported SoftDevice.

-----

# Example micro:bit V2 project for Mbed OS

## Table of contents

- [Features](#features)
- [Requirements](#requirements)
- [Using Mbed](#using-mbed)
- [Using Make](#using-make)
- [Visual Studio Code](#visual-studio-code)
- [Using NFC](#using-nfc)
- [License](#license)
- [Code of Conduct](#code-of-conduct)


## Features

This is a basic Mbed OS project for [micro:bit V2](https://microbit.org/new-microbit/).


## Requirements

- git
- [Arm GCC](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)

**Mbed only requirements:**
- Python 3
- pip (version >= 10.0)
- Mercurial
- [Mbed CLI](https://github.com/ARMmbed/mbed-cli)
    - Last tested version is 1.10.2

**Make only requirements:**
- srec_cat
- Make


## Using Mbed

### Install dependencies

Install mbed-cli using one of the methods from the official documentation:
https://os.mbed.com/docs/mbed-os/v5.12/tools/developing-mbed-cli.html

The manual installation (in a Python 2 virtual environment) is the prefer method.

### Multiple targets

As there are multiple revisions of the nRF52 board we are using multiple mbed
targets.

- `nrf52_microbit_v1_41`: For the micro:bit v1.41RC2, v1.41RC4, and v1.41RC5
  (nRF52832)
- `nrf52833_dk`: For the Nordic nRF52833 DK board (useful for testing)
- `nrf52_microbit_v1_43`: For the micro:bit v1.43.4 (nRF52833)
- `nrf52_microbit_v1_44` /`nrf52_microbit_v1_45` / `nrf52_microbit_v1_46` /
  `nrf52_microbit_v1_47`: These board versions do not really need a new target
  and are the same as the `nrf52_microbit_v1_43`
- `nrf52_microbit_v2`: This is essentially the same as `nrf52_microbit_v1_43`,
  but since the board is currently only manufactured in the `S` variant, only
  contains the LSM motion sensor (no FXOS), so it's useful to use this target
  name to be able to do conditional compilation.
- `nrf52_microbit_v2_nosd`: V2 target without including SoftDevice (Nordic
  Bluetooth stack).

The version of the board can be seen on the silkscreen at the back, near the
right side of the edge connector.

### Mbed OS Version

We are currently locked to
[v5.12.4](https://github.com/ARMmbed/mbed-os/releases/tag/mbed-os-5.12.4) as
this is the last version to support Soft Device, which has been dropped in
[v5.13+](https://github.com/ARMmbed/mbed-os/releases/tag/mbed-os-5.13.0):

> Default to Cordio BLE stack for NRF52* targets
> [10709](https://github.com/ARMmbed/mbed-os/pull/10709)
> 
> Starting with mbed-os 5.13 and the introduction of Nordic SDK V15, Nordic
> SoftDevice Bluetooth stack is not supported. Bluetooth remains supported with
> the help of Arm's Cordio stack.

~~The [latest-mbedos](https://github.com/microbit-foundation/mbedos-microbit-v2-starter/tree/latest-mbedos)
branch has been updated to use a newer version of MbedOS.~~

The [master](https://github.com/microbit-foundation/mbedos-microbit-v2-starter/tree/master)
branch has been updated to use a newer version of MbedOS.

### Mbed OS RTOS

To compile the project without the Mbed OS RTOS edit the `.mbedignore` and
uncomment all the entries.

### Initialise

Note that for the `mbed target ...` line you should select the right target
for your board.

```
git clone https://github.com/microbit-foundation/mbedos-microbit-v2-starter.git
cd mbedos-microbit-v2-starter
mbed config root .
mbed target nrf52_microbit_v2
mbed toolchain GCC_ARM
mbed deploy
```

If it fails to install some of the Python dependencies on the last command (
`mbed deploy`) you can try again manually:

```
pip install -r mbed-os/requirements.txt
```

Ideally you should be using virtual environments, alternatively you can use the
`--user` flag:

```
pip install --user -r mbed-os/requirements.txt
```

**Warning:** Do not use `mbed new .` as it can update MbedOS to the latest
version, and this is often unwanted.

### Build

```
mbed compile
```

Or if you want to manually add the flags previously configured in the project
on the "Initialise" section:

```
mbed compile -m nrf52_microbit_v2 -t GCC_ARM
```

Build output can be found in: `./BUILD/NRF52_MICROBIT_V2/GCC_ARM/mbedos-microbit-v2-starter.hex`

If `mbed` cannot find the tools directory in mbed-os, then you may have to delete the mbed cache by removing `~/.mbed/`.


## Using Make (back up option only)

The use of the Makefile is discouraged, and it is here only as a back up
mechanism to compile the Mbed project.
As the MakeFile is created based on the mbed project and some manual patches
have to be applied, it is likely this method will fall behind compared the mbed
method.

### Single target

Only the latest target is supported in the Makefile.

At the time of writing this would be v1.43.4 boards. Since the v1.44, v1.45,
v1.46, v1.47 board updates does not affect the target configuration there was
no need to regenerate the Makefile.

### Initialise

```
git clone https://github.com/microbit-foundation/mbedos-microbit-v2-starter.git
cd mbedos-microbit-v2-starter
git clone https://github.com/ARMmbed/mbed-os.git
```

Then open the `mbed-os.lib` file with a text editor, it should have something
like this:

```
https://github.com/ARMmbed/mbed-os/#73f096399b4cda1f780b140c87afad9446047432
```

The sequence after the `#` is the git commit needed of mbed-os, so:

```
cd mbed-os
git reset --hard <commit_hash_here>
```

### Build

From the `mbedos-microbit-v2-starter` folder run:

```
make
```

Build output can be found in: `./BUILD/mbedos-microbit-v2-starter-combined.hex`

### Regenerate Makefile

The Makefile can be regenerated using mbed-cli, however keep in mind that there
has been changes applied (the file header contains more information), and
some of those changes (and the header info) might need to be preserved in the
new regenerated version.

```
mbed-cli export -i GCC_ARM -m nrf52_microbit_v2 --profile develop
```


## Visual Studio Code

At the moment we have the default config files from the Mbed online compiler
project exporter. These are using `make` but could be updated to use `mbed-cli`.


## Using NFC

The Mbed board target created for the micro:bit configures the NFC pins as GPIO
as they are exposed via the Edge Connector to be used as normal GPIOs.

To change this and use them for NFC you can perform the following changes:
- Mbed: Update the `mbed_app.json` file to include a remove macro entry in the micro:bit target.
    ```
    "NRF52_MICROBIT_v1_44": {
        "target.macros_remove": ["CONFIG_NFCT_PINS_AS_GPIOS"]
    }
    ```
- Makefile: Remove the following lines from the makefile.
    ```
    C_FLAGS += -DCONFIG_NFCT_PINS_AS_GPIOS
    ...
    CXX_FLAGS += -DCONFIG_NFCT_PINS_AS_GPIOS
    ...
    ASM_FLAGS += -DCONFIG_NFCT_PINS_AS_GPIOS
    ```


## License

All files specific to this project are Apache License Version 2.0.
Please see the [LICENSE](LICENSE) file.

Some files originated from the
[Mbed OS project](https://github.com/ARMmbed/mbed-os), their copyright and
license has been preserved in each file header.

## Code of Conduct

Trust, partnership, simplicity and passion are our core values we live and
breathe in our daily work life and within our projects. Our open-source projects
are no exception. We have an active community which spans the globe and we
welcome and encourage participation and contributions to our projects by
everyone. We work to foster a positive, open, inclusive and supportive
environment and trust that our community respects the micro:bit code of conduct.

Please see our [code of conduct](https://microbit.org/safeguarding/) which
outlines our expectations for all those that participate in our community and
details on how to report any concerns and what would happen should breaches
occur.
