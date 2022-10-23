/**
 * @file lab2.cpp
 * @author TengBo (156294753@qq.com)
 * @brief 数据结构实验2 Huffman编码压缩文件
 * @version 0.2
 * @date 2022-10-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <fstream>
#include <string.h>
#include <bitset>
#define MAX_SIZE 1010

using namespace std;

typedef struct HuffmanTree{
    char name;  // 字符
    int lchild; // 左孩子
    int rchild; // 右孩子
    int parent; // 双亲
    int count;
}HFNODE;    // 哈夫曼树结点

HFNODE T[MAX_SIZE];

typedef struct{
    char ch;
    char bit[MAX_SIZE];
}CodeNode;  // 编码结点
typedef CodeNode HuffmanCode[MAX_SIZE];
HuffmanCode H;  // 存储字符编码

char ch[MAX_SIZE];  // 记录出现过的字符
int tt_ch = -1;  // 记录字符数
int count_ch[MAX_SIZE] = {0};  // 各字符对应下标为其ASCII码值，储存值为其频率
int length_str = 0;
unsigned char bytebuffer = 0;  // 按将code按位存储进byterbuffer
int count_bit = 0;  // 记录位数
bool bit_flag = false;  // 判断
int cot = 0; // 记录01序列长度

void bitbuffer(fstream* f, char* temp);
string read_bits(string file_path);
string r_txt(string file_path);  // 从txt文件中读取文本字符串并返回
void SelectMin(int n, int* p1, int* p2);  // 选取最小和次小元素
void init_Huffman_tree();  // 初始化Huffman树
void count_frequency(string file_str);  // 计算各字符频率并储存打印
void creat_Huffman_coding_tree();  // 创建文件的Huffman树,并得到编码
void print_Huffman_code();  // 打印Huffman编码
void creat_Huffman_file(string file_str);  // 得到Huffman编码压缩文件
void read_Huffman_file(string H_file_path);  // 读取Huffman编码压缩文件

void bitbuffer(fstream* f, char* temp)  // 将编码01序列转化为bit序列存储
{
    /**
     * @brief 这一部分的代码是接受字符的01序列编码并将01序列按位存储，
     * 由于计算机数据操作的最小单位是 字节(byte) 所以可以将01序列
     * “凑齐8位”之后再以 char（一字节）的形式二进制式存进文件
     * 
     * 其中主要的难点在：
     * 1.位运算的操作
     * 
     * bytebuffer（char） 作为临时过渡变量，初始二进制序列为 00000000
     * 每次循环左移一位并将01数字写入末位
     * 当满8位时 二进制写入文件 并重置 bytebuffer 为 00000000
     * 
     * count_bit 则是 bytebuffer 已使用位数的记录，每到8便重置为0
     * 
     * cot 用于记录 01序列 总长度，便于后续的读取
     */

    int i = 0;
    while(temp[i] != '\0')  // 当编码未遍历结束
    {
        bytebuffer = bytebuffer << 1;  // 左移一位为下一位空出位置
        if(temp[i] == '1') bytebuffer = bytebuffer | 1;  // 如果code等于1，则将bytebuffer最右位取1
        count_bit ++;  
        if(count_bit == 8)  // 集齐8位，则写入文件
        {
            f->write((char*)&bytebuffer,sizeof(bytebuffer));
            bytebuffer = 0;  // 初始化
            count_bit = 0;  // 初始化
        }
        i++;
    }
    cot += i;
}

string read_bits(string file_path)  // 从二进制文件中读取01序列并返回string
{
    /**
     * @brief read_bits 函数接受二进制文件，以01序列读取并以string类型的变量返回
     * 
     * 我们需要的是每一位的0|1，但文件的读取只能以字符为最小单位，因此该函数的难点在于
     * 如何将读取出来的字符 逐位取出 并记录。
     * 这里使用的方法是 
     * c >> i & 1
     * 意思是从 c 字符的首位开始，逐个遍历
     * 每次遍历与 0000 .... 0001 进行 & 操作，便可获得该位数字
     * 再加入 bitstring 中即可
     * 
     */
    string bitstring;  // 储存01序列

    ifstream f;
    f.open(file_path, ios::binary);
    char c;

    while(f.get(c))
    {
        for(int i = 7; i >= 0; i--)
        {
            // cout << ((c >> i) & 1);

            if(c >> i & 1)  // 从首到尾，按位判断bit并加入string中
                bitstring += '1';
            else 
                bitstring += '0';
        }
    }

    f.close();

    return bitstring; // 返回filestring
}

