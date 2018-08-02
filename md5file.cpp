//
// Created by Administrator on 2018/7/24.
//

#include "md5file.h"
#include "md5global.h"
#include "md5.h"

#include <fstream>
#include <sstream>
#include <memory>
#include <iomanip>
#include <exception>

using namespace std;

string getFileMD5(const string &filename) {

    ifstream fin(filename.c_str(), ifstream::in | ifstream::binary);
    if (fin) {
        MD5_CTX context;
        MD5Init(&context);

        fin.seekg(0, fin.end);
        const auto fileLength = fin.tellg();
        printf("fileLength:%d",fileLength);
        fin.seekg(0, fin.beg);

        const int bufferLen = 8192;
        unique_ptr<unsigned char[]> buffer{new unsigned char[bufferLen]{}};
        unsigned long long totalReadCount = 0;
        decltype(fin.gcount()) readCount = 0;

        // 读取文件内容，调用MD5Update()更新MD5值
        while (fin.read(reinterpret_cast<char *>(buffer.get()), bufferLen)) {
            readCount = fin.gcount();
            totalReadCount += readCount;
            MD5Update(&context, buffer.get(), static_cast<unsigned int>(readCount));
        }

        readCount = fin.gcount();
        if (readCount > 0) {
            totalReadCount += readCount;
            MD5Update(&context, buffer.get(), static_cast<unsigned int>(readCount));
        }
        fin.close();


        // 数据完整性检查
        if (totalReadCount != fileLength) {
            ostringstream oss;
            oss << "FATAL ERROR: read " << filename << " failed!" << ends;
            throw runtime_error(oss.str());
        }

        unsigned char digest[16];
        MD5Final(digest, &context);

        // 获取MD5
        ostringstream oss;
        for (int i = 0; i < 16; ++i) {
            oss << hex << setw(2) << setfill('0') << static_cast<unsigned int>(digest[i]);
        }
        oss << ends;

        return move(oss.str());
    } else {
        ostringstream oss;
        oss << "FATAL ERROR: " << filename << " can't be opened" << ends;
        throw runtime_error(oss.str());
    }
}
