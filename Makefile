#Variables for building game
DEVKITPRO := C:/devkitPro
GCCARM := $(DEVKITPRO)/devkitARM/bin/arm-none-eabi-gcc.exe
GBAFIX := $(DEVKITPRO)/tools/bin/gbafix.exe
OBJCOPY := $(DEVKITPRO)/devkitARM/bin/arm-none-eabi-objcopy.exe
MGBA := "C:/Program Files/mGBA/mGBA.exe"

TEMP := build/temp
SRC := src/
INCLUDE := src/include
MAINFILE := $(SRC)main.c
GRAPHICSFILE := $(SRC)graphics.c
GRAPHICSDATAFILE := $(SRC)graphicsdata.c
USERINTERFACEFILE := $(SRC)userinterface.c
ENGINEFILE := $(SRC)engine.c
OUTFILE := build/foolishness.gba

#build and run
run: game
	$(MGBA) $(OUTFILE)
#builds game
game:
	mkdir -p ./build/temp

	$(GCCARM) -mthumb -c $(MAINFILE) -o $(TEMP)/main.o -I $(INCLUDE)
	$(GCCARM) -mthumb -c $(GRAPHICSFILE) -o $(TEMP)/graphics.o -I $(INCLUDE)
	$(GCCARM) -mthumb -c $(GRAPHICSDATAFILE) -o $(TEMP)/graphicsdata.o -I $(INCLUDE)
	$(GCCARM) -mthumb -c $(USERINTERFACEFILE) -o $(TEMP)/userinterface.o -I $(INCLUDE)
	$(GCCARM) -mthumb -c $(ENGINEFILE) -o $(TEMP)/engine.o -I $(INCLUDE)

	$(GCCARM) -specs=gba.specs -mthumb $(TEMP)/main.o $(TEMP)/graphics.o $(TEMP)/graphicsdata.o $(TEMP)/userinterface.o $(TEMP)/engine.o -o $(TEMP)/program.elf 

	$(OBJCOPY) -O binary $(TEMP)/program.elf $(OUTFILE)

	$(GBAFIX) $(OUTFILE)
