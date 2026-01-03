#include "raylib.h"
#include <cstdlib>

int main() {
    InitWindow(800, 450, "raycer");

    Vector3 carPosition = {0.0f, 0.0f, 0.0f};

    Camera3D camera = {};
    camera.position = (Vector3){0.0f, 10.0f, 10.0f};
    camera.target = carPosition;
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawFPS(10, 10);

        BeginMode3D(camera);

        DrawGrid(10, 1.0f);

        DrawCube(carPosition, 2.0f, 1.0f, 4.0f, RED);

        DrawCubeWires(carPosition, 2.0f, 1.0f, 4.0f, MAROON);

        EndMode3D();

        EndDrawing();
    }

    CloseWindow();

    return EXIT_SUCCESS;
}
