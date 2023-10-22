#include <raylib.h>

Color green = {173,204,96,255};
Color darkGreen = {43,51,24,255};

int main()
{
    // Initialiazing the screen paramaters
    InitWindow(750, 750, "Retro Snake");

    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        ClearBackground(green);  // Painting screen background green

        EndDrawing();
    };

    CloseWindow();

    return 0;
}