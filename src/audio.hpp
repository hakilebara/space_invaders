#ifndef AUDIO_H
#define AUDIO_H

#include "SDL.h"
#include <string>
#include <thread>
#include <queue>
#include <mutex>
#include <atomic>

class Audio {
  public:
    Audio();
    ~Audio();
    void PlaySound(std::string filepath);

  private:
    void audioThreadFunc();


    SDL_AudioDeviceID device;

    // https://wiki.libsdl.org/SDL2/SDL_AudioSpec
    SDL_AudioSpec spec {
      11025,        // frequency
      AUDIO_U8,     // format
      1,            // channels
      0,            // silence
      512,          // samples
      0,            // padding
      0,            // size
      nullptr,      // callback
      nullptr       // userdata
    };

    std::thread audioThread;
    std::queue<std::string> soundQueue;
    std::mutex queueMutex;
    std::atomic<bool> shouldStop{false};
};

#endif