string r_txt(string file_path)  // 获取原txt文件内容
{
    string file_str;
    ifstream fin;

    fin.open(file_path,ios::in);

    if(fin.is_open())
    {
        while(getline(fin,file_str));
    }
    fin.close();

    return file_str;  // 返回字符串
}

void SelectMin(int n, int* p1, int* p2)  // 找出两个最小的
{
    /**
     * @brief SelectMin 函数作用是从剩下的字符中找到出现频率 最小的和次小的字符
     * 并返回两个数的下标
     * 没有什么难度
     * 
     */
    int mini = 127;
    T[mini].count = 10000;

    for(int i = 0; i <= n; i ++)
    {
        char c = T[i].name;
        if(T[i].parent == -1 && T[i].count <= T[mini].count)
        {
            mini = i;
        }
    }
    *p1 = mini;
    T[*p1].parent = 0;

    mini = 127;
    for(int i = 0; i <= n; i ++)
    {
        char c = T[i].name;
        if(T[i].parent == -1 && T[i].count <= T[mini].count)
        {
            mini = i;
        }
    }
    *p2 = mini;
}

void count_frequency(char* file_str)   // 计算字符出现频率
{
    /**
     * @brief count_frequency 函数接受 string 类型变量
     * 作用是计算字符串中各字符出现的频率并打印出来
     * 没有什么难度
     */
    for(int i = 0; i < length_str; i ++)
    {
        char c = file_str[i];

        if(count_ch[c - ' '] == 0)
            ch[ ++tt_ch ] = c;
        count_ch[c - ' ']++;
    }

    cout << "-character-|-frequency-" << endl;  
    for (int i = 0; i <= tt_ch; i ++)  // 打印出来
    {
        char c = ch[i];

        if (c == ' ')
        {
            cout << "  (space)   " << "\t" << count_ch[c - ' '] << endl;
        }
        else if(c == '\n')
        {
            cout << "  (line)  " << "\t" << count_ch[c - ' '] << endl;
        }
        else
        {
            cout << "     " << c << "\t\t" << count_ch[c - ' '] << endl;
        }
    }
    cout << endl;
}

void init_Huffman_tree()  // 初始化Huffman树
{   
    /**
     * @brief init_Huffman_tree 函数的作用是初始化Huffman编码树，只初始需要的空间
     * 没有什么难度
     * 
     */
    for (int i = 0; i <= 2*tt_ch ; i++ )
    {
        T[i].name = ch[i];
        T[i].lchild = -1;
        T[i].rchild = -1;
        T[i].parent = -1;
        T[i].count = count_ch[ch[i] - ' '];
    }
}

void creat_Huffman_coding_tree()  // 创建Huffman编码树
{
    /**
     * @brief creat_Huffman_coding_tree 函数的作用是利用字符出现频率创建Huffman编码树
     * 
     * 难点在于
     * 1.树中 双亲与孩子 关系的设置
     * 2.回溯法求各字符的编码
     * 
     * 回溯法求字符编码，
     * 从各叶子节点开始，往上走，直到根节点，
     * 过程中若前一节点是后一节点的左孩子，则编码＋'0'
     * 否则＋'0'
     * 
     */
    int p1, p2;
    for (int i = tt_ch + 1; i < 2*(tt_ch+1) - 1; i ++)
    {
        SelectMin(i - 1, &p1, &p2);  // 找到两个频率最小的字符
        T[p1].parent = i;
        T[p2].parent = i;
        T[i].lchild = p1;
        T[i].rchild = p2;
        T[i].count = T[p1].count + T[p2].count;
    }

    char temp_cd[MAX_SIZE]; //临时存储编码
    int start;  // 位置记录
    temp_cd[MAX_SIZE - 1] = '\0';  // 编码结束位置

    int c, p;  // c , p分别记录孩子和双亲
    for(int i = 0; i <= tt_ch; i ++)  // 依次遍历叶子结点，回溯
    {
        char ch = T[i].name;
        H[i].ch = ch;
        c = i;
        start = MAX_SIZE - 1;
        while((p = T[c].parent) >= 0)  // 向上回溯直到根节点
        {
            char code = T[p].lchild == c ? '0' : '1';
            temp_cd[ --start ] = code;
            c = p;
        }
        strcpy(H[i].bit, &temp_cd[start]);  // clone 编码到编码表
    }

}

void print_Huffman_code()  // 打印Huffman编码
{
    cout << "-character-|-HuffmanCode-" << endl;

    for(int i = 0; i <= tt_ch; i ++)
    {
        if(H[i].ch == ' ')
            cout << "  (space)  " << "\t" << H[i].bit << endl;
        else if(H[i].ch == '\n')
            cout << "  (line) " << "\t" << H[i].bit << endl;
        else
            cout << "     " << H[i].ch << "\t\t" << H[i].bit << endl;
    } 
}

