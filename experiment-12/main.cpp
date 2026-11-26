#include <cstddef>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <new>

template <typename T>
class CustomAllocator {
public:
    using value_type = T;

    CustomAllocator() = default;

    template <typename U>
    CustomAllocator(const CustomAllocator<U>&) noexcept {}

    T* allocate(std::size_t count) {
        std::cout << "Allocating memory for " << count << " object(s)\n";
        return static_cast<T*>(::operator new(count * sizeof(T)));
    }

    void deallocate(T* pointer, std::size_t) noexcept {
        std::cout << "Deallocating memory\n";
        ::operator delete(pointer);
    }
};

struct FileRecord {
    char fileName[50]{};
    int fileSize = 0;
};

void addFile() {
    FileRecord file{};
    std::cout << "Enter File Name: ";
    std::cin >> std::setw(sizeof(file.fileName)) >> file.fileName;
    std::cout << "Enter File Size (KB): ";
    std::cin >> file.fileSize;

    if (!std::cin || file.fileSize < 0) {
        std::cout << "Invalid file record.\n";
        return;
    }

    std::ofstream outFile("filesystem.dat", std::ios::binary | std::ios::app);
    if (!outFile) {
        std::cout << "Unable to open file.\n";
        return;
    }

    outFile.write(reinterpret_cast<const char*>(&file), sizeof(file));
    if (outFile)
        std::cout << "File record added successfully.\n";
    else
        std::cout << "Unable to write file record.\n";
}

void displayFiles() {
    std::ifstream inFile("filesystem.dat", std::ios::binary);
    if (!inFile) {
        std::cout << "No file records found.\n";
        return;
    }

    FileRecord file{};
    bool found = false;
    std::cout << "\n--- File System Records ---\n";
    while (inFile.read(reinterpret_cast<char*>(&file), sizeof(file))) {
        found = true;
        std::cout << "File Name : " << file.fileName << '\n'
                  << "File Size : " << file.fileSize << " KB\n"
                  << "--------------------------\n";
    }
    if (!found)
        std::cout << "No file records found.\n";
}

int main() {
    int choice = 0;
    do {
        std::cout << "\nMINI FILE SYSTEM SIMULATOR\n"
                  << "1. Add File\n"
                  << "2. Display Files\n"
                  << "3. Exit\n"
                  << "Enter your choice: ";
        if (!(std::cin >> choice)) {
            std::cout << "Invalid choice.\n";
            return 1;
        }

        switch (choice) {
        case 1:
            addFile();
            break;
        case 2:
            displayFiles();
            break;
        case 3:
            std::cout << "Exiting File System Simulator...\n";
            break;
        default:
            std::cout << "Invalid choice.\n";
        }
    } while (choice != 3);
}
