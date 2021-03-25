#ifndef _SOUND_MANAGER_
#define _SOUND_MANAGER_

#include <unordered_map>
#include <vector>
#include <mutex>

#define SAMPLE_FORMAT   ma_format_f32
#define CHANNEL_COUNT   2
#define SAMPLE_RATE     48000

#define VOLUME_MAX_VALUE 2.f

#include <memory>

struct ma_decoder;
struct ma_device;

typedef unsigned int sUint;

namespace Audio
{
    class Sound;

    enum class SoundType {S_MASTER, S_MUSIC, S_EFFECT};

    struct SoundData
    {
        ma_decoder* decoder;
        bool isActive {false};
        float volume {1.f};
        SoundType soundType {SoundType::S_EFFECT};

    };
    struct SoundManagerData
    {
        unsigned int ReadAndMixPcmFramesF32(const SoundData& soundData, float* pOutputF32, unsigned int frameCount);

        float masterVolume {1.0f};
        float effectVolume {1.0f};
        float musicVolume  {1.0f};

        std::unordered_map<sUint, SoundData> soundMap;

        float GetVolume(SoundType soundType);
    };


    class SoundManager
    {
        unsigned int _index {0};

        ma_device* _device;
        SoundManagerData _soundManagerData;

    public:
        SoundManager();
        ~SoundManager();

        /*Volume Function*/
        float GetMasterVolume();
        float SetMasterVolume(float newVolume);

        float GetVolume(SoundType soundType);
        float SetVolume(SoundType soundType, float newVolume);

        /*Sound Function*/
        Sound CreateSound(const char* path);

        void StartSound(sUint soundIndex);
        void StopSound(sUint soundIndex);
        void RestartSound(sUint soundIndex);

        float& SoundVolume(sUint soundIndex);
        SoundType& Sound_SoundType(sUint soundIndex);
    };
}

#endif