#ifndef __STRING_UTILS_H__
#define __STRING_UTILS_H__

#include <string>

template<typename ... Args>
std::string string_format(const std::string &format, Args ... args ) {
    int len = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // +1 extra space for '\0'
    char buffer[len] = "";
    if (len <= 0) { 
        throw std::runtime_error( "Error during formatting." ); 
    }
    std::snprintf(buffer, len, format.c_str(), args ... );
    std::string str_output(buffer);
    return str_output;
}

#endif
