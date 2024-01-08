/* This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 */
void dummy_test_entrypoint() {
}

#define PI 3.14159265358979323846f
#define DEG2RAD (PI/180.0f)
#define RAD2DEG (180.0f/PI)

typedef enum{false,true} bool;  

typedef struct Vector3 {
    float x;
    float y;
    float z;
} Vector3;

typedef struct Camera3d {
    Vector3 position;
    Vector3 rotation;
} Camera3d;

typedef struct Point2d {
    int x;
    int y;
} Point2d;

typedef struct Matrix {
    float m0, m4, m8, m12;  // Matrix first row (4 components)
    float m1, m5, m9, m13;  // Matrix second row (4 components)
    float m2, m6, m10, m14; // Matrix third row (4 components)
    float m3, m7, m11, m15; // Matrix fourth row (4 components)
} Matrix;

float sinf(float x){
    float result;
    asm("fsin" : "=t"(result) : "0"(x));
    return result;
}

float cosf(float x){
    float result;
    asm("fcos" : "=t"(result) : "0"(x));
    return result;
}

float tan(float x){
    float result;
    asm("fptan" : "=t"(result) : "0"(x));
    return result;
}

Matrix MatrixIdentity(void)
{
    Matrix result = { 1.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 1.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 1.0f };

    return result;
}

Matrix MatrixRotateXYZ(Vector3 angle)
{
    Matrix result = MatrixIdentity();

    float cosz = cosf(-angle.z);
    float sinz = sinf(-angle.z);
    float cosy = cosf(-angle.y);
    float siny = sinf(-angle.y);
    float cosx = cosf(-angle.x);
    float sinx = sinf(-angle.x);

    result.m0 = cosz*cosy;
    result.m1 = (cosz*siny*sinx) - (sinz*cosx);
    result.m2 = (cosz*siny*cosx) + (sinz*sinx);

    result.m4 = sinz*cosy;
    result.m5 = (sinz*siny*sinx) + (cosz*cosx);
    result.m6 = (sinz*siny*cosx) - (cosz*sinx);

    result.m8 = -siny;
    result.m9 = cosy*sinx;
    result.m10= cosy*cosx;

    return result;
}

Matrix MatrixTranslate(float x, float y, float z)
{
    Matrix result = { 1.0f, 0.0f, 0.0f, x,
                      0.0f, 1.0f, 0.0f, y,
                      0.0f, 0.0f, 1.0f, z,
                      0.0f, 0.0f, 0.0f, 1.0f };

    return result;
}

Matrix MatrixMultiply(Matrix left, Matrix right)
{
    Matrix result = { 0 };

    result.m0 = left.m0*right.m0 + left.m1*right.m4 + left.m2*right.m8 + left.m3*right.m12;
    result.m1 = left.m0*right.m1 + left.m1*right.m5 + left.m2*right.m9 + left.m3*right.m13;
    result.m2 = left.m0*right.m2 + left.m1*right.m6 + left.m2*right.m10 + left.m3*right.m14;
    result.m3 = left.m0*right.m3 + left.m1*right.m7 + left.m2*right.m11 + left.m3*right.m15;
    result.m4 = left.m4*right.m0 + left.m5*right.m4 + left.m6*right.m8 + left.m7*right.m12;
    result.m5 = left.m4*right.m1 + left.m5*right.m5 + left.m6*right.m9 + left.m7*right.m13;
    result.m6 = left.m4*right.m2 + left.m5*right.m6 + left.m6*right.m10 + left.m7*right.m14;
    result.m7 = left.m4*right.m3 + left.m5*right.m7 + left.m6*right.m11 + left.m7*right.m15;
    result.m8 = left.m8*right.m0 + left.m9*right.m4 + left.m10*right.m8 + left.m11*right.m12;
    result.m9 = left.m8*right.m1 + left.m9*right.m5 + left.m10*right.m9 + left.m11*right.m13;
    result.m10 = left.m8*right.m2 + left.m9*right.m6 + left.m10*right.m10 + left.m11*right.m14;
    result.m11 = left.m8*right.m3 + left.m9*right.m7 + left.m10*right.m11 + left.m11*right.m15;
    result.m12 = left.m12*right.m0 + left.m13*right.m4 + left.m14*right.m8 + left.m15*right.m12;
    result.m13 = left.m12*right.m1 + left.m13*right.m5 + left.m14*right.m9 + left.m15*right.m13;
    result.m14 = left.m12*right.m2 + left.m13*right.m6 + left.m14*right.m10 + left.m15*right.m14;
    result.m15 = left.m12*right.m3 + left.m13*right.m7 + left.m14*right.m11 + left.m15*right.m15;

    return result;
}

