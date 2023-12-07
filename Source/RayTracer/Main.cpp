#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "MathUtils.h"
#include "Canvas.h"
#include "Scene.h"
#include "Material.h"
#include "Color.h"
#include <memory>
#include "Sphere.h"
#include "Object.h"
#include "Triangle.h"
#include "Plane.h"

int main(int, char**)
{
    std::cout << "Hello World \nRayTracer is successfully building!\n";
    seedRandom((unsigned int)time(nullptr));

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("Ray Tracer", 500, 400);

    Canvas canvas(500, 400, renderer);

    float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(
        glm::vec3{ 0, 0, -2.0 },
        glm::vec3{ 0.5, 0, 0 },
        glm::vec3{ 0, 1, 0 },
        70.0f,
        aspectRatio
    );

    Scene scene(20);
    scene.SetCamera(camera);

    // Create material
    auto material = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
    auto lambertian = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
    auto metal = std::make_shared<Metal>(color3_t{ 0, 0, 1 }, 5);


    // Create and add the plane
    material = std::make_shared<Lambertian>(color3_t{ 1, 1, 1 });
    auto plane = std::make_unique<Plane>(glm::vec3{ 1, -1, 1 }, glm::vec3{ 0, 1, 0 }, material);
    scene.AddObject(std::move(plane));

    // Create and add spheres
    for (int i = 0; i < 5; i++)
    {
        float radius = random(0.1f, 0.2f);
        glm::vec3 position = random(glm::vec3{ -2, 0, -1 }, glm::vec3{ 0, 1, 0 });
        std::shared_ptr<Material> material = (std::rand() % 2 == 0) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);

        auto sphere = std::make_unique<Sphere>(position, radius, material);
        scene.AddObject(std::move(sphere));
    }

    // Render scene
    // canvas.Clear({ 0, 0, 0, 1 });
    scene.Render(canvas, 10);
    canvas.Update();

    // MAIN LOOP
    bool quit = false;
    while (!quit)
    {
        // Event loop
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        }
        renderer.PresentCanvas(canvas);
    }

    renderer.Shutdown();
    return 0;
}
