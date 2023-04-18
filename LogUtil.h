#ifndef __LOGUTIL_H__
#define __LOGUTIL_H__

template<typename T>
std::string c_string_list(const std::vector<T> &list) {
    std::ostringstream oss;
    for (T x: list) {
        oss << x << ", ";
    }
    std::string str = oss.str();
    str = str.substr(0, str.length() - 2);
    // char *c_str = new char[str.length()+1];
    // std::strcpy(c_str, str.c_str());
    return str;
}

#endif
