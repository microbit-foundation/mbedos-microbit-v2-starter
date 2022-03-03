# Target for the nRF52833 MCU

## Linker files

The linker files `NRF52833.ld` are based on the NRF52840 version on 
`mbed-os/targets/TARGET_NORDIC/TARGET_NRF5x/TARGET_NRF52/TARGET_MCU_NRF52840/device/TOOLCHAIN_GCC_ARM/NRF52840.ld`,
from commit `1bf6b20df9d3cd5f29f001ffc6f0d0fcbbb96118`:
https://github.com/ARMmbed/mbed-os/blob/1bf6b20df9d3cd5f29f001ffc6f0d0fcbbb96118/targets/TARGET_NORDIC/TARGET_NRF5x/TARGET_NRF52/TARGET_MCU_NRF52840/device/TOOLCHAIN_GCC_ARM/NRF52840.ld

The changes made to the memory regions in the linker file can be seen in this
GitHub PR comment:
https://github.com/microbit-foundation/mbedos-microbit-v2-starter/pull/12#issuecomment-575753666

### Failed attempts to overwrite nrf52840 target memory regions

Things we tried, and didn't work, to reduce the flash and RAM without having a
custom linker file:

- Tried adding `"NRF52_MICROBIT_V1_43": { "overrides": { "target.restrict_size": "0x40000" } }`
  in `custom_targets.json`, didn't seem to produce a different hex file.
- However adding `"NRF52_MICROBIT_V1_43": { "target.restrict_size": "0x40000" }`
  to the `mbed_app.json` file did produce a different hex file, so we assume
  it works?
- Tried adding ` "NRF52_MICROBIT_V1_43": { "macros_add": ["MBED_RAM_SIZE=0x20000"]}`
  in `custom_targets.json` but didn't work (nRF52833 didn't do anything).
- Tried adding `"NRF52_MICROBIT_V1_43": { "target.macros_add": ["MBED_RAM_SIZE=0x20000""] }`
  in `mbed_app.json`, but didn't work either (nRF52833 didn't do anything).


## custom_targets.json

Due to some NRF52 SDK 14.2 and/or Mbed OS issues we had to disable
CRYPTOCELL310 and MBEDTLS_CONFIG_HW_SUPPORT

More info can be found in these links:
- https://github.com/ARMmbed/mbed-os/issues/7069
- https://github.com/ARMmbed/mbed-os/issues/9880
- https://github.com/ARMmbed/mbed-os/issues/11428
