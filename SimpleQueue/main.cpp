#include "readwritequeue.h"

int main()
{
    moodycamel::ReaderWriterQueue<int> q(100);
    
    return 0;
}