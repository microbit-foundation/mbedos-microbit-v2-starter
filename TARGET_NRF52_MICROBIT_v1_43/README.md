# Target for the micro:bit v1.43

The linker file `NRF52833.ld` is based on the NRF52840 version on 
`mbed-os/targets/TARGET_NORDIC/TARGET_NRF5x/TARGET_NRF52/TARGET_MCU_NRF52840/device/TOOLCHAIN_GCC_ARM/NRF52840.ld`,
from commit `1bf6b20df9d3cd5f29f001ffc6f0d0fcbbb96118`:
https://github.com/ARMmbed/mbed-os/blob/1bf6b20df9d3cd5f29f001ffc6f0d0fcbbb96118/targets/TARGET_NORDIC/TARGET_NRF5x/TARGET_NRF52/TARGET_MCU_NRF52840/device/TOOLCHAIN_GCC_ARM/NRF52840.ld

The `device.h` has just been copied from the TARGET_NRF52_MICROBIT_v1_41 target.

The `PinNames.h` file has been copied  from the TARGET_NRF52_MICROBIT_v1_41
target and edited to follow similar pin mappings as the NRF52840 DK.

Things we tried to reduce the flash and RAM without having a custom linker
file:
- Tried adding `"NRF52_MICROBIT_v1_43": { "overrides": { "target.restrict_size": "0x40000" } }`
  in `custom_targets.json`, didn't seem to produce a different hex file.
- However adding `"NRF52_MICROBIT_v1_43": { "target.restrict_size": "0x40000" }`
  to the `mbed_app.json` file did produce a different hex file, so we assume
  it works?
- Tried adding ` "NRF52_MICROBIT_v1_43": { "macros_add": ["MBED_RAM_SIZE=0x20000"]}`
  in `custom_targets.json` but didn't work (nRF52833 didn't do anything).
- Tried adding `"NRF52_MICROBIT_v1_43": { "target.macros_add": ["MBED_RAM_SIZE=0x20000""] }`
  in `mbed_app.json`, but didn't work either (nRF52833 didn't do anything).
