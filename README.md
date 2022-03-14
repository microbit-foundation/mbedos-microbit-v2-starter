# Example micro:bit V2 project for Mbed OS

## Table of contents

- [Features](#features)
- [Requirements](#requirements)
- [Building This Project](#building-this-project)
- [Visual Studio Code](#visual-studio-code)
- [Using NFC](#using-nfc)
- [License](#license)
- [Code of Conduct](#code-of-conduct)


## Features

This is a basic Mbed OS project for [micro:bit V2](https://microbit.org/new-microbit/).


## Requirements

- [Git](https://git-scm.com/downloads)
- [Mercurial](https://www.mercurial-scm.org/downloads)
- [Arm GCC](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
    - v7.3.1 is the oldest and v10.2.1 the last tested versions
- Python 3
    - Tested with Python 3.7.12
- [Mbed CLI](https://github.com/ARMmbed/mbed-cli)
    - v1.10.2, and v1.10.5 are the last tested versions
    - Can be installed using one of the methods from the official documentation:
      https://os.mbed.com/docs/mbed-os/v6.15/build-tools/install-and-set-up.html
    - The installers are outdated and not recommended
    - If installed via pip a virtual environment is recommended


## Building This Project

### Available Targets

This project contains multiple Mbed OS "targets" for different versions of the
micro:bit V2 board and for the Nordic nRF52833 DK development board.

- `nrf52_microbit_v2`: Target for all production micro:bit V2 board versions.
- `nrf52833_dk`: For the Nordic nRF52833 DK board (useful for testing).

Other targets are available for micro:bit V2 prototype boards, and their
names can be found in the [mbed_app.json](mbed_app.json) file.
These are essentially the same as the `nrf52_microbit_v2` target, but for code
to support multiple boards it is useful to have different target names to be
able to do conditional compilation of pins, I2C addresses, etc, as shown in the
[sensors.cpp example](examples/sensors.cpp) code.

Even older prototype targets can be found in the `mbedos-softdevice` branch.

The version of the micro:bit V2 board can be seen on the silkscreen at the
back, near the right side of the edge connector.

#### Interface MCU

The micro:bit V2.2 contains an nRF52 microcontroller as the
[Interface MCU](https://tech.microbit.org/software/daplink-interface/) and Mbed
OS targets has been created to be able to create Mbed OS project for these
microcontrollers as well.

- `nrf52_microbit_v2_if_820`: Target for micro:bit V2.2 with a nRF52820
  Interface MCU.
- `nrf52_microbit_v2_if_833`: For a micro:bit V2.2 with a nRF52833 Interface
  MCU. This target is configured to be identical to the nrf52820 builds
  (including reduced RAM & Flash), with the only difference being some pin
  assignments.

### Initialise the Project

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

If it fails to install some of the Python dependencies on the last command
(`mbed deploy`) you can try to install them manually.

Run this command in the Python environment that has `mbed-cli` installed:

```
pip install -r mbed-os/requirements.txt
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

If `mbed` cannot find the tools directory in mbed-os, then you may have to
delete the mbed cache by removing `~/.mbed/`.

### Mbed OS Version

This repo is currently configured Mbed OS to version
[6.13.0](https://github.com/ARMmbed/mbed-os/releases/tag/mbed-os-6.13.0).

The branch `mbedos-softdevice` (commit
`9e185e9388cdd634ac4cc38f92a0bbf73af9c5b3`) is configured to
[v5.12.4](https://github.com/ARMmbed/mbed-os/releases/tag/mbed-os-5.12.4), as
this is the last Mbed OS version to support the Nordic Soft Device BLE stack
before it was switched to the Cordio BLE stack.

### Mbed OS RTOS

This section needs to be updated to work with the Mbed OS v6 bare metal
profile.

mbed_app.json:
```
{
    "requires": [
        "bare-metal",
        "drivers-usb",
        "events"
    ],
    "target_overrides": {
        "*": {
            "target.c_lib": "small"
        }
    }
}
```


## Using NFC

The Mbed board target created for the micro:bit configures the NFC pins as GPIO
as they are exposed via the Edge Connector to be used as normal GPIOs.

To change this and use them for NFC you can perform the following changes:
- Mbed: Update the `mbed_app.json` file to include a remove macro entry in the micro:bit target.
    ```
    "NRF52_MICROBIT_V2": {
        "target.macros_remove": ["CONFIG_NFCT_PINS_AS_GPIOS"]
    }
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
