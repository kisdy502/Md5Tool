#include <iostream>
#include <cstring>
#include "md5file.h"

using namespace std;

int main() {
    std::string md5 = getFileMD5("C:\\Users\\Administrator\\Desktop\\errorlog.txt");
    md5 = md5.substr(0, md5.length() - 1);
    int len2 = std::strlen("f33cbf57e4a2af4eaf8f2545726fa317");
    std::cout << "md5 len:" << md5.length() << std::endl;
    std::cout << "md5 len2:" << len2 << std::endl;
    std::cout << "equal:" << (md5 == "f33cbf57e4a2af4eaf8f2545726fa317") << endl;
    return 0;

    //f33cbf57e4a2af4eaf8f2545726fa317
    //F33CBF57E4A2AF4EAF8F2545726FA317
}