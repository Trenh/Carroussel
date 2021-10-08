#include "Game.h"
#include "Carousel.h"
#include "Timer.h"
#include "Maths.h"

bool Game::initialize() {
    return !window.init();
}

void Game::load() {

    // Creation of an Actor
    Actor* carousel = new Carousel("carousel");
    carousel->setWorldPosition(0, 0, 10);

    // Init the Actor
    for (auto a : actors) {
        a->init();
    }
}

void Game::loop() {
    while (!window.windowShouldClose()) {
        // update the window (clear, resize, ...)
        window.update();

        /*
        -------------------------------------------------
            Camera View update
        -------------------------------------------------
        */
        const bx::Vec3 at = { 5.0f, 0.0f,  10.0f };
        const bx::Vec3 eye = { -8.0f, 7.0f, 3.0f };
        float view[16];
        bx::mtxLookAt(view, eye, at);
        float proj[16];
        bx::mtxProj(proj, 90.0f, float(window.getWidth()) / float(window.getHeight()), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
        bgfx::setViewTransform(0, view, proj);


        Actor* carousel = searchActor("carousel");
        if (carousel != nullptr) {
            carousel->setWorldRotation(0, 0, -Maths::cos(Timer::getTime())* 22.5 + 22.5);
        }

        // Actor update
        for (auto a : actors) {
            a->update();
        }

        // Go to the next frame
        bgfx::frame();
    }
}

void Game::unload() {
    actors.clear();
}

void Game::close() {
    bgfx::shutdown();
    window.shutdown();
}

void Game::addActor(Actor* actor)
{
    actors.emplace_back(actor);
}

void Game::removeActor(Actor* actor)
{
    // Erase actor from the two vectors
    auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
    if (iter != end(pendingActors))
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, end(pendingActors) - 1);
        pendingActors.pop_back();
    }
    iter = std::find(begin(actors), end(actors), actor);
    if (iter != end(actors))
    {
        std::iter_swap(iter, end(actors) - 1);
        actors.pop_back();
    }
}

Actor* Game::searchActor(char* actorName)
{
    for (auto a : actors) {
        if (a->isTheActor(actorName)) {
            return a;
        }
    }
    return nullptr;
}