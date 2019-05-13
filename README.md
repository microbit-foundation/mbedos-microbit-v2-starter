# Example nRF52 project for Mbed OS

## Requirements

- git
- Arm GCC
- Python (2 or 3)
- [Mbed CLI](https://github.com/ARMmbed/mbed-cli)

## Initialise

```
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

## Building

```
mbed compile -m nrf52_dk -t GCC_ARM
```
