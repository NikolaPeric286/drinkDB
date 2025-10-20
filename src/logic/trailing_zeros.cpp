#include "trailing_zeros.hpp"

std::string remove_trailing_zeros(std::string& str) {

    // ChatGPT Wrote this!

    // Find the index of the last character that is NOT '0'
    size_t last_non_zero = str.find_last_not_of('0');

    // If a non-zero character was found, erase everything after it.
    // If the string is all zeros, last_non_zero will be string::npos.
    // In that case, we clear the string or leave a single '0' if desired.
    if (last_non_zero != std::string::npos) {
        str.erase(last_non_zero + 1);
    } else {
        // Handle cases where the string is "0", "00", etc.
        // You might want to clear it or leave a single "0".
        // For example, to leave "0":
        if (!str.empty()) {
            str = "0";
        }
        // Or to clear it completely:
        // str.clear();
    }


    // I added this to remove the . if the number has no decimal 
    if(str.at(str.size()-1) == '.' ){
        str.pop_back();
    }

    return str;
}