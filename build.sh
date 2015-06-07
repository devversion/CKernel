
# CLEAN
rm dist/* -Rf

# NASM
nasm -f bin -o dist/boot0.bin src/boot0/boot0.asm
nasm -f elf -o dist/boot1.o src/boot1/boot1.asm

# C Kernel
i586-elf-gcc -m32 -std=c99 -ffreestanding -O2 -Wall -Wextra -c src/kernel/kernel.c -o dist/kernel.o

# LINK
i586-elf-ld --oformat binary -Ttext 0x1000 -m elf_i386 -o dist/kernel.bin dist/boot1.o dist/kernel.o

# FILL ZEROS
SIZE=$(wc -c <"dist/kernel.bin")
dd if=/dev/zero bs=1 count=$((8192 - $SIZE)) >> dist/kernel.bin

# MERGE BINARIES
cat dist/boot0.bin dist/kernel.bin > dist/ckernel.bin

# COPY FOR IMG
cp dist/ckernel.bin dist/ckernel.img
