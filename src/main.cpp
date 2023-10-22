#include <raylib.h>

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;

class Food
{
public:
    Vector2 position = {5, 6};

    void Draw()
    {
        DrawRectangle(position.x * cellSize, position.y * cellSize, cellSize, cellSize, darkGreen);
    }
};

int main()
{
    // Initialiazing the screen paramaters
    InitWindow(cellSize * cellCount, cellSize * cellCount, "Retro Snake");
    SetTargetFPS(60);

    Food food = Food();

    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        ClearBackground(green); // Painting screen background green
        food.Draw();

        EndDrawing();
    };

    CloseWindow();

    return 0;
}