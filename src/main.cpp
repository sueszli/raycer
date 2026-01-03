#include "raylib.h"
#include "rlgl.h"
#include <cmath>
#include <cstdint>
#include <cstdlib>

std::int32_t main() {
    InitWindow(800, 450, "raycer");

    // car state
    Vector3 carPosition = {0.0f, 0.0f, 0.0f};
    float speed = 10.0f; // Units per second

    Camera3D camera = {};
    // camera.position and target are updated in the loop
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        DrawFPS(10, 10);

        // update
        float dt = GetFrameTime();
        carPosition.z -= speed * dt;

        // camera follow
        camera.target = carPosition;
        camera.position = (Vector3){carPosition.x + 0.0f, carPosition.y + 10.0f, carPosition.z + 10.0f};

        // draw
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(camera);

        // infinite grid effect: draw grid offset by the rounded car position so it always appears under the car
        rlPushMatrix();
        rlTranslatef(0.0f, 0.0f, roundf(carPosition.z));
        DrawGrid(200, 1.0f);
        rlPopMatrix();

        // draw car
        DrawCube(carPosition, 2.0f, 1.0f, 4.0f, RED);
        DrawCubeWires(carPosition, 2.0f, 1.0f, 4.0f, MAROON);

        EndMode3D();

        EndDrawing();
    }

    CloseWindow();

    return EXIT_SUCCESS;
}
