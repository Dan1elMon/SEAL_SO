CC = i686-linux-gnu-gcc
AS = i686-linux-gnu-as
LD = i686-linux-gnu-gcc
GRUB = grub-mkrescue
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude
LDFLAGS = -T linker.ld -nostdlib -ffreestanding

SRC = src
INCLUDE = include
BUILD = build

OBJS = $(BUILD)/boot.o $(BUILD)/kernel.o $(BUILD)/memoria.o $(BUILD)/dispositivo.o $(BUILD)/archivo.o

all: $(BUILD)/Seal_OS.iso

$(BUILD)/boot.o: $(SRC)/boot.s
	$(AS) $(SRC)/boot.s -o $(BUILD)/boot.o

$(BUILD)/kernel.o: $(SRC)/kernel.c
	$(CC) $(CFLAGS) -c $(SRC)/kernel.c -o $(BUILD)/kernel.o

$(BUILD)/memoria.o: $(SRC)/memoria.c
	$(CC) $(CFLAGS) -c $(SRC)/memoria.c -o $(BUILD)/memoria.o

$(BUILD)/dispositivo.o: $(SRC)/dispositivo.c
	$(CC) $(CFLAGS) -c $(SRC)/dispositivo.c -o $(BUILD)/dispositivo.o

$(BUILD)/archivo.o: $(SRC)/archivo.c
	$(CC) $(CFLAGS) -c $(SRC)/archivo.c -o $(BUILD)/archivo.o

$(BUILD)/Seal_OS.bin: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(BUILD)/Seal_OS.bin -lgcc

$(BUILD)/Seal_OS.iso: $(BUILD)/Seal_OS.bin
	mkdir -p isodir/boot/grub
	cp $(BUILD)/Seal_OS.bin isodir/boot/Seal_OS.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	$(GRUB) -o $(BUILD)/Seal_OS.iso isodir

run: $(BUILD)/Seal_OS.iso
	qemu-system-i386 -cdrom $(BUILD)/Seal_OS.iso

clean:
	rm -rf $(BUILD)/*.o $(BUILD)/*.bin $(BUILD)/*.iso isodir

.PHONY: all clean run