void creat_Huffman_file(string file_str,string H_file_path)  // 压缩并创建文件
{
    /**
     * @brief creat_Huffman_file 函数的作用是压缩并创建压缩文件
     * 
     * 总的来说是对之前函数的使用，按顺序看即可
     * 
     */
    fstream fout;
    // 打开压缩文件，并准备写入
    fout.open(H_file_path,ios::out|ios::binary);

    // 逐个读取原文件字符串，匹配其编码后
    // 利用 bitbuffer 函数将其写入文件
    for(int i = 0; i < file_str.size(); i ++)
    {
        char ch = file_str[i];

        int j;
        for(j = 0; j <= tt_ch; j ++)
        {
            if (H[j].ch == ch)
             break;
        }
        
        bitbuffer(&fout, H[j].bit);  
    }

    // 若01序列总数非8的倍数，则进行补位
    // 功能实现与 bitbuffer函数 类似
    if(count_bit > 0)
    {
        bit_flag = true;
        bytebuffer <<= 1;
        bytebuffer |= 1;

        for(int i = count_bit + 1; i < 8; i ++)
        {
            bytebuffer <<= 1;
        }
        fout.write((char*) &bytebuffer, sizeof(bytebuffer));
    }    

    fout.close();
}

void read_Huffman_file(string H_file_path)  // 读取文件并译码
{
    /**
     * @brief read_Huffman_file 函数的作用是读取压缩文件并进行译码
     * 
     * 没有什么难度，按顺序看即可
     * 
     */
    ifstream fin;  // 从压缩文件中读取
    fstream Hfout;  // 写入译码之后的文件
    
    string newfile_path = "newfile.txt";

    string file_code;
    file_code = read_bits(H_file_path);  // 获取压缩文件01序列字符串
    Hfout.open(newfile_path,ios::out);  // 打开解压后的文件，准备写入
    
    int start = 2*tt_ch;  // 从根节点开始

    // 循环 cot 次，即有效01序列总长度
    for(int i = 0; i < cot; i ++)
    {
        if(T[start].name == '\0')  // 如果是非叶节点
        {
            if(file_code[i] == '0')
            {
                start = T[start].lchild;
            }
            else if(file_code[i] == '1')
            {
                start = T[start].rchild;
            }
        }
        else  // 到达叶子节点
        {
            char c = T[start].name;
            start = 2*tt_ch;  // 回到根

            Hfout << c;  // 写入文件
            i--;
        }
    }
    fin.close();
    Hfout.close();

}

void cal_CpRate()  // 计算压缩率
{
    double raw_size;  // 原始文件大小
    double cp_size;  // 压缩文件大小
    double cp_rate;  // 压缩率

    raw_size = (length_str-1);
    cp_size = (cot + 8 - count_bit) / 8;
    cp_rate = (cp_size / raw_size) * 100;

    cout << '\n' << "original file size is : " << raw_size << " byte." << endl;
    cout << "Compressed file size is : " << cp_size << " byte." << endl;
    cout << "Compression ratio is : " << cp_rate << " %." << endl;
}

int main()
{
    string file_path = "E:/code/c++/hit_dts/content.txt";  // 待压缩文件路径
    char file_str[100010];

    ifstream fin;

    fin.open(file_path,ios::in);

    char c;
    while(fin.get(c))
    {
        file_str[ length_str++ ] = c;
    }
    fin.close();

    // cout << file_str << endl;
    cout << "Original file: " << endl;
    cout << file_str << endl << endl;

    count_frequency(file_str);  // 计算字符出现频率
    init_Huffman_tree();  // 初始化HuffmanTree
    creat_Huffman_coding_tree();  // 创建Huffman编码树
    print_Huffman_code();  // 打印
    // 在得到字符对应编码的前提下，对源文件进行压缩
    string H_file_path = "H_content.txt";
    creat_Huffman_file(file_str,H_file_path);  // 编码获得压缩文件
    
    read_Huffman_file(H_file_path);  // 译码

    char newfile_str[100010];
    fin.open("newfile.txt",ios::in);

    int copy_c = 0;
    while(fin.get(c))
    {
        newfile_str[ copy_c++ ] = c;
    }
    fin.close();

    cout << "\n" << "file after decompression: " << endl;\
    cout << newfile_str << endl;

    cal_CpRate();

    system("pause");
    return 0;
}