//fov as rad
Matrix MatrixPerspective(double fovY, double aspect, double nearPlane, double farPlane)
{
    Matrix result = { 0 };

    double top = nearPlane*tan(fovY*0.5);
    double bottom = -top;
    double right = top*aspect;
    double left = -right;

    // MatrixFrustum(-right, right, -top, top, near, far);
    float rl = (float)(right - left);
    float tb = (float)(top - bottom);
    float fn = (float)(farPlane - nearPlane);

    result.m0 = ((float)nearPlane*2.0f)/rl;
    result.m5 = ((float)nearPlane*2.0f)/tb;
    result.m8 = ((float)right + (float)left)/rl;
    result.m9 = ((float)top + (float)bottom)/tb;
    result.m10 = -((float)farPlane + (float)nearPlane)/fn;
    result.m11 = -1.0f;
    result.m14 = -((float)farPlane*(float)nearPlane*2.0f)/fn;

    return result;
}

Vector3 Vector3Transform(Vector3 v, Matrix mat)
{
    Vector3 result = { 0 };

    float x = v.x;
    float y = v.y;
    float z = v.z;

    result.x = mat.m0*x + mat.m4*y + mat.m8*z + mat.m12;
    result.y = mat.m1*x + mat.m5*y + mat.m9*z + mat.m13;
    result.z = mat.m2*x + mat.m6*y + mat.m10*z + mat.m14;

    return result;
}

//transformation matrix
Matrix GetCameraViewMatrix(Camera3d camera){
    Matrix positionMatrix = MatrixTranslate(camera.position.x, camera.position.y, camera.position.z);
    Matrix rotationMatrix = MatrixRotateXYZ((Vector3){ camera.rotation.x * DEG2RAD, camera.rotation.y * DEG2RAD, camera.rotation.z * DEG2RAD });

    Matrix viewMatrix = MatrixMultiply(positionMatrix, rotationMatrix);

    return viewMatrix;
}

Matrix GetCameraProjectionMatrix(){
    return MatrixPerspective(90 * DEG2RAD, 1, 0.1, 1000);
}

Matrix WorldToScreenMatrix(Camera3d camera){
    Matrix viewMatrix = GetCameraViewMatrix(camera);
    Matrix projectionMatrix = GetCameraProjectionMatrix();
    return MatrixMultiply(viewMatrix, projectionMatrix);
}

bool edgeFunction(Point2d startLine, Point2d endLIne, Point2d point)
{
    return ((point.x - startLine.x) * (endLIne.y - startLine.y) - (point.y - startLine.y) * (endLIne.x - startLine.x) >= 0);
}

bool pointIsInsideTriangle(Point2d v0, Point2d v1, Point2d v2, Point2d point)
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

int min(int a, int b)
{
    if(a < b)
        return a;
    return b;
}

int max(int a, int b)
{
    if(a > b)
        return a;
    return b;
}

//counter clockwise
void drawTriangle(Camera3d camera, Vector3 v0, Vector3 v1, Vector3 v2, char color){
    Matrix matrix = WorldToScreenMatrix(camera); 

    v0 = Vector3Transform(v0, matrix);
    v1 = Vector3Transform(v1, matrix);
    v2 = Vector3Transform(v2, matrix);

    int minX = min(v0.x, min(v1.x, v2.x));
    int minY = min(v0.y, min(v1.y, v2.y));
    int maxX = max(v0.x, max(v1.x, v2.x));
    int maxY = max(v0.y, max(v1.y, v2.y));
    
    for (int x = minX; x < maxX; ++x) {
        for (int y = minY; y < maxY; ++y) {
            if(pointIsInsideTriangle((Point2d){ v0.x, v0.y }, (Point2d){ v1.x, v1.y }, (Point2d){ v2.x, v2.y }, (Point2d){ x, y })){
                setPixel(x, y, color);
            }
        }
    }
}

void main() {
    Camera3d camera = {};

    drawTriangle(camera, (Vector3){20, 20}, (Vector3){20, 100}, (Vector3){100, 100}, 13);
    drawTriangle(camera, (Vector3){100, 100}, (Vector3){100, 20}, (Vector3){20, 20}, 14);
}

//very good article explaining matrix stuff: https://gamedev.stackexchange.com/questions/178643/the-view-matrix-finally-explained