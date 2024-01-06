/* This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 */
void dummy_test_entrypoint() {
}

int strlen(char *s)
{
    int i = 0;
    while(s[i] != 0)
    {
        i++;
    }
    return i;
}

void strcpy(char* from, char* to)
{
    int fromLen = strlen(from);
    for(int i = 0; i < fromLen; i++)
    {
        to[i] = from[i];
    }
}

void print(char* s, char color)
{
    char* video_memory = (char*) 0xb8000;
    
    int fromLen = strlen(s);
    for(int i = 0; i < fromLen; i++)
    {
        video_memory[i * 2] = s[i];
        video_memory[(i * 2) + 1] = color;
    }
}

void main() {
    char *string_to_display = "FlareOs 4 the win";
    print(string_to_display, 0x5);
}

