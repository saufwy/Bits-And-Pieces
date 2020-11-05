#include <iostream>
#include <ctype.h>

int my_atoi(const char* str) {
    if (str == nullptr) {
        return 0;
    }
    while (isspace(*str)) {
        ++str;
    }
    char sign = '+';
    if (*str == '-' || *str == '+') {
        sign = *str++;
    }

    int total = 0;
    while (isdigit(*str)) {
        total = total * 10 + (*str++ - '0');
    }
    if (sign == '-') {
        return -total;
    }
    return total;
}

int main() {
    const char* str = "  -789";
    std::cout << my_atoi(str) << std::endl;
    return 0;
}

