//
// Created by sunjinlong01 on 2022/6/5.
//

#include<stdio.h>
#ifndef PYTHON_BUFFEREDINPUTSTREAM_H
#define PYTHON_BUFFEREDINPUTSTREAM_H

#define BUFFER_SIZE 256

class BufferedInputStream{
private:
    FILE* fp; // 文件指针
    char szBuffer[BUFFER_SIZE]; // 读缓冲区
    int index; // 文件位置索引
public:
    BufferedInputStream(const char * filename){
        fp = fopen(filename, "rb");
        fread(szBuffer, BUFFER_SIZE * sizeof(char), 1, fp);
        index = 0;
    }
    ~BufferedInputStream(){
        close();
    }

    // read 读1个字节
    const char read(){
        if (index < BUFFER_SIZE){
            return szBuffer[index++];
        }else{
            index = 0;
            fread(szBuffer, BUFFER_SIZE * sizeof(char), 1, fp);
            return szBuffer[index++];
        }
    }

    // unread
    void unread(){
        index --;
    }

    // readint 读4个字节
    int readint(){
        /*
         *  小端存储 | b1 | b2 | b3 | b4 |
         *  b4 b3 b2 b1
         * */

        int byte1 = int(read() & 0xff) << (0 * 8);
        int byte2 = int(read() & 0xff) << (1 * 8);
        int byte3 = int(read() & 0xff) << (2 * 8);
        int byte4 = int(read() & 0xff) << (3 * 8);

        return byte1 | byte2 | byte3 | byte4;
    }

    // close 关闭文件流
    void close(){
        if (fp != NULL){
            fclose(fp);
            fp = NULL;
        }

    }

};


#endif //PYTHON_BUFFEREDINPUTSTREAM_H
