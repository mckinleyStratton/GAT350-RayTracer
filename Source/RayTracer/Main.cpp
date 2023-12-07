#include "Renderer.h"
#include "Canvas.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include "Object.h"
#include "Triangle.h"
#include "Plane.h"
#include "Dielectric.h"
#include "Mesh.h"

#include <memory>
#include <iostream>

void InitScene01(Scene& scene, const Canvas& canvas);
void InitScene02(Scene& scene, const Canvas& canvas);

int main(int, char**)
{
    //std::cout << "Hello World \nRayTracer is successfully building!\n";

    const int width = 500;
    const int height = 400;
    const int samples = 10;
    const int depth = 2;

    seedRandom((unsigned int)time(nullptr));

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("Ray Tracer", width, height);

    Canvas canvas(width, height, renderer);
    Scene scene(glm::vec3{ 1.0f }, glm::vec3{ 0.5f, 0.7f, 1.0f });

    InitScene02(scene, canvas);

    // render scene
    canvas.Clear({ 0, 0, 0, 1 });
    scene.Render(canvas, samples, depth);
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

void InitScene01(Scene& scene, const Canvas& canvas)
{
    float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
    std::shared_ptr<Camera> camera = std::make_shared<Camera>
        (
            glm::vec3{ 0, 2, 10 },
            glm::vec3{ 0, 1, 0 }, 
            glm::vec3{ 0, 1, 0 }, 
            50.0f,
            aspectRatio
        );

    scene.SetCamera(camera);

    auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 2, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
    scene.AddObject(std::move(triangle));

    auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
    scene.AddObject(std::move(plane));

}

void InitScene02(Scene& scene, const Canvas& canvas)
{
    float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
    std::shared_ptr<Camera> camera = std::make_shared<Camera>
        (
            glm::vec3{ 0, 2, 20 },
            glm::vec3{ 0, 1, 0 },
            glm::vec3{ 0, 1, 0 },
            50.0f,
            aspectRatio
        );

    scene.SetCamera(camera);
   
    auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.9f }));
    scene.AddObject(std::move(plane));

    auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0, 1 }));
    mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0}, glm::vec3{ 1, 0, 0 });
    scene.AddObject(std::move(mesh));
}
