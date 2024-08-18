#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
using namespace std;

#define BINARY_PATH "challenge.bin"

ifstream::pos_type get_file_size(const string path) {
    filesystem::path p(path);
    uintmax_t size = filesystem::file_size(p);
    return size;
}

int load_program(const string path, char* memory_region) {
    ifstream fptr(path, std::ios::binary);
    fptr.read(memory_region, get_file_size(path));
    return 0;
}

int main() {
    ifstream::pos_type file_size = get_file_size(BINARY_PATH);
    cout << "File size: " << file_size << " bytes" << endl;
    char* vm_memory = (char*) calloc(file_size, 1);
    load_program(BINARY_PATH, vm_memory);
    return 0;
}