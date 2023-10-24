#include <cstdlib>
#include <ios>
#include <iostream>
#include <fstream>
#include <iterator>
#include <ostream>
#include <stdexcept>
#include <vector>
#include <string>
// Takes a binary and pads it with zeros until it is of 1.4 MB.


int get_file_size(std::string &file_path) {
    std::ifstream file(file_path, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cout << "Could not open file " << file_path <<  " for getting file_size" << std::endl;
        exit(1);
    }
    return file.tellg();
}

void pad_with_zeros(
        std::string &input_file_path,
        int input_file_size,
        std::string &output_file_path,
        int padding_size) {

    std::ifstream input_file(input_file_path, std::ios::binary);
    if (!input_file) {
        std::cout << "Could not open input file " << input_file_path << " for reading" << std::endl;
        exit(1);
    }
    // read the input_file into memory
    std::vector<char> input_file_data(input_file_size);
    if (!input_file.read(input_file_data.data(), input_file_size)) {
        std::cout << "Could not read input file " << input_file_path << " data ";
        exit(1);
    }

    std::ofstream output_file(output_file_path, std::ios::binary);

    if (!output_file) {
        std::cout << "Could not open file" << output_file_path << " for padding " << std::endl;
        exit(1);
    }

    std::vector<unsigned char> padding(padding_size, 0x00);

    output_file.write(reinterpret_cast<char*>(input_file_data.data()), input_file_data.size());
    output_file.write(reinterpret_cast<char*>(padding.data()), padding.size());
}

int main() {
    std::string input_file_path = "./build/main_floppy.img";
    int file_size = get_file_size(input_file_path);
    std::cout << "file size" << file_size << "\n";
    int to_pad = 1440000 - file_size;

    std::string output_file_path = "./build/main_floppy_big.img";
    pad_with_zeros(input_file_path, file_size, output_file_path, to_pad);
}
