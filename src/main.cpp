#include <iostream>
#include <raylib.h>
#include <deque>

using namespace std;

// Define colors for the game grid
Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

// Define cell size and count for the game grid
int cellSize = 30;
int cellCount = 25;

class Snake
{
public:
    deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};

    void Draw()
    {
        for (unsigned int i = 0; i < body.size(); i++)
        {
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment = Rectangle{x * cellSize, y * cellSize, (float)cellSize, (float)cellSize};

            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
        }
    }
};

// Food class definition
class Food
{
public:
    // Food position on the grid
    Vector2 position;
    // Texture for the food
    Texture2D texture;

    // Constructor: Load the food texture
    Food()
    {
        Image image = LoadImage("src/graphics/food.png"); // Load the food image
        texture = LoadTextureFromImage(image);            // Convert the image to a texture
        UnloadImage(image);                               // Unload the image from memory

        position = GenerateRandomPos();
    }

    // Destructor: Unload the food texture
    ~Food()
    {
        UnloadTexture(texture);
    }

    // Draw the food on the screen
    void Draw()
    {
        // DrawRectangle(position.x * cellSize, position.y * cellSize, cellSize, cellSize, darkGreen);
        DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
    }

    // Generate Random position on the screen
    Vector2 GenerateRandomPos()
    {
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);
        return Vector2{x, y};
    }
};

// Main function
int main()
{
    // Initialize the window with the calculated dimensions and title
    InitWindow(cellSize * cellCount, cellSize * cellCount, "Retro Snake");
    // Set the target frames per second (FPS)
    SetTargetFPS(60);

    // Create a Food object
    Food food = Food();
    // Create a Snake Object
    Snake snake = Snake();

    // Main game loop
    while (WindowShouldClose() == false)
    {
        // Begin drawing phase
        BeginDrawing();

        // Clear the background with the green color
        ClearBackground(green);
        // Draw the food on the screen
        food.Draw();
        // Draw the snake on the scree
        snake.Draw();

        // End drawing phase
        EndDrawing();
    };

    // Close the window and free resources
    CloseWindow();

    // Return 0 to indicate successful execution
    return 0;
}
