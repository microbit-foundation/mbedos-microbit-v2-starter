# Project Title

This branch removes the following to be a smaller template for simple programs:
- Makefile
- VSCode config
- FXOS and LSM libraries
- Example files
- Configures MbedOS without softdevice
    - Can be reverted in mbed_app.json
- Configures MbedOS without RTOS
    - Can be reverted by deleting .mbedignore

Replace this content with your own project description.



## MbedOS Project Set-up

## Requirements

- git
- [Arm GCC](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
- Python (2 or 3, at the moment Python 2 might be preferred)
- pip (version >=10.0)
- Mercurial
- [Mbed CLI](https://github.com/ARMmbed/mbed-cli)

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
- `nrf52_microbit_v1_44`: For the micro:bit v1.44.4 (nRF52833)

The version of the board can be seen on the silkscreen at the back, near the
right side of the edge connector.

### Initialise

Note that for the `mbed target ...` line you should select the right target
for your board.

```
mbed config root .
mbed target nrf52_microbit_v1_44
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
mbed compile -m nrf52_microbit_v1_44 -t GCC_ARM
```

Build output can be found in: `./BUILD/NRF52_MICROBIT_V1_44/GCC_ARM/mbedos-nrf52-starter.hex`

If `mbed` cannot find the tools directory in mbed-os, then you may have to delete the mbed cache by removing `~/.mbed/`.
