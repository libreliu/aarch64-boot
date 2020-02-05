# aarch64-boot
A simple Multiboot-compatible chainloader for AArch64 platform

## Status

**Currently only RPi 3b+ supported**. To port to other platforms:
- Figure out the load entry address for the bootloader it self, then edit the `. = 0x80000;` line in `linker.ld`
- Decide where to put actual images to be loaded, along with the dtb file
  - configurable via `config.h`
- Modify `printf_impl.c` to provide your ways of character output (By writing new `_putchar` function)

## Why not U-Boot?

U-Boot is powerful, but..

- Porting U-Boot can be time-consuming (if specified arch is not ready)
- U-boot have higher complexity when custumization in source code level needed

This project provides a simple but efficient way of booting under AArch64, suitable for customized OS development.

## How it works?

Briefly: Link `kernel.elf` and `device_tree.dtb` with the executable, then converted into flat binary.

## Usage

This project is currently tested **only** under RPi 3b+.

### RPi 3b+ (Raspberry Pi 3b+)

In RPi 3b+, `kernel8.img` is the filename used as boot image in aarch64. The image will be loaded into 0x80000, which differs from `kernel7.img` in AArch32 (0x8000).

## LICENSE

This project is licensed under MIT License.

```
    Copyright (C) 2020 libreliu (libreliu@github)

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use, copy,
    modify, merge, publish, distribute, sublicense, and/or sell copies
    of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
```

## External Sources Included
- UART stuff: https://github.com/bztsrc/raspi3-tutorial
  - MIT Licensed, author [bztsrc](https://github.com/bztsrc/raspi3-tutorial)
- embedded printf: https://github.com/mpaland/printf/
  - MIT LIcensed, author [Marco Paland](https://github.com/mpaland/)