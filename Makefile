#Variables for building game
DEVKITPRO := C:/devkitPro
GCCARM := $(DEVKITPRO)/devkitARM/bin/arm-none-eabi-gcc.exe
GBAFIX := $(DEVKITPRO)/tools/bin/gbafix.exe
OBJCOPY := $(DEVKITPRO)/devkitARM/bin/arm-none-eabi-objcopy.exe
MGBA := "C:/Program Files/mGBA/mGBA.exe"

TEMP := build/temp
SRC := src
INCLUDE := src/include
TARGETLIST := main foo
OUTFILE := build/foolishness.gba

#build and run
run: game clean
	$(MGBA) $(OUTFILE)

$(TARGETLIST): 
	mkdir -p ./$(TEMP)
	$(GCCARM) -mthumb -c $(SRC)/$(@).c -o $(TEMP)/$(@).o -I $(INCLUDE)

#builds game
game: $(TARGETLIST)
	$(GCCARM) -specs=gba.specs -mthumb $(addprefix $(TEMP)/,$(addsuffix .o,$(TARGETLIST))) -o $(TEMP)/program.elf 

	$(OBJCOPY) -O binary $(TEMP)/program.elf $(OUTFILE)

	$(GBAFIX) $(OUTFILE)

clean:
	rm -f $(TEMP)/*.o