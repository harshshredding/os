ASM=nasm
SRC_DIR=src
BUILD_DIR=build


$(BUILD_DIR)/main_floppy.img: $(BUILD_DIR)/main.bin $(BUILD_DIR)/pad
	cp $(BUILD_DIR)/main.bin $(BUILD_DIR)/main_floppy.img
	./$(BUILD_DIR)/pad

# compile the program that pads our operating system floppy
$(BUILD_DIR)/pad: $(SRC_DIR)/pad.cpp
	clang++ $(SRC_DIR)/pad.cpp -o $(BUILD_DIR)/pad

$(BUILD_DIR)/main.bin: $(SRC_DIR)/main.asm
	$(ASM) $(SRC_DIR)/main.asm -f bin -o $(BUILD_DIR)/main.bin
