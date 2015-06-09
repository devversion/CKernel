# CLEAN
rm dist/* -Rf

# ASSEMBLY
nasm -f elf -o dist/boot1.o src/boot/boot1.asm
nasm -f bin -o dist/boot0.bin src/boot/boot0.asm

# GCC
i586-elf-gcc -nostdlib -nostdinc -ffreestanding -o dist/kernel.o -c src/kernel/kernel.c
i586-elf-gcc -nostdlib -nostdinc -ffreestanding -o dist/ports.o -c src/kernel/ports.c
i586-elf-gcc -nostdlib -nostdinc -ffreestanding -o dist/util.o -c src/kernel/util.c
i586-elf-gcc -nostdlib -nostdinc -ffreestanding -o dist/idt.o -c src/kernel/idt.c

# LINK
i586-elf-ld -Ttext 0x1000 -o dist/kernel.bin dist/boot1.o dist/kernel.o dist/idt.o dist/util.o dist/ports.o --oformat binary

# MERGE
cat dist/boot0.bin dist/kernel.bin > dist/kernel.img

# FILL FLOPPY
dd if='/dev/zero' of='dist/floppy.img' bs='512' count='2880'
dd if='dist/kernel.img' of='dist/floppy.img'

rm dist/kernel.img