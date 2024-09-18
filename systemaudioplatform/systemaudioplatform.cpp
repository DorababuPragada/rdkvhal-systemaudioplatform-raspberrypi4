#include "systemaudioplatform.h"
#include "logger.h"
#include <cmath>

void systemAudioInitialize()
{
    
}

void systemAudioDeinitialize()
{
    
}

void systemAudioChangePrimaryVol(MixGain gain, int volume)
{
    	
}

bool systemAudioGeneratePipeline(GstElement  *pipeline, GstElement  *source,GstElement *capsfilter,GstElement **audioSink,GstElement **audioVolume,AudioType type,PlayMode mode,SourceType sourceType,bool smartVolumeEnable)
{
return true;
}

void systemAudioSetThreshold(double thresHold)
{
    //NA on realtek
}

void systemAudioSetVolume(GstElement *audioVolume,AudioType audioType,PlayMode playMode,int thisVol)
{
     //NA
}

//Player set DetectTime
void systemAudioSetDetectTime( int detectTimeMs)
{   
    //NA on realtek
}

//Player set HoldTime
void systemAudioSetHoldTime( int holdTimeMs)
{   
    //NA on realtek
}

