#include "audio.hpp"
#include <iostream>

Audio::Audio() {
  device = SDL_OpenAudioDevice(nullptr, 0, &spec, nullptr, 0);
  if (!device) {
    throw std::runtime_error("Sound device error: " + std::string(SDL_GetError()));
  }
  SDL_PauseAudioDevice(device, 0);

  audioThread = std::thread(&Audio::audioThreadFunc, this);
}

Audio::~Audio() {
  shouldStop = true;
  if (audioThread.joinable()) {
    audioThread.join();
  }
  if (device) {
    SDL_CloseAudioDevice(device);
  }
}

void Audio::PlaySound(std::string file) {
  std::string filepath = "../assets/" + file;
  std::lock_guard<std::mutex> lock(queueMutex);
  soundQueue.push(filepath);
}

void Audio::audioThreadFunc() {
  while(!shouldStop) {
    std::string filepath;

    // Try to get a sound from the queue (non-blocking)
    {
      std::lock_guard<std::mutex> lock(queueMutex);
      if (!soundQueue.empty()) {
        filepath = std::move(soundQueue.front());
        soundQueue.pop();
      }
    }

    if (!filepath.empty()) {
      uint8_t* wavBuffer = nullptr;
      SDL_AudioSpec dummy{};
      uint32_t wavLength = 0;

      std::cout << "Playing " << filepath << std::endl;

      if (SDL_LoadWAV(filepath.c_str(), &dummy, &wavBuffer, &wavLength) != nullptr) {
        SDL_QueueAudio(device, wavBuffer, wavLength);
        SDL_FreeWAV(wavBuffer);
      } else {
        std::cerr << "Failed to load WAV: " << filepath << " - " << SDL_GetError() << std::endl;
      }
    }
  }
}
