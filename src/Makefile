SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

# Input and output
ELF_BIN = kernel.elf.bin
ELO = kernel.elo
DTB = devicetree.dtb
DTO = devicetree.dto
CFLAGS = -Wall -O2 -ffreestanding -nostdlib -nostartfiles -g

all: clean kernel8.img

start.o: start.S
	aarch64-linux-gnu-gcc $(CFLAGS) -c start.S -o start.o

%.o: %.c
	aarch64-linux-gnu-gcc $(CFLAGS) -c $< -o $@

# !Make sure there is no .elf output
kernel8.img: start.o $(OBJS) $(DTO) $(ELO)
	aarch64-linux-gnu-ld -nostdlib -nostartfiles start.o $(OBJS) $(DTO) $(ELO) -T linker.ld -o kernel8.elf
	aarch64-linux-gnu-objcopy -O binary kernel8.elf kernel8.img
#	mv kernel8.elf kernel8.img

# DTB Objects
$(DTO): $(DTB)
	aarch64-linux-gnu-objcopy -I binary -O elf64-littleaarch64 -B aarch64 $< $@

# Target Multiboot ELF binary to be added
$(ELO): $(ELF_BIN)
	aarch64-linux-gnu-objcopy -I binary -O elf64-littleaarch64 -B aarch64 $< $@

clean:
	rm kernel8.elf *.o *.dto *.elo >/dev/null 2>/dev/null || true

run:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial stdio -drive file=sd.img,format=raw,if=sd

debug:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -S -gdb tcp::2345 -drive file=sd.img,format=raw,if=sd