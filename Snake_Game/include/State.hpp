#pragma once

namespace Engine
{
    class State
    {
        public:
            virtual void Init() = 0; 
            virtual void ProcessInput() = 0;
            virtual void Update(float deltaTime) = 0;
            virtual void Draw(float deltaTime) = 0;

            virtual void Pause() {};
            virtual void Resume() {};
    };
}