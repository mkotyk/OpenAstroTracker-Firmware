# OpenAstroTracker-Firmware
Official firmware for the OpenAstroTracker. Other important resources can be found [here](https://wiki.openastrotech.com/en/Links).


## Fork notes:

🚨 You probably don't want this fork unless you're using a **BigTreeTech SKR MINI E3 V3.0**!  No
other platforms are maintained or tested in this fork.

- I've restructured this project to make it work in my environment.  PlatformIO was choking on the
  directory structure and/or the ini file.  _"Human sacrifice, ~~dogs~~ headers and ~~cats~~ sources living together... MASS HYSTERIA!"._
- Started with a fresh `pio project init`, then moved files into the correct places.
- Moved all the cluttering python scripts out of the top level
- Moved all the gorpy configuration headers out of the top level
- Not really interested in upstreaming this work or any critiques, I'm just scratching my own itch.

## Notes about the BigTreeTech SKR MINI E3 V3.0
- This is a neat little 3D Printer controller available on Amazon for a very low price.
- It features an STM32G0B1 Arm Cortex-M processor with 512K flash and 144K ram
- It includes 4 TMC2209 stepper drivers under a nice clean heatsink.  They are UART enabled utilizing hardware serial port 4, all chained together with fixed identifier ids
- It is quite small and fits inside the lower 2020 frame of the OAT
- It has a microsd card slot, and a variety of expansion headers for LCDs, GPS, compass etc

## Change log
See the [Changelog](Changelog.md) for details about what versions made what changes.

## Coding guidelines

See `.clang-format` file. A GitHub action is run on every PR to make sure that the code complies with the formatting guidelines.

### Run clang-format locally
* Install `clang-format` version 12. _Note: not all distributions default to version 12_
  * Windows: Installers available from [LLVM Website](https://llvm.org/builds/)
  * Ubuntu: `sudo apt install clang-format-12`
  * ArchLinux: `sudo pacman -S clang`
* Run the formatter: 
  * VSCode Extension: [https://marketplace.visualstudio.com/items?itemName=xaver.clang-format](https://marketplace.visualstudio.com/items?itemName=xaver.clang-format)
  * Shell: `bash -c 'shopt -s nullglob globstar;GLOBIGNORE=./src/libs/TimerInterrupt/*; for i in ./{.,src/**,unit_tests,boards/**}/*.{c,cpp,h,hpp}; do clang-format -i $i; done'`
## Contribution

This is an open source project and everyone is welcome to contribute. We will be following these rules while reviewing your pull request:
- The pull request consists **only** of the **changes related to its particular feature or bugfix**. If there are multiple unrelated changes which should be merged into this repository, you have to create a separate pull request for each of them. 
- The pull request **builds correctly**. If it doesn't, please fix the issues and push them to the source branch. You can use the matrix_build.py script to build all the important configurations locally (works similar to our CI).
- The pull request can only be merged **after** all comments were resolved BY **OAT DEVELOPERS**. Please don't resolve the comments yourself since this can lead to missed issues.
- If the pull request is not maintained by its author in a reasonably prompt manner after a review, the developers can decide to close it without merging since the accumulated merge conflicts and original code changes could lead to massive efforts. You can then still recreate your pull request after applying all the required changes on your fork branch.

## Development

Even if Arduino IDE is supported, we highly recommend using VSCode with [PlatformIO](https://platformio.org/) for development. It allows automatic dependency management, powerful IDE, debugging, automatic build flags definition and more.

### Debugging

#### ATmega2560-based

> :warning: **Debugging is only supported on mega2560 platforms at the moment!**

For this example we will be using the `ramps` environment, but you can use any derived environment as well

> You may need to set `debug_port` in your `platformio.ini`, platformio says it will auto-detect the port but it doesn't seem to be working at the moment

Start a gdb shell debugging the current firmware:
```shell
pio run -e ramps -t clean  # Clean the environment
piodebuggdb -e ramps  # Initialize a debug session.
# This will build the firmware in debug mode, and then initialize a remote gdb session
# You may have visual debug capabilities in your IDE if it has platformio integration as well
```

When using `avr-stub` as a debug interface, it requires 2 things:
1. Serial link 0 must not be used in the firmware
    - As such, all external interfaces using `Serial` are disabled in a debug build (`Serial1`, `Serial2` etc are ok)
2. Exclusive access to an interrupt vector
    - This requires hot-patching the arduino framework (specifically `WInterrupts.c`) to disable the ISR registration. The implementation of this is in `pre_script_patch_debug.py`, which should happen automagically

> Note that while avr-stub is in RAM mode, the firmware will run very slowly and timing-related functions might not work correctly

Debugging is still a bit flakey, so you may need to try multiple times in order to get a solid debugging session.

More information is available in the [avr-stub documentation](https://github.com/jdolinay/avr_debug/tree/master/doc)

### Meade Command Documentation
The Meade commands page on the Wiki is generated by running:
```shell
python .\scripts\MeadeCommandParser.py
```
from the main directory. The page is generated in the scripts folder and needs to be copy pasted into the Wiki manually. Please add the version manually (for now) by pasting something like this:
```
> This documentation is current as of Firmware **V1.13.9**
{.is-warning}
```
