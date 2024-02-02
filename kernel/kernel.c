#include "../drivers/ports.h"

void random_sect()
{

}

int cursorX = 0;
int cursorY = 0;

void printC(int x, int y, char c)
{
    char* video_memory = (char*) 0xb8000;

    int offset = (80 * 2 * y) + x * 2;

    video_memory += offset;

    *video_memory = c;
}

int strlen(char* str)
{
    int counter = 0;

    while(str[counter] != 0)
    {
        counter++;   
    }

    return counter;
}

void print(char* str)
{
    int len = strlen(str);

    for(int i = 0; i < len; i++){
        printC(cursorX, cursorY, str[i]);
        cursorX++;
        if(cursorX == 80){
            cursorX = 0;
            cursorY++;
        }
    }
}

void print_decimal(int num)
{
    while(num != 0)
    {
        int digit = num % 10;

        char c = digit + '0';

        print(&c);

        num /= 10;
    }
}

void get_cursor_pos()
{
    port_byte_out(0x3d4, 14);
    int position = port_byte_in(0x3d5);
    position = position << 8;

    port_byte_out(0x3d4, 15);
    position += port_byte_in(0x3d5);

    int offset_from_vga = position * 2;

    char posToPrint = position % 10 + 48;

    print(&posToPrint);
}

void main() {
    
    get_cursor_pos();
}
