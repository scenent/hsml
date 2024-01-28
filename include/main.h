#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <istream>
#include <Windows.h>

#include "scanner.h"
#include "parser.h"
#include "interpreter.h"

static std::wstring s2ws(const std::string& val) {
    std::wstring result(val.begin(), val.end());
    return result;
}

static std::string getCurPath() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
}

static std::wstring getCurPathW() {
    return s2ws(getCurPath());
}

static size_t getSizeOfFile(const std::wstring& path) {
    struct _stat fileinfo;
    _wstat(path.c_str(), &fileinfo);
    return fileinfo.st_size;
}

static std::wstring readFileW(const std::wstring& filename) {
    std::wstring buffer;
    FILE* f;
    _wfopen_s(&f, filename.c_str(), L"rtS, ccs=UTF-8");
    if (f == NULL) return buffer;
    size_t filesize = getSizeOfFile(filename);
    if (filesize > 0) {
        buffer.resize(filesize);
        size_t wchars_read = fread(&(buffer.front()), sizeof(wchar_t), filesize, f);
        buffer.resize(wchars_read);
        buffer.shrink_to_fit();
    }
    fclose(f);
    return buffer;
}




#endif