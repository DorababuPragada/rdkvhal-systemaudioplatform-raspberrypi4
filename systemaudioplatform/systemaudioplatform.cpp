#include "systemaudioplatform.h"
#include "RtkHALMisc.h"
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
      if(gain == MIXGAIN_PRIM)
      {		
          hal_set_audio_volume(volume);
      }		
}

bool systemAudioGeneratePipeline(GstElement  *pipeline, GstElement  *source,GstElement *capsfilter,GstElement **audioSink,GstElement **audioVolume,AudioType type,PlayMode mode,SourceType sourceType,bool smartVolumeEnable)
{
    
    GstElement *convert = gst_element_factory_make("audioconvert", NULL);
    GstElement *resample = gst_element_factory_make("audioresample", NULL);
    GstElement *audiofilter = gst_element_factory_make("capsfilter", NULL);
    GstCaps *audiocaps = NULL;
    *audioSink = gst_element_factory_make("rtkaudiosink", NULL);
    *audioVolume = gst_element_factory_make("volume", NULL);
    audiocaps = gst_caps_new_simple("audio/x-raw", "channels", G_TYPE_INT, 2, "rate", G_TYPE_INT, 48000, NULL);
    g_object_set( G_OBJECT(audiofilter),  "caps",  audiocaps, NULL );
    gst_caps_unref(audiocaps);
    g_object_set(G_OBJECT(*audioSink), "media-tunnel",  FALSE, NULL);
    g_object_set(G_OBJECT(*audioSink), "audio-service",  TRUE, NULL);
    
    bool result = TRUE; 

    if(type == MP3)
    {
        GstElement *parser = gst_element_factory_make("mpegaudioparse", NULL);
        GstElement *decodebin = gst_element_factory_make("avdec_mp3", NULL);
        gst_bin_add_many(GST_BIN(pipeline), source, parser, convert, resample, audiofilter, decodebin, *audioSink, *audioVolume, NULL);
        result = gst_element_link_many (source, parser, decodebin, convert, resample, audiofilter, *audioVolume, *audioSink, NULL);
    }
    else if(type == PCM)
    {   
        if(sourceType == DATA || sourceType == WEBSOCKET)
        {
            g_object_set(G_OBJECT(*audioSink), "async",  FALSE, NULL);
            gst_bin_add_many(GST_BIN(pipeline), source, convert, resample, audiofilter, *audioSink, *audioVolume, NULL);
            result = gst_element_link_many (source, convert, resample, audiofilter, *audioVolume, *audioSink,NULL);
        }
        else
        {   
            gst_bin_add_many(GST_BIN(pipeline), source, capsfilter, convert, resample,audiofilter,*audioVolume,*audioSink, NULL);
            result = gst_element_link_many (source, capsfilter, convert, resample, audiofilter, *audioVolume, *audioSink,NULL);			
        }
    }
    else
    {   //wav
        GstElement *wavparser = gst_element_factory_make("wavparse", NULL);        
        gst_bin_add_many(GST_BIN(pipeline), source, wavparser, convert, resample, audiofilter, *audioVolume, *audioSink, NULL);
        result = gst_element_link_many (source, wavparser, convert, resample, audiofilter, *audioVolume, *audioSink,NULL);
    }

return result;
}

void systemAudioSetThreshold(double thresHold)
{
    //NA on realtek
}

void systemAudioSetVolume(GstElement *audioVolume,AudioType audioType,PlayMode playMode,int thisVol)
{
     g_object_set(G_OBJECT(audioVolume), "volume", (double)thisVol/100, NULL);
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

