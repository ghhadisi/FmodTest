//
// Created by acerhss on 17-10-26.
//

#include <jni.h>
#include "include/fmod.hpp"
#include "include/fmod_dsp.h"
#include "include/fmod_dsp_effects.h"
#include <android/log.h>
#include <unistd.h>
#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"jason",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"jason",FORMAT,##__VA_ARGS__);

#define MODE_NORMAL 0
#define MODE_LUOLI 1
#define MODE_DASHU 2
#define MODE_JINGSONG 3
#define MODE_GAOGUAI 4
#define MODE_KONGLING 5


extern  "C"{
JNIEXPORT void JNICALL
    Java_com_dbgs_fmodtest_MainActivity_playSound(JNIEnv *env, jobject instance, jstring path_,
                                                  jint type) {
        const char *path = env->GetStringUTFChars( path_, 0);

        // TODO
    FMOD::System     *system;
    FMOD::Sound      *sound1;
    FMOD::Channel    *channel = 0;
    FMOD_RESULT       result;
    unsigned int      version;
    void             *extradriverdata = 0;
    bool         playing = true;
    FMOD::DSP       *dsp;

    /*
          Create a System object and initialize
      */
    result = FMOD::System_Create(&system);

//    ERRCHECK(result);
    result = system->getVersion(&version);
//    ERRCHECK(result);
    if (version < FMOD_VERSION)
    {
//        Common_Fatal("FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);
    }
    result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
//    ERRCHECK(result);
    result = system->createSound(path, FMOD_DEFAULT, 0, &sound1);
//    ERRCHECK(result);

    result = sound1->setMode(FMOD_LOOP_OFF);
    float frequency;

//    ERRCHECK(result);
    /*
          Main loop
      */
    try {
        switch (type){

            case MODE_NORMAL:
            default:
                result = system->playSound(sound1, 0, false, &channel);
                LOGE("%s","正常");
                break;

            case MODE_LUOLI:
                LOGI("%s","萝莉");
                //FMOD_DSP_TYPE_PITCHSHIFT提高音调，但是又不改变语速
                result = system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                //2.0代表调高一个八度(12345671)
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH,2.5);
                result = system->playSound(sound1, 0, false, &channel);
                channel->addDSP(0,dsp);
                result = dsp->setBypass(true);

                break;
            case MODE_DASHU:
                LOGI("%s","大叔");
                //FMOD_DSP_TYPE_PITCHSHIFT提高音调，但是又不改变语速
                result = system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                //2.0代表调高一个八度(12345671)
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH,0.8);
                //system->createDSPByType(FMOD_DSP_TYPE_DELAY, &dsp);
                //dsp->setParameterFloat(FMOD_DSP_DELAY_CH0,200);
                result = system->playSound(sound1, 0, false, &channel);
                channel->addDSP(0,dsp);
                result = dsp->setBypass(true);

                break;
            case MODE_JINGSONG :
                LOGI("%s","惊悚");
                //FMOD_DSP_TYPE_TREMOLO 颤抖
                result = system->createDSPByType(FMOD_DSP_TYPE_TREMOLO, &dsp);
                //2.0代表调高一个八度(12345671)
                dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW,0.8);
                //system->createDSPByType(FMOD_DSP_TYPE_DELAY, &dsp);
                //dsp->setParameterFloat(FMOD_DSP_DELAY_CH0,200);
                result = system->playSound(sound1, 0, false, &channel);
                channel->addDSP(0,dsp);
                result = dsp->setBypass(true);
                break;
            case MODE_GAOGUAI:
                LOGI("%s","搞怪");
                result = system->createDSPByType(FMOD_DSP_TYPE_NORMALIZE, &dsp);
                //2.0代表调高一个八度(12345671)
//                dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW,0.8);
                //system->createDSPByType(FMOD_DSP_TYPE_DELAY, &dsp);
                //dsp->setParameterFloat(FMOD_DSP_DELAY_CH0,200);
                result = system->playSound(sound1, 0, false, &channel);
                channel->addDSP(0,dsp);
                channel->getFrequency(&frequency);
                frequency = frequency*1.6;
                channel->setFrequency(frequency);
                result = dsp->setBypass(true);
                break;
            case MODE_KONGLING :
                LOGI("%s","空灵");
                system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
                dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY,300);
                dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK,20);
                system->playSound(sound1, NULL, false, &channel);
                channel->addDSP(0, dsp);
                break;
        }


    }catch (...){
        LOGE("%s","发送异常");
        goto end;
    }


    result = system->update();
//检查是否结束播放
    while(playing){
        channel->isPlaying(&playing);
        usleep(1000);
    }
end:
    result = sound1->release();
    result = system->close();
    result = system->release();
    env->ReleaseStringUTFChars( path_, path);
    }
}
