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
#include "Dielectric.h"

int main(int, char**)
{
    std::cout << "Hello World \nRayTracer is successfully building!\n";
    seedRandom((unsigned int)time(nullptr));

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("Ray Tracer", 500, 400);

    Canvas canvas(500, 400, renderer);

    float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
    std::shared_ptr<Camera> camera = std::make_shared<Camera>
        (
            glm::vec3{ 0, 1, -11 }, 
            glm::vec3{ 0, 0, 0 }, 
            glm::vec3{ 0, 1, 0 }, 
            20.0f, 
            aspectRatio
        );

    Scene scene(8, glm::vec3{ 1.0f }, glm::vec3{ 0.5f, 0.7f, 1.0f });
    scene.SetCamera(camera);

    // Create material
    auto material = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
    auto lambertian = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
    auto metal = std::make_shared<Metal>(color3_t{ 0, 0, 1 }, 5);


    // Create and add the plane
    material = std::make_shared<Lambertian>(color3_t{ 1, 1, 1 });
    auto plane = std::make_unique<Plane>(glm::vec3{ 1, -1, 1 }, glm::vec3{ 0, 1, 0 }, material);
    scene.AddObject(std::move(plane));

    // Create and add the triangle
    material = std::make_shared<Lambertian>(color3_t{ 1, 0, 0 });
    auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 1, 0 }, glm::vec3{ 2, 1, 0 }, glm::vec3{ -2, 1, 0 }, material);
    scene.AddObject(std::move(triangle));

    // Create and add spheres
    for (int x = 0; x < 2; x++)
    {
        for (int z = -10; z < 10; z++)
        {

            std::shared_ptr<Material> material;

            // create random material
            float r = random01();
            if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
            else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
            else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
            else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

            // set random sphere radius
            float radius = random(0.2f, 0.3f);
            // create sphere using random radius and material
            auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
            // add sphere to the scene
            scene.AddObject(std::move(sphere));
        }
    }

    // Render scene
    // canvas.Clear({ 0, 0, 0, 1 });
    scene.Render(canvas, 20);
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
