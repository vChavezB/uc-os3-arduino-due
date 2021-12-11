# uC-OS3 Arduino Due

This is a an adaption of the uc-OS3 RTOS to make it compatible with the Arduino IDE and its SDK. The current version of the source files are

- uc-OS3: [V3.08.01](https://github.com/weston-embedded/uC-OS3/tree/7af6c6e8aff1c75caf008fcc266b759528199eb2)
- uc-LIB: [v1.39.01](https://github.com/weston-embedded/uC-LIB/tree/71b5f65da27859028a89c4ceac1df53c880916dc)
- uc-CPU: [V1.32.01](https://github.com/weston-embedded/uC-CPU/tree/ae5796e2049b043f69ef4f29fc330f29217b6344)

The specific Port files used for the library are Cortex-M3 (ARMv7-M)

## What has been modified?

Some include directories have been made relative since the Arduino platform doesn't have an option to include directories via compiler flags easily without hacking the boards.txt and platforms.txt. In addition `pendSVHook` and `sysTickHook` have been implemented in `/src/uc-os3-Arduino.c`. These two functions are called in the cortex handlers in the Arduino Due SDK `/core/arduino/cortex_handlers.c`.


## Installation

To use the library this repository can be cloned to your Arduino libraries directory.

```bash
git clone https://git.fh-aachen.de/embedded-arduino/uc-os3-arduino-due.git
```

Uc-OS3 uses some header files for configuration of the OS and a source file with hook implementations for the app. A directory named `os_cfg` shall be created where you have your sketch. This dir. should contain the following files:

- os_app_hooks.c
- os_app_hooks.h
- os_cfg.h
- os_cfg_app.h

These files can be obtaineed from the `cfg_template` folder. Since the Arduino platform does not have an option to include these header files directly, the boards.txt of the Arduino Due board have to be modified by adding a new entry. This file is typically located in `/AppData/Local/Arduino15/packages/arduino/hardware/sam/YOUR_BOARD_VERSION/boards.txt`. The entry which has to be added at the end looks as follows:

```
arduino_due_x_dbg_os.name=Arduino Due uc-OS3
arduino_due_x_dbg_os.vid.0=0x2341
arduino_due_x_dbg_os.pid.0=0x003d
arduino_due_x_dbg_os.vid.1=0x2A03
arduino_due_x_dbg_os.pid.1=0x003d
arduino_due_x_dbg_os.upload.tool=bossac
arduino_due_x_dbg_os.upload.protocol=sam-ba
arduino_due_x_dbg_os.upload.maximum_size=524288
arduino_due_x_dbg_os.upload.use_1200bps_touch=true
arduino_due_x_dbg_os.upload.wait_for_upload_port=false
arduino_due_x_dbg_os.upload.native_usb=false
arduino_due_x_dbg_os.build.mcu=cortex-m3
arduino_due_x_dbg_os.build.f_cpu=84000000L
arduino_due_x_dbg_os.build.usb_manufacturer="Arduino LLC"
arduino_due_x_dbg_os.build.usb_product="Arduino Due"
arduino_due_x_dbg_os.build.board=SAM_DUE
arduino_due_x_dbg_os.build.core=arduino
arduino_due_x_dbg_os.build.extra_flags=-D__SAM3X8E__ -mthumb {build.usb_flags} -I "{build.path}/sketch/os_cfg"
arduino_due_x_dbg_os.build.ldscript=linker_scripts/gcc/flash.ld
arduino_due_x_dbg_os.build.variant=arduino_due_x
arduino_due_x_dbg_os.build.variant_system_lib=libsam_sam3x8e_gcc_rel.a
arduino_due_x_dbg_os.build.vid=0x2341
arduino_due_x_dbg_os.build.pid=0x003e
```

Where the most important part is the addition of 

```
-I "{build.path}/sketch/os_cfg"
```

to arduino_due_x_dbg_os.build.extra_flags.

Remember to change the board to `Arduino Due uc-OS3` to compile your project with uc-OS3
