# Example nRF52 project for Mbed OS

## Table of contents

- [Features](#features)
- [Requirements](#requirements)
- [Using Mbed](#using-mbed)
- [Using Make](#using-make)
- [Visual Studio Code](#visual-studio-code)
- [Contributing](#contributing)
- [License](#license)


## Features

TBD.


## Requirements

- git
- [Arm GCC](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)

**Mbed only requirements:**
- Python (2 or 3, at the moment Python 2 might be preferred)
- pip (version >=10.0)
- Mercurial
- [Mbed CLI](https://github.com/ARMmbed/mbed-cli)

**Make only requirements:**
- srec_cat
- Make


## Using Mbed

### Install dependencies

Install mbed-cli using one of the methods from the official documentation:
https://os.mbed.com/docs/mbed-os/v5.12/tools/developing-mbed-cli.html

The manual installation (in a Python 2 virtual environment) is the prefer method.

### Initialise

```
git clone https://github.com/microbit-foundation/mbedos-nrf52-starter.git
cd mbedos-nrf52-starter
mbed config root .
mbed target nrf52_dk
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
mbed compile -m nrf52_dk -t GCC_ARM
```

Build output can be found in: `./BUILD/NRF52_DK/GCC_ARM/mbedos-project.hex`

If `mbed` cannot find the tools directory in mbed-os, then you may have to delete the mbed cache by removing `~/.mbed/`.

## Using Make

### Initialise

```
git clone https://github.com/microbit-foundation/mbedos-nrf52-starter.git
cd mbedos-nrf52-starter
git clone https://github.com/ARMmbed/mbed-os.git
```

Then open the `mbed-os.lib` file with a text editor, it should have something
like this:

```
https://github.com/ARMmbed/mbed-os/#0f959dbe4749c20416236e4fe1dac5692cbe18ab
```

The sequence after the `#` is the git commit needed of mbed-os, so:

```
cd mbed-os
git reset --hard <commit_hash_here>
```

### Build

From the `mbedos-nrf52-starter` folder run:

```
make
```

Build output can be found in: `BUILD/nrf52-mbed-os-blinky-combined.hex`


## Visual Studio Code

At the moment we have the default config files from the Mbed online compiler
project exporter. These are using `make` but could be updated to use `mbed-cli`.


## Contributing

TBD.


## License

TBD.
