# Example nRF52 project for Mbed OS

## Requirements

- git
- make
- Arm GCC
- Python (2 or 3, at the moment Python 2 might be preferred)
- [Mbed CLI](https://github.com/ARMmbed/mbed-cli) or Make


## Using Mbed

### Install dependencies

Install mbed-cli using one of the methods from the official website:
https://os.mbed.com/docs/mbed-os/v5.12/tools/developing-mbed-cli.html

The manual installation (in a Python virtual environment) is the prefer method.

### Initialise

```
git clone https://github.com/microbit-foundation/mbedos-nrf52-starter.git
cd mbedos-nrf52-starter
mbed deploy
```

If it fails to install some of the Python dependencies you can try again
manually:

```
pip install -r mbed-os/requirements.txt
```

Ideally you should be using virtual environments, alternatively you can use the
`--user` flag:

```
pip install --user -r mbed-os/requirements.txt
```

**Warning:** Do not use `mbed new .`, this will update MbedOS to the latest
version, and this is often unwanted.

### Build

```
mbed compile -m nrf52_dk -t GCC_ARM
```

Build output can be found in: `TBD`


## Using Makefile

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

Build output can be found in: `TBD`


## Visual Studio Code

At the moment we have the default config files from the Mbed online compiler
project exporter. These are using `make` but could be updated to use `mbed-cli`.
