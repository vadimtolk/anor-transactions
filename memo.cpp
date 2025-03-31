#include <iostream>
#include <windows.h>
#include <cstring>

std::pair<LPVOID, size_t>* allocMemory(size_t value) {
    LPVOID memo_ptr = VirtualAlloc(NULL, value, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    return memo_ptr ? new std::pair(memo_ptr, value) : nullptr;
}

LPVOID writeMemo(const std::string& data, const size_t& data_size, LPVOID next_free_byte, size_t free_memo) {
    if (data_size <= free_memo) {
        void* isWrote = memcpy(next_free_byte, data.data(), data_size);
        return static_cast<char*>(next_free_byte) + data_size;
    }

    return nullptr;
}

int main() {
    std::pair<LPVOID, size_t>* info = allocMemory(1024 * 1024);
    LPVOID next_free_byte = nullptr;

    if (info) {
        next_free_byte = info->first;
        std::cout << "Succsesful reserving of " << info->second << " bytes. First-byte's address : " << info->first << '\n';
    } else {
        std::cout << "Reserve Error." << std::endl;
        return 1;
    }

    std::string data = "";
    std::cout << "Enter your data : ";
    std::getline(std::cin, data);

    size_t freeMemo = info->second - ( static_cast<char*>(next_free_byte) - static_cast<char*>(info->first) );

    LPVOID isWrote = writeMemo(data, data.size() + 1, next_free_byte, freeMemo);

    if (isWrote) {
        next_free_byte = isWrote;
        std::cout << "Succsesful writing of " << data.size() + 1 << " bytes. Next-byte's address : " << next_free_byte << '\n';
    } else {
        std::cout << "Writing error." << std::endl;
        return 1;
    }

    char* st = static_cast<char*>(info->first);

    std::cout << st;

    VirtualFree(info->first, 0, MEM_RELEASE);
    delete info;

    return 0;
}