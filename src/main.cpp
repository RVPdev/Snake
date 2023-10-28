#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>

using namespace std;

// Define colors for the game grid
Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

// Define cell size and count for the game grid
int cellSize = 30;
int cellCount = 25;

// Initialize a variable to keep track of the last update time
double lastUpdateTime = 0;

// Function to check if a given Vector2 element exists in a deque of Vector2 elements
bool ElementInDeque(Vector2 element, deque<Vector2> deque)
{
    // Loop through each element in the deque
    for (unsigned int i = 0; i < deque.size(); i++)
    {
        // Check if the current deque element matches the given element
        if (Vector2Equals(deque[i], element))
        {
            return true; // Element found, return true
        }
    }

    return false; // Element not found, return false
};

// Function to check if an event should be triggered based on a time interval
bool eventTriggered(double interval)
{
    // Get the current time using Raylib's GetTime function
    double currentTime = GetTime();

    // Check if the time elapsed since the last update is greater than or equal to the specified interval
    if (currentTime - lastUpdateTime >= interval)
    {
        // Update the last update time to the current time
        lastUpdateTime = currentTime;

        // Return true to indicate that the event should be triggered
        return true;
    }

    // Return false if the time elapsed is less than the specified interval
    return false;
}

// Snake class definition
class Snake
{
public:
    // Initialize the snake's body as a deque of Vector2 objects
    // The snake starts with three segments at positions (6,9), (5,9), and (4,9)
    deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};

    // Initialize the snake's direction to move right (1,0)
    Vector2 direction = {1, 0};

    bool addSegment = false;

    // Draw the snake on the screen
    void Draw()
    {
        // Loop through each segment in the snake's body
        for (unsigned int i = 0; i < body.size(); i++)
        {
            // Get the x and y coordinates of the current segment
            float x = body[i].x;
            float y = body[i].y;

            // Create a Rectangle object for the current segment
            Rectangle segment = Rectangle{x * cellSize, y * cellSize, (float)cellSize, (float)cellSize};

            // Draw the segment as a rounded rectangle on the screen
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
        }
    }

    // Update the snake's position based on its current direction
    void Update()
    {
        // Add a new segment at the front of the snake's body.
        // This new segment's position is calculated by adding the current direction to the position of the current head segment.
        body.push_front(Vector2Add(body[0], direction));

        // Check if a new segment needs to be added permanently (usually after eating food)
        if (addSegment == true)
        {
            // Reset the flag so no more segments are added until the next food is eaten
            addSegment = false;
        }
        else
        {
            // Remove the last segment from the snake's body to maintain the same length.
            // This effectively moves the snake forward.
            body.pop_back();
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
    Food(deque<Vector2> snakeBody)
    {
        Image image = LoadImage("src/graphics/food.png"); // Load the food image
        texture = LoadTextureFromImage(image);            // Convert the image to a texture
        UnloadImage(image);                               // Unload the image from memory

        position = GenerateRandomPos(snakeBody);
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

    // Function to generate a random cell position within the grid
    Vector2 GenerateRandomCell()
    {
        float x = GetRandomValue(0, cellCount - 1); // Generate a random x-coordinate within the grid
        float y = GetRandomValue(0, cellCount - 1); // Generate a random y-coordinate within the grid
        return Vector2{x, y};                       // Return the generated coordinates as a Vector2
    }

    // Function to generate a random position on the screen that is not occupied by the snake
    Vector2 GenerateRandomPos(deque<Vector2> snakeBody)
    {
        Vector2 position = GenerateRandomCell(); // Generate an initial random cell position

        // Keep generating new positions until we find one not occupied by the snake
        while (ElementInDeque(position, snakeBody))
        {
            position = GenerateRandomCell(); // Generate a new random cell position
        }
        return position; // Return the generated position that is not occupied by the snake
    }
};

// Define the Game class to encapsulate all game-related functionalities
class Game
{
public:
    // Create instances of the Snake and Food classes
    Snake snake = Snake();
    Food food = Food(snake.body);

    // Draw method to render the game elements on the screen
    void Draw()
    {
        food.Draw();  // Draw the food on the screen
        snake.Draw(); // Draw the snake on the screen
    }

    // Update method to handle the game logic
    void Update()
    {
        snake.Update();           // Update the snake's position based on its current direction
        CheckCollisionWithFood(); // Check if the snake has collided with the food
    }

    // Method to check if the snake's head has collided with the food
    void CheckCollisionWithFood()
    {
        // Check if the first element of the snake's body (the head) is at the same position as the food
        if (Vector2Equals(snake.body[0], food.position))
        {
            // If so, generate a new random position for the food that is not occupied by the snake
            food.position = food.GenerateRandomPos(snake.body);
            snake.addSegment = true;
        }
    }
};

// Main function
int main()
{
    // Initialize the window with the calculated dimensions and title
    InitWindow(cellSize * cellCount, cellSize * cellCount, "Retro Snake");
    // Set the target frames per second (FPS)
    SetTargetFPS(60);

    Game game = Game();

    // Main game loop
    while (WindowShouldClose() == false)
    {
        // Begin drawing phase
        BeginDrawing();

        // Update movement per every .2 seconds
        if (eventTriggered(0.2))
        {
            // move the snake boyd
            game.Update();
        }

        // Check if the UP arrow key is pressed and the snake is not already moving downward
        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1)
        {
            // Set the snake's direction to move upward
            game.snake.direction = {0, -1};
        }

        // Check if the DOWN arrow key is pressed and the snake is not already moving upward
        if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1)
        {
            // Set the snake's direction to move downward
            game.snake.direction = {0, 1};
        }

        // Check if the LEFT arrow key is pressed and the snake is not already moving to the right
        if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1)
        {
            // Set the snake's direction to move to the left
            game.snake.direction = {-1, 0};
        }

        // Check if the RIGHT arrow key is pressed and the snake is not already moving to the left
        if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1)
        {
            // Set the snake's direction to move to the right
            game.snake.direction = {1, 0};
        }

        // Clear the background with the green color
        ClearBackground(green);

        game.Draw();

        // End drawing phase
        EndDrawing();
    };

    // Close the window and free resources
    CloseWindow();

    // Return 0 to indicate successful execution
    return 0;
}
