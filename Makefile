INSTALL_DEST = \\.\e:

all: clean boot0.bin boot1.bin ckernel.bin ckernel.img

clean:
	rm dist/* -R

install:
	dd if='dist/boot0.bin' of='$(INSTALL_DEST)' count='1' conv='notrunc'
	dd if='dist/boot1.bin' of='$(INSTALL_DEST)' seek='1' 'conv=notrunc'

boot1.bin: src/boot1/boot1.asm
	nasm -f bin -o dist/$@ $<

boot0.bin: src/boot0/boot0.asm
	nasm -f bin -o dist/$@ $<

ckernel.bin: dist/boot0.bin dist/boot1.bin
	cat dist/boot0.bin dist/boot1.bin > dist/$@

ckernel.img: dist/ckernel.bin
	cp $< dist/$@