#Variables for building game
DEVKITPRO := C:/devkitPro
GCCARM := $(DEVKITPRO)/devkitARM/bin/arm-none-eabi-gcc.exe
GBAFIX := $(DEVKITPRO)/tools/bin/gbafix.exe
OBJCOPY := $(DEVKITPRO)/devkitARM/bin/arm-none-eabi-objcopy.exe
MGBA := "C:/Program Files/mGBA/mGBA.exe"
INCLUDE := src/include

TEMP := build/temp
SRCFILE := src/main.cpp
TOOLBOX := src/toolbox.cpp
OUTFILE := build/nonograms.gba

#build and run
run: game
	$(MGBA) $(OUTFILE)
#builds game
game:
	$(GCCARM) -mthumb -c $(SRCFILE) -o $(TEMP)/main.o -I $(INCLUDE)
	
	$(GCCARM) -mthumb -c $(TOOLBOX) -o $(TEMP)/toolbox.o -I $(INCLUDE)

	$(GCCARM) -specs=gba.specs -mthumb $(TEMP)/main.o $(TEMP)/toolbox.o -o $(TEMP)/program.elf 

	$(OBJCOPY) -O binary $(TEMP)/program.elf $(OUTFILE)

	$(GBAFIX) $(OUTFILE)

#cleans temp folder
clean:
	rm -f $(TEMP)/program.o $(TEMP)/toolbox.o $(TEMP)/program.elf
