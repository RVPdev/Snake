#include <raylib.h>

// Define colors for the game grid
Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

// Define cell size and count for the game grid
int cellSize = 30;
int cellCount = 25;

// Food class definition
class Food
{
public:
    // Food position on the grid
    Vector2 position = {5, 6};
    // Texture for the food
    Texture2D texture;

    // Constructor: Load the food texture
    Food()
    {
        Image image = LoadImage("graphics/food.png");  // Load the food image
        texture = LoadTextureFromImage(image);         // Convert the image to a texture
        UnloadImage(image);                            // Unload the image from memory
    }

    // Destructor: Unload the food texture
    ~Food()
    {
        UnloadTexture(texture);
    }

    // Draw the food on the screen
    void Draw()
    {
        DrawRectangle(position.x * cellSize, position.y * cellSize, cellSize, cellSize, darkGreen);
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

    // Main game loop
    while (WindowShouldClose() == false)
    {
        // Begin drawing phase
        BeginDrawing();

        // Clear the background with the green color
        ClearBackground(green);
        // Draw the food on the screen
        food.Draw();

        // End drawing phase
        EndDrawing();
    };

    // Close the window and free resources
    CloseWindow();

    // Return 0 to indicate successful execution
    return 0;
}
