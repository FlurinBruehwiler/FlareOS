/* This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 */
void dummy_test_entrypoint() {
}

typedef enum{false,true} bool;  

typedef struct Vector2 {
    int x;
    int y;
} Vector2;

bool edgeFunction(Vector2 startLine, Vector2 endLIne, Vector2 point)
{
    return ((point.x - startLine.x) * (endLIne.y - startLine.y) - (point.y - startLine.y) * (endLIne.x - startLine.x) >= 0);
}

bool pointIsInsideTriangle(Vector2 v0, Vector2 v1, Vector2 v2, Vector2 point)
{
    bool inside = true;
    inside &= edgeFunction(v0, v1, point);
    inside &= edgeFunction(v1, v2, point);
    inside &= edgeFunction(v2, v0, point);

    return inside;
}

void setPixel(int x, int y, char color) {
    char *videoMemory = (char*)0xA0000;

    // Calculate the offset for the pixel at (x, y)
    int offset = (y * 320) + x;

    // Set the color at the calculated offset
    videoMemory[offset] = color;
}

void drawTriangle(Vector2 v0, Vector2 v1, Vector2 v2, char color){
    for (int x = 0; x < 200; ++x) {
        for (int y = 0; y < 200; ++y) {
            if(pointIsInsideTriangle(v0, v1, v2, (Vector2){ x, y })){
                setPixel(x, y, color);
            }
        }
    }
}

void main() {
    drawTriangle((Vector2){180, 20}, (Vector2){100, 100}, (Vector2){180, 180}, 14);
}

