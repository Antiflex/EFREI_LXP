// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
// Copyright (c) 2017 Magic Leap, Inc. All Rights Reserved.
// Use of this file is governed by the Software License Agreement,
// located here: https://www.magicleap.com/software-license-agreement-ml2
// Terms and conditions applicable to third-party materials accompanying
// this distribution may also be found in the top-level NOTICE file
// appearing herein.
// %COPYRIGHT_END%
// ---------------------------------------------------------------------
// %BANNER_END%

#pragma once

#include "ml_api.h"
#include "ml_types.h"

ML_EXTERN_C_BEGIN

/*!
  \addtogroup Audio
  \sharedobject audio.magicleap
  \brief APIs for the Audio Service.

  The Audio Service supports audio input (capture) and audio output (render).

  The audio capture capabilities of the Audio Service include capturing:

  \li Mono mic signal focused on the user's voice (Voice Comm & Voice Capture).

  \li Stereo mic signal of the ambient environment (World Capture).

  \li Stereo mix of the audio output currently being rendered (Virtual Capture).

  \li Six-channel mix of unprocessed raw mic data (Raw Mics & AEC Reference).

  \li Mix of voice capture, world capture and virtual capture (Mixed Capture).

  To initiate a capture input, the client allocates an 'input' using one of the
  create functions, followed by a 'start' call to initiate the input. The audio
  input streaming can be accomplished either by polling or callbacks.

  The audio render capabilities for the Audio Service include rendering:

  \li An audio file fully loaded into memory (Loaded File).

  \li An audio file streamed from flash memory in chunks (Streamed File).

  \li A buffered stream of audio output (Buffered Output).

  To initiate a render output, the client allocates a 'sound' using one of
  the create functions, followed by a 'start' call to play the audio. For the
  first two rendering options, the audio file can either be passed to the create
  function of a specific sound, or pre-loaded as a persistent 'resource' to be
  used by multiple sounds that get created and destroyed. For the third rendering
  option, buffered streaming can be accomplished either by polling or callbacks.
  For sounds where audio spatialization is desired, the client must enable
  'spatial sound' for that sound and set its position along with other optional
  spatial sound parameters.
  \{
*/

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
///                      AUDIO DEFINITIONS.
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

/*!
  \defgroup AudioDefs Audio Definitions
  \ingroup Audio
  \addtogroup AudioDefs
  \{
*/

/////////////////////
///    CONTROL.
/////////////////////

/*!
  \defgroup DefControl Control
  \ingroup AudioDefs
  \addtogroup DefControl
  \{
*/

/*! Possible playback states for sounds and inputs. */
typedef enum MLAudioState {
  /*! Stopped, can be started. */
  MLAudioState_Stopped,
  /*! Playing, can be stopped or paused. */
  MLAudioState_Playing,
  /*! Paused, can be resumed or re-started. */
  MLAudioState_Paused,
  /*! Ensure enum is represented as 32 bits. */
  MLAudioState_Ensure32Bits = 0x7FFFFFFF
} MLAudioState;

/*! Possible events for individual sound outputs. */
typedef enum MLAudioSoundEvent {
  /*! A sound output has reached the end and is stopping. */
  MLAudioSoundEvent_End,
  /*! A sound output has reached the end and is looping. */
  MLAudioSoundEvent_Loop,
  /*! A sound output has been muted due to system conditions. */
  MLAudioSoundEvent_MutedBySystem,
  /*! A previously muted sound output has been unmuted due to system conditions. */
  MLAudioSoundEvent_UnmutedBySystem,
  /*! A sound output has been ducked due to system conditions. */
  MLAudioSoundEvent_DuckedBySystem,
  /*! A previously ducked sound output has been unducked due to system conditions. */
  MLAudioSoundEvent_UnduckedBySystem,
  /*! The resource used by a sound output has been destroyed. */
  MLAudioSoundEvent_ResourceDestroyed,
  /*! Ensure enum is represented as 32 bits. */
  MLAudioSoundEvent_Ensure32Bits = 0x7FFFFFFF
} MLAudioSoundEvent;

/*! Possible media control events initiated by the user. */
typedef enum MLAudioMediaEvent {
  /*! Indicates a user command to play. */
  MLAudioMediaEvent_Play,
  /*! Indicates a user command to stop. */
  MLAudioMediaEvent_Stop,
  /*! Indicates a user command to pause. */
  MLAudioMediaEvent_Pause,
  /*! Indicates a user command to go to next track. */
  MLAudioMediaEvent_NextTrack,
  /*! Indicates a user command to go to previous track. */
  MLAudioMediaEvent_PrevTrack,
  /*! Ensure enum is represented as 32 bits. */
  MLAudioMediaEvent_Ensure32Bits = 0x7FFFFFFF
} MLAudioMediaEvent;
/*! \} */

/////////////////////
///   PARAMETERS.
/////////////////////

/*!
  \defgroup DefParameters Parameters
  \ingroup AudioDefs
  \addtogroup DefParameters
  \{
*/

/*! The currently active output device. */
typedef enum MLAudioOutputDevice {
  /*! Built-in speakers in the wearable. */
  MLAudioOutputDevice_Wearable,
  /*! USB audio from the beltpack. */
  MLAudioOutputDevice_USB,
  /*! A2DP audio via Bluetooth. */
  MLAudioOutputDevice_Bluetooth,
  /*! Hearing Aid audio via Bluetooth. */
  MLAudioOutputDevice_HearingAid,
  /*! Ensure enum is represented as 32 bits. */
  MLAudioOutputDevice_Ensure32Bits = 0x7FFFFFFF
} MLAudioOutputDevice;
/*! \} */

/*!
  \brief The type of mic input to capture.

  \apilevel 29
*/
typedef enum MLAudioMicCaptureType {
    /*!
      \brief User voice, suitable for communications.
      Mono, 16 bit integer, 16k sampling rate.
    */
    MLAudioMicCaptureType_VoiceComm,
    /*!
      \brief High fidelity user voice, suitable for recording.
      Mono, 16 bit integer, 48k sampling rate.
    */
    MLAudioMicCaptureType_VoiceCapture,
    /*!
      \brief Mic mix representing the user's surroundings.
      Stereo, 16 bit integer, 48k sampling rate.
    */
    MLAudioMicCaptureType_WorldCapture=4,
    /*!
      \brief All 4 mics unprocessed (front L/R, side L/R) + AEC return from amp (L/R).
      Channel layout: 1 - Front L, 2 - Front R, 3 - Side L, 4 - Side R, 5 - AEC return L, 6 - AEC return R.
      DC Offset and/or background hum may be present on channels 1-4 due to lack of processing.
      6-channel, 16 bit integer, 48k sampling rate.
    */
    MLAudioMicCaptureType_RawMicsAndAECRef,
    /*! Ensure enum is represented as 32 bits. */
    MLAudioMicCaptureType_Ensure32Bits=0x7FFFFFFF
} MLAudioMicCaptureType;

/*!
  \brief Properties specifying a broadband level and three sub-band levels.

  \apilevel 20
*/
typedef struct MLAudioMultibandLevel {
  /*! Level for all frequencies. Range is contextual. Default is 1. */
  float main;
  /*! Level for low frequencies. Range is contextual. Default is 1. */
  float lf;
  /*! Level for mid frequencies. Range is contextual. Default is 1. */
  float mf;
  /*! Level for high frequencies. Range is contextual. Default is 1. */
  float hf;
} MLAudioMultibandLevel;

/////////////////////
///   ACOUSTICS.
/////////////////////

/*!
  \defgroup DefAcoustics Acoustics
  \ingroup AudioDefs
  \addtogroup DefAcoustics
  \{
*/

/*!
  \brief Properties specifying acoustic dispersion (clustered reflections).

  \apilevel 20
*/
typedef struct MLAudioDispersionProperties {
    /*! Dispersion output mix level. Range is [0, 0, 0, 0] to [8, 2, 2, 2]. Default is [0.25, 1, 1, 1]. */
    MLAudioMultibandLevel gain;
    /*! Delay (secs) from direct sound to earliest reflection cluster onset. Must be <= reverb pre_delay. Range is 0.005 to 0.1. Default is 0.01. */
    float pre_delay;
} MLAudioDispersionProperties;

/*!
  \brief Properties specifying acoustic reverberation.

  \apilevel 20
*/
typedef struct MLAudioReverbProperties {
    /*! Reverb output mix level. Range is [0, 0, 0, 0] to [8, 2, 2, 2]. Default is [0.16, 1, 1, 1]. */
    MLAudioMultibandLevel gain;
    /*! Delay (secs) from direct sound to the late reverberation onset. Must be >= dispersion pre_delay. Range is 0.02 to 0.1. Default is 0.03. */
    float pre_delay;
    /*! Decay time (secs) for late reverberation. Range is 0 to 20. Default is 0.7. */
    float decay_time;
    /*! Relative reverberation decay time multiplying factor for low frequencies. Range is 0.1 to 2. Default is 1. */
    float decay_time_lf_ratio;
    /*! Relative reverberation decay time multiplying factor for high frequencies. Range is 0.1 to 2. Default is 0.6.*/
    float decay_time_hf_ratio;
} MLAudioReverbProperties;

/////////////////////
/// SPATIAL SOUND.
/////////////////////

/*!
  \defgroup DefSpatialSound Spatial Sound
  \ingroup AudioDefs
  \addtogroup DefSpatialSound
  \{
*/

/*! Properties describing the distance attenuation of a spatial sound using two distances, between which attention values are interpolated. */
typedef struct MLAudioSpatialSoundDistanceProperties {
  /*! Distance until which sound is at full volume. Range is 0 to FLT_MAX. Default is 1. */
  float min_distance;
  /*! Distance beyond which sound gets no quieter. Range is min_distance to FLT_MAX. Default is FLT_MAX. */
  float max_distance;
  /*! Scale factor relative to real-world distance attenuation. Range is 0 to FLT_MAX. Default is 1 (real world). */
  float rolloff_factor;
} MLAudioSpatialSoundDistanceProperties;

/*! Properties describing the directionality of a spatial sound using two cones, between which attention values are interpolated. */
typedef struct MLAudioSpatialSoundRadiationProperties {
  /*! Angle in degrees defining the sides of a cone, within which there is no radiation attenuation. Range is 0 to 360. Default is 50. */
  float inner_angle;
  /*! Angle in degrees defining the sides of a cone, beyond which the outer_gain values are fully applied. Range is 0 to 360. Default is 340. */
  float outer_angle;
  /*! Gain applied beyond outer cone for all frequencies. Range is 0 to 1. Default is 1.  */
  float outer_gain;
  /*! Gain applied beyond outer cone for low frequencies. Range is 0 to 1. Default is 0.65. */
  float outer_gain_lf;
  /*! Gain applied beyond outer cone for mid frequencies. Range is 0 to 1. Default is 0.4. */
  float outer_gain_mf;
  /*! Gain applied beyond outer cone for high frequencies. Range is 0 to 1. Default is 0.08. */
  float outer_gain_hf;
} MLAudioSpatialSoundRadiationProperties;

/*!
  \brief Two points in space describing a ray.

  \apilevel 20
*/
typedef struct MLAudioRaycast {
    /*! Starting point of the ray. */
    MLVec3f eye_point;
    /*! Ending point of the ray. */
    MLVec3f end_point;
} MLAudioRaycast;

/*!
  \brief Obstruction along a ray.

  \apilevel 20
*/
typedef struct MLAudioObstruction {
    /*! Amount of obstruction [0-1] with 1 = fully applied transmission values. */
    float factor;
    /*! Location of obstruction. */
    MLVec3f hit_point;
}  MLAudioObstruction;

/*!
  \brief ID-tracked request for a single raycast operation.

  \apilevel 20
*/
typedef struct MLAudioRaycastRequest {
    /*! Internal identifier. */
    MLHandle source_id;
    /*! Internal identifier. */
    MLHandle image_id;
    /*! Internal identifier. */
    uint32_t leg_index;
    /*! Raycast to test for obstruction. */
    MLAudioRaycast ray;
} MLAudioRaycastRequest;

/*!
  \brief ID-tracked result for a single raycast operation.

  \apilevel 20
*/
typedef struct MLAudioRaycastResult {
    /*! Internal identifier. */
    MLHandle source_id;
    /*! Internal identifier. */
    MLHandle image_id;
    /*! Internal identifier. */
    uint32_t leg_index;
    /*! Raycast tested for obstruction. */
    MLAudioRaycast ray;
    /*! Result of obstruction test. */
    MLAudioObstruction obstruction;
} MLAudioRaycastResult;
/*! \} */

/////////////////////
///   BUFFERING.
/////////////////////

/*!
  \defgroup DefBuffering Buffering
  \ingroup AudioDefs
  \addtogroup DefBuffering
  \{
*/

/*! Possible sample formats for input and output streams. */
typedef enum MLAudioSampleFormat {
  /*! Samples are integer. */
  MLAudioSampleFormat_Int,
  /*! Samples are float. Not currently implemented for buffered I/O. */
  MLAudioSampleFormat_Float,
  /*! Ensure enum is represented as 32 bits. */
  MLAudioSampleFormat_Ensure32Bits = 0x7FFFFFFF
} MLAudioSampleFormat;

/*! Channel formats for buffered outputs. */
typedef enum MLAudioChannelFormat {
    /*! Infer channel format from buffer format settings. */
    MLAudioChannelFormat_Default,
    /*! Ambisonic AmbiX format. */
    MLAudioChannelFormat_AmbisonicAmbix,
    /*! Ensure enum is represented as 32 bits. */
    MLAudioChannelFormat_Ensure32Bits = 0x7FFFFFFF,
} MLAudioChannelFormat;

/*!
  \brief Buffer format settings for input and output streams.

  \apilevel 20
*/
typedef struct MLAudioBufferFormat {
  /*! Number of channels. */
  uint32_t channel_count;
  /*! Sample rate. */
  uint32_t samples_per_second;
  /*! Number of bits per sample. */
  uint32_t bits_per_sample;
  /*! Number of bits used per sample. */
  uint32_t valid_bits_per_sample;
  /*! Integer or float. Float is not currently implemented for buffered I/O. */
  MLAudioSampleFormat sample_format;
  /*! Channel configuration. */
  MLAudioChannelFormat channel_format;
} MLAudioBufferFormat;

/*! An audio buffer for passing data to/from buffered outputs and inputs. */
typedef struct MLAudioBuffer {
  /*! Pointer to audio data. */
  uint8_t *ptr;
  /*! Size of audio data in bytes. */
  uint32_t size;
} MLAudioBuffer;
/*! \} */

/////////////////////
///    ANALYSIS.
/////////////////////

/*!
  \defgroup DefAnalysis Analysis
  \ingroup AudioDefs
  \addtogroup DefAnalysis
  \{
*/

/*! Available trait analyses of an audio stream. */
typedef enum MLAudioTraitAnalysisTarget {
    /*! Ambient Sound Level dBFS, a full scale sound level measurement of an ambient mic stream. */
    MLAudioTraitAnalysisTarget_AmbientSoundLevelDbfs,
    /*! Voice Presence, indicates absence (0) or presence (1) of voice in a voice mic stream. */
    MLAudioTraitAnalysisTarget_UserVoicePresence,
    /*! Voice Level dBFS, a full scale sound level measurement of a voice mic stream. */
    MLAudioTraitAnalysisTarget_UserVoiceLevelDbfs,
    /*! Voice Pitch, frequency in hertz of the voice in a voice mic stream. */
    MLAudioTraitAnalysisTarget_UserVoicePitch,
    /*! Ensure enum is represented as 32 bits. */
    MLAudioTraitAnalysisTarget_Ensure32Bits = 0x7FFFFFFF
} MLAudioTraitAnalysisTarget;

/*! Available frequency spectrum analyses of an audio stream. */
typedef enum MLAudioSpectralAnalysisTarget {
    /*! Voice Mel Frequency Cepstral Coefficients (MFCC), spectral analysis of a voice mic stream. (typically used for lip-sync). */
    MLAudioSpectralAnalysisTarget_UserVoiceSpectrumMfcc,
    /*! Ambient Sound Spectrum Bark Scale, spectral analysis of ambient mic stream(s) using Bark scale. */
    MLAudioSpectralAnalysisTarget_AmbientSoundSpectrumBark,
    /*! Ambient Sound Spectrum Mel Scale, spectral analysis of ambient mic stream(s) using Mel scale. */
    MLAudioSpectralAnalysisTarget_AmbientSoundSpectrumMel,
    /*! Ambient Sound Spectrum Third Octave Scale, spectral analysis of ambient mic stream(s) using a 1/3 octave scale. */
    MLAudioSpectralAnalysisTarget_AmbientSoundSpectrumThirdOctave,
    /*! Ensure enum is represented as 32 bits. */
    MLAudioSpectralAnalysisTarget_Ensure32Bits = 0x7FFFFFFF
} MLAudioSpectralAnalysisTarget;

/*! A representation of frequency spectrum energy over a window of time. */
typedef struct MLAudioSpectralAnalysis {
    /*! Magnitudes of the spectral energy in a column-major matrix. */
    float *values;
    /*! Number of bands of spectral energy. */
    int32_t num_columns;
    /*! Number of divisions of the time window. */
    int32_t num_rows;
} MLAudioSpectralAnalysis;
/*! \} */

/////////////////////
/// RESULT CODES.
/////////////////////

/*!
  \defgroup DefResultCodes Result Codes
  \ingroup AudioDefs
  \addtogroup DefResultCodes
  \{
*/

enum {
  /*! Defines the prefix for MLAudioResult codes. */
  MLResultAPIPrefix_Audio = MLRESULT_PREFIX(0x9e11)
};

/*!
  \brief Return values for Audio Service API calls.

  \apilevel 4
*/
typedef enum MLAudioResult {
  /*! Function not implemented. */
  MLAudioResult_NotImplemented = MLResultAPIPrefix_Audio,
  /*! Not a valid MLHandle for a sound or input. */
  MLAudioResult_HandleNotFound,
  /*! Sample rate not supported. */
  MLAudioResult_InvalidSampleRate,
  /*! Bits per sample not supported. */
  MLAudioResult_InvalidBitsPerSample,
  /*! Valid bits per sample not supported. */
  MLAudioResult_InvalidValidBits,
  /*! Sample format not supported. */
  MLAudioResult_InvalidSampleFormat,
  /*! Channel count not supported. */
  MLAudioResult_InvalidChannelCount,
  /*! Buffer size too small. */
  MLAudioResult_InvalidBufferSize,
  /*! Buffer not ready for read or write. */
  MLAudioResult_BufferNotReady,
  /*! Specified file not found. */
  MLAudioResult_FileNotFound,
  /*! Specified file has unsupported format. */
  MLAudioResult_FileNotRecognized,
  /*! Specified resource is not on the list. */
  MLAudioResult_ResourceNotFound,
  /*! Data was unloaded or file was closed. */
  MLAudioResult_ResourceDiscarded,
  /*! Requested operation not possible for given item. */
  MLAudioResult_OperationUnavailable,
  /*! Requested operation has not yet been processed. */
  MLAudioResult_OperationNotReady,
  /*! Internal configuration problem was detected. */
  MLAudioResult_InternalConfigError,
  /*! Ensure enum is represented as 32 bits. */
  MLAudioResult_Ensure32Bits = 0x7FFFFFFF
} MLAudioResult;

/*!
  \brief Returns an ASCII string for each result code.

  MLResult and MLAudioResult codes are converted to more detailed descriptions.

  \param[in] result_code MLResult to be converted.

  \return ASCII string containing readable version of result code.
*/
ML_API const char* ML_CALL MLAudioGetResultString(MLResult result_code);
/*! \} */

/////////////////////
///   CALLBACKS.
/////////////////////

/*!
  \defgroup DefCallbacks Callbacks
  \ingroup AudioDefs
  \addtogroup DefCallbacks
  \{
*/

/*!
  \brief Callback to notify when a sound event has occurred.

  \note The callback will be called on a separate thread which is non-blocking, except for calls
  to MLAudioDestroySound which will be blocked until the callback returns (unless the 'Destroy'
  call is called from the same thread as the callback, in which case it won't be blocked).
*/
typedef void (*MLAudioSoundEventCallback)(MLHandle handle, MLAudioSoundEvent event, void *context);

/*!
  \brief Callback to notify when a media event has occurred.
  \note The callback will be called on a separate thread which is non-blocking.
*/
typedef void (*MLAudioMediaEventCallback)(MLAudioMediaEvent event, void *context);

/*!
  \brief Callback to notify when an audio buffer is available for reading or writing.

  \note The callback will be called on a separate thread which is non-blocking, except for calls
  to MLAudioDestroySound and MLAudioDestroyInput (for sounds and inputs respectively) which will
  be blocked until the callback returns (unless the 'Destroy' call is called from the same thread
  as the callback, in which case it won't be blocked).
*/
typedef void (*MLAudioBufferCallback)(MLHandle handle, void *context);

/*!
  \brief Callback to notify when an audio resource's data is being discarded to make room
  for other resource data. Resource data that is not being referenced by a sound will be
  discarded before resource data that is being referenced by a sound. Resources that are
  being played by a sound will not have their data discarded.

  \note The callback will be called on a separate thread which is non-blocking.
*/
typedef void (*MLAudioResourceDiscardedCallback)(MLHandle resource, void *context);

/*!
  \brief Callback to notify when the master volume has been changed.
  \note The callback will be called on a separate thread which is non-blocking.
*/
typedef void (*MLAudioMasterVolumeChangedCallback)(float new_volume, void *context);

/*!
  \brief Callback to notify when the global output mute has been changed.
  \note The callback will be called on a separate thread which is non-blocking.
 */
typedef void (*MLAudioOutputMuteChangedCallback)(bool is_muted, void *context);

/*!
  \brief Callback to notify when the active output device has changed.
  \note The callback will be called on a separate thread which is non-blocking.
 */
typedef void (*MLAudioOutputDeviceChangedCallback)(MLAudioOutputDevice current_device, void *context);

/*!
  \brief Callback to notify when the global mic mute has been changed.
  \note The callback will be called on a separate thread which is non-blocking.
*/
typedef void (*MLAudioMicMuteCallback)(bool is_muted, void *context);

/*!
  \brief Callback to provide a changed value for a running trait analysis.
  \note The callback will be called on a separate thread which is non-blocking.
*/
typedef void (*MLAudioTraitAnalysisCallback)(MLHandle handle, MLAudioTraitAnalysisTarget target, float value, void *context);

/*!
  \brief Callback to provide a changed value set for a running spectral analysis.
  \note The callback will be called on a separate thread which is non-blocking.
*/
typedef void (*MLAudioSpectralAnalysisCallback)(MLHandle handle, MLAudioSpectralAnalysisTarget target, MLAudioSpectralAnalysis values, void *context);
/*! \} */
/*! \} */

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
///                             AUDIO OUTPUT.
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

/*!
  \defgroup AudioOutput Audio Output
  \ingroup Audio
  \addtogroup AudioOutput
  \{
*/

/////////////////////////////
/////////////////////////////
///       RESOURCES.
/////////////////////////////
/////////////////////////////

/*!
  \defgroup OutputResources Resources
  \ingroup AudioOutput
  \addtogroup OutputResources
  \{
*/

/*!
  \brief Creates a new Loaded Resource that references a loaded audio file.

  Loaded Audio Resources provide the ability to preload audio files that stay in memory,
  so a single audio file can be played by multiple sound outputs. The resource can be
  used to create a sound output by passing the resource ID (MLHandle) provided by this
  function via out_resource to MLAudioCreateSoundWithLoadedResource. Files can be of
  type WAV, FLAC, MP3 and OGG, can be stereo or mono, can have 16kHz to 48kHz sample rate,
  and can be represented as 16-bit, 24-bit, and 32-bit integers or 32-bit floats.

  The audio data for a Loaded Resource can be discarded by the system due to memory limits.
  Resources that are not being referenced by a sound output will be discarded prior to
  resources that are being referenced. Resources that are being played by a sound output will
  not be discarded. If a resource has been discarded, it must be refreshed prior to use by
  calling MLAudioRefreshResource. MLAudioResourceDiscardedCallback is an optional argument to
  this function that will result in a callback to inform the client if the audio data for this
  Loaded Resource has been discarded due to system limits.

  \param[in] file File descriptor specifying the audio file.
  \param[in] dynamic_decode Not currently implemented.
  \param[in] callback Callback function pointer.
  \param[in] context Generic data pointer passed back through the callback.
  \param[out] out_resource MLHandle to be used in subsequent calls.

  \retval MLResult_AllocFailed Failed due to memory allocation failure.
  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully created resource.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_FileNotRecognized Failed because file was not recognized.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_InvalidBitsPerSample Failed due to invalid bits per sample.
  \retval MLAudioResult_InvalidChannelCount Failed due to an invalid channel count.
  \retval MLAudioResult_InvalidSampleRate Failed due to an invalid sample rate.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioCreateLoadedResource(int file, bool dynamic_decode, MLAudioResourceDiscardedCallback callback, void *context, MLHandle *out_resource);

/*!
  \brief Creates a new audio resource that references a streamed audio file.

  Streamed Audio Resources provide the ability to pre-establish a persistent reference to
  an audio file (in the form of a file descriptor), so a single audio file can be streamed
  by multiple sound outputs, with audio data streamed from flash memory into main memory in
  chunks during playback. The resource can be used to create a sound output by passing the
  resource ID (MLHandle) provided by this function via out_resource to
  MLAudioCreateSoundWithStreamedResource. Files can be of type WAV, FLAC, MP3 and OGG, can
  be stereo or mono, can have 16kHz to 48kHz sample rate, and can be represented as 16-bit,
  24-bit, and 32-bit integers or 32-bit floats.

  The File Descriptor for a Streamed Resource can be discarded by the system due to a limited
  number of available File Descriptors. Resources that are not being referenced by a sound
  output will be discarded prior to resources that are being referenced. Resources that are
  being played by a sound output will not be discarded. If a resource has been discarded, it
  must be refreshed prior to use by calling MLAudioRefreshResource. MLAudioResourceDiscardedCallback
  is an optional argument to this function that will result in a callback to inform the client
  if the File Descriptor for this Streamed Resource has been discarded due to system limits.

  \param[in] file File descriptor specifying the audio file.
  \param[in] callback Callback function pointer.
  \param[in] context Generic data pointer passed back through the callback.
  \param[out] out_resource MLHandle to be used in subsequent calls.

  \retval MLResult_AllocFailed Failed due to memory allocation failure.
  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully created resource.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioCreateStreamedResource(int file, MLAudioResourceDiscardedCallback callback, void *context, MLHandle *out_resource);

/*!
  \brief Queries whether a Loaded or Streamed Resource has been discarded due to system limits.

  The audio data for a Loaded Resource can be discarded by the system due to memory limits.
  The File Descriptor for a Streamed Resource can be discarded by the system due to a limited
  number of available File Descriptors. Resources that are not being referenced by a sound
  output will be discarded prior to resources that are being referenced. Resources that are
  being played by a sound output will not be discarded. If a resource has been discarded, it
  must be refreshed prior to use by calling MLAudioRefreshResource.

  \param[in] resource MLHandle of the resource.
  \param[out] out_is_ready If true, the resource is ready to use.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully reported the value.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.
  \retval MLAudioResult_ResourceNotFound Failed because resource was not found.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioCheckResource(MLHandle resource, bool *out_is_ready);

/*!
  \brief Queries the size of the memory footprint for a Loaded Resource.

  For Loaded Resources using compressed file formats, the data is decompressed when loaded,
  and the size of the decompressed data is reported. For Streamed Resources, this call will
  fail with MLAudioResult_NotImplemented.

  \apilevel 7

  \param[in] resource MLHandle of the resource.
  \param[out] out_size_in_bytes The retrieved size of the memory footprint.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the value.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_NotImplemented Failed because Streamed Resource was queried.
  \retval MLAudioResult_ResourceNotFound Failed because resource was not found.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetResourceSize(MLHandle resource, uint32_t *out_size_in_bytes);

/*!
  \brief Refreshes a resource whose data was discarded due to system limits.

  The audio data for a Loaded Resource can be discarded by the system due to memory limits.
  The File Descriptor for a Streamed Resource can be discarded by the system due to a limited
  number of available File Descriptors. Resources that are not being referenced by a sound
  output will be discarded prior to resources that are being referenced. Resources that are
  being played by a sound output will not be discarded. If a resource has been discarded, it
  must be refreshed prior to use by calling this function.

  \param[in] resource MLHandle of the resource.
  \param[in] file File descriptor specifying the audio file.

  \retval MLResult_AllocFailed Failed due to memory allocation failure.
  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully refreshed resource.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_FileNotRecognized Failed because file was not recognized.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_InvalidBitsPerSample Failed due to invalid bits per sample.
  \retval MLAudioResult_InvalidBufferSize Failed due to an invalid buffer size.
  \retval MLAudioResult_InvalidChannelCount Failed due to an invalid channel count.
  \retval MLAudioResult_InvalidSampleFormat Failed due to an invalid sample format.
  \retval MLAudioResult_InvalidSampleRate Failed due to an invalid sample rate.
  \retval MLAudioResult_InvalidValidBits Failed due to invalid valid bits.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.
  \retval MLAudioResult_OperationUnavailable Failed because operation is unavailable.
  \retval MLAudioResult_ResourceNotFound Failed because resource was not found.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioRefreshResource(MLHandle resource, int file);

/*!
  \brief Destroys a previously created audio resource.

  Even if a resource is currently in use it will be destroyed immediately. If a sound output
  is playing the resource, the sound will be stopped and a corresponding Sound Event callback
  of type MLAudioSoundEvent_ResourceDestroyed will be issued.

  \param[in] resource MLHandle of the resource.

  \retval MLResult_Ok Successfully destroyed resource.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.
  \retval MLAudioResult_ResourceNotFound Failed because resource was not found.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioDestroyResource(MLHandle resource);

/*!
  \brief Creates a sound output referencing a Loaded Audio Resource.

  Once created, a sound output can be configured and controlled by calling other MLAudio API calls,
  passing the sound ID (MLHandle) provided by this function via out_handle. Playback can be started
  by calling MLAudioStartSound.

  \param[in] resource MLHandle of the Loaded Resource.
  \param[in] auto_destroy If true, the sound output is destroyed when playback reaches end of file.
  \param[out] out_handle MLHandle to be used in subsequent calls.

  \retval MLResult_AllocFailed Failed due to memory allocation failure.
  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully created sound input.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_FileNotRecognized Failed because file was not recognized.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_InvalidBitsPerSample Failed due to invalid bits per sample.
  \retval MLAudioResult_InvalidChannelCount Failed due to an invalid channel count.
  \retval MLAudioResult_InvalidSampleRate Failed due to an invalid sample rate.
  \retval MLAudioResult_ResourceNotFound Failed because resource was not found.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioCreateSoundWithLoadedResource(MLHandle resource, bool auto_destroy, MLHandle *out_handle);

/*!
  \brief Creates a sound output referencing a Streamed Audio Resource.

  Once created, a sound output can be configured and controlled by calling other MLAudio API calls,
  passing the sound ID (MLHandle) provided by this function via out_handle. Playback can be started
  by calling MLAudioStartSound.

  \param[in] resource MLHandle of the streamed audio resource.
  \param[in] auto_destroy If true, the sound output is destroyed when playback reaches end of file.
  \param[out] out_handle MLHandle to be used in subsequent calls.

  \retval MLResult_AllocFailed Failed due to memory allocation failure.
  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully created sound output.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_InvalidBufferSize Failed due to an invalid buffer size.
  \retval MLAudioResult_ResourceDiscarded Failed because file was closed.
  \retval MLAudioResult_ResourceNotFound Failed because resource was not found.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioCreateSoundWithStreamedResource(MLHandle resource, bool auto_destroy, MLHandle *out_handle);
/*! \} */

/////////////////////////////
/////////////////////////////
///       ALLOCATION.
/////////////////////////////
/////////////////////////////

/*!
  \defgroup OutputAllocation Allocation
  \ingroup AudioOutput
  \addtogroup OutputAllocation
  \{
*/

/*!
  \brief Creates a sound output that uses audio data loaded from a file descriptor into memory.

  Once created, the sound output can be configured and controlled by calling other MLAudio API calls,
  passing the sound ID (MLHandle) provided by this function via out_handle. Playback can be started
  by calling MLAudioStartSound. Files can be of type WAV, FLAC, MP3 and OGG, can be stereo or mono,
  can have 16kHz to 48kHz sample rate, and can be represented as 16-bit, 24-bit, and 32-bit integers
  or 32-bit floats.

  \param[in] file File descriptor specifying the audio file.
  \param[in] auto_destroy If true, the sound output is destroyed when playback reaches end of file.
  \param[in] dynamic_decode Not currently implemented.
  \param[out] out_handle MLHandle to be used in subsequent calls.

  \retval MLResult_AllocFailed Failed due to memory allocation failure.
  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully created sound output.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_FileNotRecognized Failed because file was not recognized.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_InvalidBitsPerSample Failed due to invalid bits per sample.
  \retval MLAudioResult_InvalidChannelCount Failed due to an invalid channel count.
  \retval MLAudioResult_InvalidSampleRate Failed due to an invalid sample rate.
  \retval MLAudioResult_InvalidValidBits Failed due to invalid valid bits.
  \retval MLAudioResult_ResourceNotFound Failed because resource was not found.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioCreateSoundWithLoadedFile(int file, bool auto_destroy, bool dynamic_decode, MLHandle *out_handle);

/*!
  \brief Creates a sound output that streams audio data from flash memory via a file descriptor.

  Once created, the sound output can be configured and controlled by calling other MLAudio API calls,
  passing the sound ID (MLHandle) provided by this function via out_handle. Playback can be started
  by calling MLAudioStartSound. Files can be of type WAV, FLAC, MP3 and OGG, can be stereo or mono,
  can have 16kHz to 48kHz sample rate, and can be represented as 16-bit, 24-bit, and 32-bit integers
  or 32-bit floats.

  \param[in] file File descriptor specifying the audio file.
  \param[in] auto_destroy If true, the sound output is destroyed when playback reaches end of file.
  \param[out] out_handle MLHandle to be used in subsequent calls.

  \retval MLResult_AllocFailed Failed due to memory allocation failure.
  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully created sound output.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_FileNotFound Failed because file was missing.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_ResourceDiscarded Failed because file was closed.
  \retval MLAudioResult_ResourceNotFound Failed because resource was not found.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioCreateSoundWithStreamedFile(int file, bool auto_destroy, MLHandle *out_handle);

/*!
  \brief Creates a sound output that plays a client-provided stream of buffered audio data.

  The sound output allocates a double buffer that the caller is responsible for continuously
  filling with audio data. This can be done within a callback of type MLAudioBufferCallback
  that is set via the 'callback' argument or by polling MLAudioGetOutputBuffer if no callback
  is set. When polling, a return value of MLAudioResult_BufferNotReady indicates the sound output
  is not ready and the caller must wait. Setting the 'buffer_size_in_bytes' argument to 0 will
  utilize the system-preferred buffer size. Double-buffers can optionally be pre-filled prior
  to starting the sound. Once created, a sound output can be configured and controlled by calling
  other MLAudio API calls, passing the sound ID (MLHandle) provided by this function via out_handle.
  Playback can be started by calling MLAudioStartSound. Audio data can be mono, stereo, 4-channel
  (ambisonics), 6-channel (5.1), 8-channel (7.1), or 12-channel (7.1.4). It can have 16kHz to 48kHz
  sample rate, and must be 16-bit integer.

  \apilevel 7

  \param[in] format MLAudioBufferFormat struct specifying the format properties.
  \param[in] buffer_size_in_bytes Requested size in bytes for each of the output buffers.
  \param[in] callback Callback function pointer.
  \param[in] context Generic data pointer passed back through the callback.
  \param[out] out_handle MLHandle to be used in subsequent calls.

  \retval MLResult_AllocFailed Failed due to memory allocation failure.
  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully created sound output.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_InvalidSampleRate Failed due to an invalid sample rate.
  \retval MLAudioResult_InvalidBufferSize Failed due to an invalid buffer size.
  \retval MLAudioResult_InvalidChannelCount Failed due to an invalid channel count.
  \retval MLAudioResult_InvalidSampleFormat Failed due to an invalid sample format.
  \retval MLAudioResult_InvalidSampleRate Failed due to an invalid sample rate.
  \retval MLAudioResult_InvalidValidBits Failed due to invalid valid bits.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioCreateSoundWithBufferedOutput(const MLAudioBufferFormat *format, uint32_t buffer_size_in_bytes, MLAudioBufferCallback callback, void *context, MLHandle *out_handle);

/*!
  \brief Destroys a previously created sound output.

  \param[in] handle MLHandle of the sound output.

  \retval MLResult_Ok Successfully destroyed sound output.
  \retval MLResult_UnspecifiedFailure Failed to destroy sound output due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed to destroy sound output due to a missing handle.
  \retval MLAudioResult_NotImplemented Failed to destroy sound output because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioDestroySound(MLHandle handle);
/*! \} */

/////////////////////////////
/////////////////////////////
///        CONTROL.
/////////////////////////////
/////////////////////////////

/*!
  \defgroup OutputControl Control
  \ingroup AudioOutput
  \addtogroup OutputControl
  \{
*/

/*!
  \brief Starts playback for a sound output.

  Calling this function on a playing sound has no effect and returns success. Calling this
  function on a paused sound will start the sound output from the beginning. When starting
  playback for a buffered output stream, the "out_frames_played" counter retrieved by calling
  MLAudioGetBufferedOutputFramesPlayed is reset to 0.

  \param[in] handle MLHandle of the sound output.

  \retval MLResult_Ok Sound output is started, or continues if already playing.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.
  \retval MLAudioResult_ResourceDiscarded Failed because file was closed.
  \retval MLAudioResult_ResourceNotFound Failed because resource was not found.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioStartSound(MLHandle handle);

/*!
  \brief Stops playback for a sound output.

  Calling this function on a stopped sound has no effect and returns success.

  \param[in] handle MLHandle of the sound output.

  \retval MLResult_Ok Sound output is stopped, or remains stopped if already stopped.
  \retval MLResult_UnspecifiedFailure Failed to stop playback due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed to stop playback due to a missing handle.
  \retval MLAudioResult_NotImplemented Failed to stop playback because feature has not been implemented yet.
  \retval MLAudioResult_ResourceNotFound Failed to stop playback because resource was not found.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioStopSound(MLHandle handle);

/*!
  \brief Pauses playback for a currently playing sound output.

  If the sound output is not playing, the pause will fail with MLAudioResult_OperationUnavailable.
  Calling this function on a paused sound has no effect and returns success.

  \param[in] handle MLHandle of the sound output.

  \retval MLResult_Ok Sound output is paused, or remains paused if already paused.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.
  \retval MLAudioResult_OperationUnavailable Failed because operation is unavailable.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioPauseSound(MLHandle handle);

/*!
  \brief Resumes playback for a currently paused sound output.

  Calling this function on a paused sound will resume playback from the current position. Calling
  this function on a playing or stopped sound will fail with MLAudioResult_OperationUnavailable.

  \param[in] handle MLHandle of the sound output.

  \retval MLResult_Ok Sound output resumes playing.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.
  \retval MLAudioResult_OperationUnavailable Failed because operation is unavailable.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioResumeSound(MLHandle handle);

/*!
  \brief Queries the playback state of a sound output.

  The MLAudioState enum defines the possible playback states which are Stopped, Playing and Paused.

  \param[in] handle MLHandle of the sound output.
  \param[out] out_state MLAudioState enum to be filled with the current playback state.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the properties.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetSoundState(MLHandle handle, MLAudioState *out_state);

/*!
  \brief Queries the audio format of a sound output.

  For sound outputs referencing streamed resources, the format is not available until ~100
  milliseconds after playback has started.

  \param[in] handle MLHandle of the sound output.
  \param[out] out_format MLAudioBufferFormat struct to be filled with the format properties.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the properties.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.
  \retval MLAudioResult_OperationUnavailable Failed because operation is unavailable.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetSoundFormat(MLHandle handle, MLAudioBufferFormat *out_format);

/*!
  \brief Registers a callback for Sound Events relating to a sound output.

  Sound outputs generate events as specified in the MLAudioSoundEvent enum, such as when a sound
  has looped, stopped, etc. Each of these events will trigger the MLAudioSoundEventCallback.

  \apilevel 20

  \param[in] handle MLHandle of the sound output.
  \param[in] callback Callback function pointer.
  \param[in] context Generic data pointer passed back through the callback.

  \retval MLResult_AllocFailed Failed due to memory allocation failure.
  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully registered the callback.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetSoundEventCallback(MLHandle handle, MLAudioSoundEventCallback callback, void *context);

/*!
  \brief Registers a callback for media transport events.

  Media transport events can be triggered by devices such as bluetooth media controls. The
  possible events include Stop, Start, Pause, NextTrack and PrevTrack as specified in the
  MLAudioMediaEvent enum.

  \apilevel 20

  \param[in] callback Callback function pointer.
  \param[in] context Generic data pointer passed back through the callback.

  \retval MLResult_AllocFailed If memory allocation fails.
  \retval MLResult_InvalidParam If input parameter is invalid.
  \retval MLResult_Ok Successfully registered the callback.
  \retval MLResult_UnspecifiedFailure Internal error.
  \retval MLAudioResult_HandleNotFound Handle not found.
  \retval MLAudioResult_InternalConfigError Internal config error.
  \retval MLAudioResult_NotImplemented Internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetMediaEventCallback(MLAudioMediaEventCallback callback, void *context);

/*! \} */

/////////////////////////////
/////////////////////////////
///     PARAMETERS.
/////////////////////////////
/////////////////////////////

/*!
  \defgroup OutputParameters Parameters
  \ingroup AudioOutput
  \addtogroup OutputParameters
  \{
*/

/*!
  \brief Sets the volume of a sound output using a linear scale.

  The range of valid values is from 0 to 8. A value of 0 indicates silence. A value of 1
  indicates unity gain. A maximum value of 8 indicates 8x unity gain (+18 dB).

  \param[in] handle MLHandle of the sound output.
  \param[in] volume The linear volume that the sound output will be set to.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully set the value.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetSoundVolumeLinear(MLHandle handle, float volume);

/*!
  \brief Queries the volume of a sound output in a linear scale.

  The range of valid values is from 0 to 8. A value of 0 indicates silence. A value of 1
  indicates unity gain. A maximum value of 8 indicates 8x unity gain (+18 dB).

  \param[in] handle MLHandle of the sound output.
  \param[out] out_volume Retrieved linear volume of the sound output.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the value.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetSoundVolumeLinear(MLHandle handle, float *out_volume);

/*!
  \brief Sets the volume of a sound output using a decibel scale.

  The range of valid values is from -100 dB to +18 dB. A value of -100 dB indicates silence.
  A value of 0 dB indicates unity gain. A maximum value of 18 dB indicates 8x unity gain.

  \param[in] handle MLHandle of the sound output.
  \param[in] volume The dB volume that the sound output will be set to.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully set the value.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetSoundVolumeDb(MLHandle handle, float volume);

/*!
  \brief Queries the volume of a sound output using a decibel scale.

  The range of valid values is from -100 dB to +18 dB. A value of -100 dB indicates silence.
  A value of 0 dB indicates unity gain. A maximum value of 18 dB indicates 8x unity gain.

  \param[in] handle MLHandle of the sound output.
  \param[out] out_volume Retrieved dB volume of the sound output.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the value.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetSoundVolumeDb(MLHandle handle, float *out_volume);

/*!
  \brief Sets the pitch of a sound output by modifying its playback speed.

  The range of valid values is from 0.5 which plays at half speed and produces an octave
  shift down, to 2.0 which plays at double speed and produces an octave shift up. The
  default value of 1.0 plays the sound at its original speed and pitch.

  \param[in] handle MLHandle of the sound output.
  \param[in] pitch The pitch of the sound output to be set.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully set the value.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_InvalidBufferSize Failed due to an invalid buffer size.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetSoundPitch(MLHandle handle, float pitch);

/*!
  \brief Queries the pitch of a sound output which corresponds to its playback speed.

  The range of valid values is from 0.5 which plays at half speed and produces an octave
  shift down, to 2.0 which plays at double speed and produces an octave shift up. At the
  default value of 1.0 the sound plays at its original speed and pitch.

  \param[in] handle MLHandle of the sound output.
  \param[out] out_pitch Retrieved pitch of the sound output.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the value.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetSoundPitch(MLHandle handle, float *out_pitch);

/*!
  \brief Sets the mute state of a sound output.

  The 'sound mute' of a sound output only affects that one sound output.

  \param[in] handle MLHandle of the sound output.
  \param[in] is_muted If true, the sound output will be muted.

  \retval MLResult_Ok Successfully set the value.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetSoundMute(MLHandle handle, bool is_muted);

/*!
  \brief Queries the mute state of a sound output.

  The 'sound mute' of a sound output only affects that one sound output.

  \apilevel 20

  \param[in] handle MLHandle of the sound output.
  \param[out] out_is_muted If true, the sound output is muted.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the value.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetSoundMute(MLHandle handle, bool *out_is_muted);

/*!
  \brief Sets whether a sound output is exempt from attenuation due to master volume.

  This call sets whether a sound output is bypassing master volume, making it effectively
  "always audible" (assuming it is neither muted nor set to zero volume on a per-sound basis).
  This option is available only on certain SKUs; trying to set it when the device is not
  compatible will produce an error as listed below. In addition, this option only works
  when a sound is non-spatial; the non-spatial sound parameters volume, pitch, etc remain
  active for sounds that are bypassing master volume.

  \apilevel 20

  \param[in] handle MLHandle of the sound output.
  \param[in] is_bypassing Indicates whether the sound output should bypass master volume or not.

  \retval MLResult_Ok Successfully set the value.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLResult_IncompatibleSKU Failed due to feature not being supported on current device version.

  \permissions None
*/

ML_API MLResult ML_CALL MLAudioSetSoundBypassesMasterVolume(MLHandle handle, bool is_bypassing);

/*!
  \brief Queries whether a sound output is exempt from attenuation due to master volume.

  This call queries whether a sound output is bypassing master volume, making it effectively
  "always audible" (assuming it is neither muted nor set to zero volume on a per-sound basis).
  This option is available only on certain SKUs; trying to query it when the device is not
  compatible will produce an error as listed below. In addition, this option only works when
  a sound is non-spatial; the non-spatial sound parameters volume, pitch, etc remain active
  for sounds that are bypassing master volume.

  \apilevel 20

  \param[in] handle MLHandle of the sound output.
  \param[out] out_is_bypassing Indicates whether the sound output is bypassing master volume or not.

  \retval MLResult_Ok Successfully queried the bypassing state of the sound output.
  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLResult_IncompatibleSKU Failed due to feature not being supported on current device version.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetSoundBypassesMasterVolume(MLHandle handle, bool *out_is_bypassing);

/*!
  \brief Sets whether a sound output is looping or not.

  Looping is available for sound outputs that use Loaded Files and Streamed Files (and their
  audio resource equivalents). If a sound output is set to looping, then when it reaches the
  end of the file, it continues playing from the beginning of the file. Looping is not available
  for sound outputs that use Buffered Outputs.

  \param[in] handle MLHandle of the sound output.
  \param[in] is_looping Determines whether the sound output is looping or not.

  \retval MLResult_Ok Successfully set looping of audio.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/

ML_API MLResult ML_CALL MLAudioSetSoundLooping(MLHandle handle, bool is_looping);

/*!
  \brief Queries whether a sound output is looping or not.

  Looping is available for sound outputs that use Loaded Files and Streamed Files (and their
  audio resource equivalents). If a sound output is set to looping, then when it reaches the
  end of the file, it continues playing from the beginning of the file. Looping is not available
  for sound outputs that use Buffered Outputs.

  \param[in] handle MLHandle of the sound output.
  \param[out] out_is_looping If true, the sound output state is looping.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the value.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetSoundLooping(MLHandle handle, bool *out_is_looping);

/*!
  \brief Sets the playback position of a sound output that's playing a Streamed File.

  The playback position is in milliseconds and can be set regardless of the playback state.

  \param[in] handle MLHandle of the sound output.
  \param[in] offset_in_msec The playback position in milliseconds the sound output will be set to.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully set the value.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.
  \retval MLAudioResult_OperationUnavailable Failed because operation is unavailable.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetStreamedFileOffset(MLHandle handle, uint32_t offset_in_msec);

/*!
  \brief Queries the playback position of a sound output that's playing a Streamed File.

  The playback position is in milliseconds.

  \param[in] handle MLHandle of the sound output.
  \param[out] out_offset_in_msec Retrieved playback position.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the value.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.
  \retval MLAudioResult_OperationUnavailable Failed because operation is unavailable.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetStreamedFileOffset(MLHandle handle, uint32_t *out_offset_in_msec);

/*!
  \brief Queries which type of sound output device is being used for sound output.

  This is a global configuration that is not specific to individual sound outputs.

  \param[out] out_current_device Enum indicating what kind of audio output device is currently in use.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully indicated the type of output device.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetOutputDevice(MLAudioOutputDevice *out_current_device);

/*!
  \brief Registers a callback for when the active audio hardware output has changed.

  \apilevel 8

  \param[in] callback Callback function pointer.
  \param[in] context Generic data pointer passed back through the callback.

  \retval MLResult_AllocFailed Failed due to memory allocation failure.
  \retval MLResult_Ok Successfully registered the callback.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetOutputDeviceCallback(MLAudioOutputDeviceChangedCallback callback, void *context);
/*!\} */

/////////////////////////////
/////////////////////////////
///     ACOUSTICS.
/////////////////////////////
/////////////////////////////

/*!
  \defgroup OutputAcoustics Acoustics
  \ingroup AudioOutput
  \addtogroup OutputAcoustics
  \{
*/

/*!
  \brief Resets the Acoustic Scene.

  Each client of this audio API is automatically assigned an Acoustic Scene that specifies
  the acoustic behaviors of that client's spatial audio content. An Acoustic Scene can be
  modified and customized by calling functions in the ACOUSTICS section of this audio API.
  This function resets the caller's Acoustic Scene to its initial default state.

  \apilevel 20

  \retval MLResult_Ok Successfully reset the Acoustic Scene.
  \retval MLResult_UnspecifiedFailure Internal error.
  \retval MLAudioResult_HandleNotFound No custom scene exists for client.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioResetAcousticScene();

/*!
  \brief Pauses the processing of changes to the Acoustic Scene.

  This function signals the beginning of a collection of changes to the Acoustic Scene,
  intended to be heard at the same time. After calling MLAudioBeginAcousticSceneUpdate,
  any subsequent calls to functions in the ACOUSTICS section of this audio API will be
  deferred, and will be applied simultaneously when MLAudioEndAcousticSceneUpdate is called.

  \apilevel 20

  \retval MLResult_Ok Successfully began the Acoustic Scene update.
  \retval MLResult_UnspecifiedFailure Internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioBeginAcousticSceneUpdate();

/*!
  \brief Resumes the processing of changes to the Acoustic Scene.

  This function signals the ending of a collection of changes to the Acoustic Scene,
  causing them to be heard at the same time. After calling MLAudioBeginAcousticSceneUpdate,
  any subsequent calls to functions in the ACOUSTICS section of this audio API will be
  deferred, and will be applied simultaneously when MLAudioEndAcousticSceneUpdate is called.

  \apilevel 20

  \retval MLResult_Ok Successfully ended the Acoustic Scene update.
  \retval MLResult_UnspecifiedFailure Internal error.
  \retval MLAudioResult_HandleNotFound No custom scene exists for client.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioEndAcousticSceneUpdate();

/*!
  \brief Sets whether spatial rendering emulates the acoustics of the user's environment.

  The Acoustic Map is a device-curated representation of the acoustics of the local physical
  environment. Enabling the Acoustic Map makes virtual objects sound as though they exist
  in the local physical environment.

  \apilevel 20

  \param[in] is_enabled If true, the Acoustic Map will be enabled.

  \retval MLResult_Ok Successfully set the value.
  \retval MLResult_UnspecifiedFailure Internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetAcousticSceneMapEnable(bool is_enabled);

/*!
  \brief Queries whether spatial rendering emulates the acoustics of the user's environment.

  The Acoustic Map is a device-curated representation of the acoustics of the local physical
  environment. When the Acoustic Map is enabled, virtual objects sound as though they exist
  in the local physical environment.

  \apilevel 20

  \param[out] out_is_enabled If true, the Acoustic Map is enabled.

  \retval MLResult_Ok Successfully retrieved the value.
  \retval MLResult_InvalidParam If input parameter is invalid.
  \retval MLResult_UnspecifiedFailure Internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetAcousticSceneMapEnable(bool *out_is_enabled);

/*!
  \brief Sets the default attenuation applied to obstructed spatial sounds.

  The propagation of virtual sound in space can be obstructed by virtual objects created
  by the client, or by the virtual representation of the local physical environment. In
  cases where these obstructions have no transmission properties defined, the Acoustic
  Scene default transmission properties set by this function are used. Transmission
  properties are specified by an MLAudioMultibandLevel struct in which values of
  [1, (1, 1, 1)] represent fully unobstructed, while [0, (1, 1, 1)] or [1, (0, 0, 0)]
  both represent fully obstructed.

  \apilevel 20

  \param[in] transmission MLAudioMultibandLevel struct to set the default properties.

  \retval MLResult_Ok Successfully set the default properties.
  \retval MLResult_InvalidParam If input parameter is invalid.
  \retval MLResult_UnspecifiedFailure Internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetAcousticSceneTransmissionDefault(const MLAudioMultibandLevel *transmission);

/*!
  \brief Queries the default attenuation applied to obstructed spatial sounds.

  The propagation of virtual sound in space can be obstructed by virtual objects created
  by the client, or by the virtual representation of the local physical environment. In
  cases where these obstructions have no transmission properties defined, the Acoustic
  Scene default transmission properties queried by this function are used. Transmission
  properties are specified by an MLAudioMultibandLevel struct in which values of
  [1, (1, 1, 1)] represent fully unobstructed, while [0, (1, 1, 1)] or [1, (0, 0, 0)]
  both represent fully obstructed.

  \apilevel 20

  \param[out] out_transmission MLAudioMultibandLevel struct to be filled with the default properties.

  \retval MLResult_Ok Successfully retrieved the default properties.
  \retval MLResult_InvalidParam If input parameter is invalid.
  \retval MLResult_UnspecifiedFailure Internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetAcousticSceneTransmissionDefault(MLAudioMultibandLevel *out_transmission);

/*!
  \brief Sets the default dispersion properties, which control the rendering of clustered reflections.

  The propagation model for a spatial sound has 4 parts: direct path, reflections, dispersion,
  and reverb. Dispersion comprises the clustered non-discrete reflections that precede the reverb.
  In areas where no dispersion properties are explicitly defined, the Acoustic Scene default
  dispersion properties set by this function are used. Dispersion properties are specified by an
  MLAudioDispersionProperties struct which specifies a gain using an MLAudioMultibandLevel, and a
  pre-delay. If the pre-delay setting is greater than the pre-delay of the default reverb properties,
  it will be clamped to an equal value.

  This 'AcousticScene' API sets a shared acoustic processing effect that is applied to multiple spatial
  sounds. To set the per-sound mix levels for this effect, see the corresponding 'SpatialSoundSendLevel'
  API which is MLAudioSetSpatialSoundDispersionSendLevel.

  \apilevel 20

  \param[in] properties MLAudioDispersionProperties struct to set the default properties.

  \retval MLResult_Ok Successfully set the default properties.
  \retval MLResult_InvalidParam If input parameter is invalid.
  \retval MLResult_UnspecifiedFailure Internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetAcousticSceneDispersionDefault(const MLAudioDispersionProperties *properties);

/*!
  \brief Queries the default dispersion properties, which control the rendering of clustered reflections.

  The propagation model for a spatial sound has 4 parts: direct path, reflections, dispersion,
  and reverb. Dispersion comprises the clustered non-discrete reflections that precede the reverb.
  In areas where no dispersion properties are explicitly defined, the Acoustic Scene default
  dispersion properties queried by this function are used. Dispersion properties are specified by an
  MLAudioDispersionProperties struct which specifies a gain using an MLAudioMultibandLevel, and a
  pre-delay.

  This 'AcousticScene' API queries a shared acoustic processing effect that is applied to multiple spatial
  sounds. To query the per-sound mix levels for this effect, see the corresponding 'SpatialSoundSendLevel'
  API which is MLAudioGetSpatialSoundDispersionSendLevel.

  \apilevel 20

  \param[out] out_properties MLAudioDispersionProperties struct to be filled with the default properties.

  \retval MLResult_Ok Successfully retrieved the default properties.
  \retval MLResult_InvalidParam If input parameter is invalid.
  \retval MLResult_UnspecifiedFailure Internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetAcousticSceneDispersionDefault(MLAudioDispersionProperties *out_properties);

/*!
  \brief Sets the default reverb properties, which control the rendering of late reverberation.

  The propagation model for a spatial sound has 4 parts: direct path, reflections, dispersion, and reverb.
  The reverb comprises late stage sound decay caused by the acoustic space. In areas where no reverb
  properties are explicitly defined, the Acoustic Scene default reverb properties set by this function
  are used. Reverb properties are specified by an MLAudioReverbProperties struct which specifies a gain
  using an MLAudioMultibandLevel, a pre-delay, and the time and frequency contour of the reverb envelope.
  If the pre-delay setting is less than the pre-delay of the default dispersion properties, it will
  be clamped to an equal value.

  This 'AcousticScene' API sets a shared acoustic processing effect that is applied to multiple spatial
  sounds. To set the per-sound mix levels for this effect, see the corresponding 'SpatialSoundSendLevel'
  API which is MLAudioSetSpatialSoundReverbSendLevel.

  \apilevel 20

  \param[in] properties MLAudioReverbProperties struct to set the properties.

  \retval MLResult_Ok Successfully set the default properties.
  \retval MLResult_InvalidParam If input parameter is invalid.
  \retval MLResult_UnspecifiedFailure Internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetAcousticSceneReverbDefault(const MLAudioReverbProperties *properties);

/*!
  \brief Queries the default reverb properties, which control the rendering of late reverberation.

  The propagation model for a spatial sound has 4 parts: direct path, reflections, dispersion, and reverb.
  The reverb comprises late stage sound decay caused by the acoustic space. In areas where no reverb
  properties are explicitly defined, the Acoustic Scene default reverb properties queried by this function
  are used. Reverb properties are specified by an MLAudioReverbProperties struct which specifies a gain using an
  MLAudioMultibandLevel, a pre-delay, and the time and frequency contour of the reverb envelope.

  This 'AcousticScene' API queries a shared acoustic processing effect that is applied to multiple spatial
  sounds. To query the per-sound mix levels for this effect, see the corresponding 'SpatialSoundSendLevel'
  API which is MLAudioGetSpatialSoundReverbSendLevel.

  \apilevel 20

  \param[out] out_properties MLAudioReverbProperties struct to be filled with the default properties.

  \retval MLResult_Ok Successfully retrieved the default properties.
  \retval MLResult_InvalidParam If input parameter is invalid.
  \retval MLResult_UnspecifiedFailure Internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetAcousticSceneReverbDefault(MLAudioReverbProperties *out_properties);

/*!
  \brief INTERNAL USE ONLY: Retrieves the Acoustic Map if it has been updated since the previous call.

  Acoustic Map data is a device-curated representation of the acoustics of the local physical environment.
  The out_map_data argument will point to a serialized copy of the map and must deleted after use.
  This function is intended for internal use and should not be called by clients of the MLAudio API.

  \apilevel 20

  \param[in] prev_map_tag The map tag received in previous call.
  \param[out] out_map_data Retrieved pointer to serialized copy of Acoustic Map data if prev_map_tag != out_map_tag.
  \param[out] out_map_size_in_bytes Retrieved length of serialized Acoustic Map data in bytes.
  \param[out] out_map_tag Retrieved current map tag to be passed in subsequent call.

  \retval MLResult_Ok Successfully retrieved properties.
  \retval MLResult_InvalidParam If input parameter is invalid.
  \retval MLResult_UnspecifiedFailure Internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetChangedAcousticMap(uint32_t prev_map_tag, uint8_t **out_map_data, uint32_t *out_map_size_in_bytes, uint32_t *out_map_tag);

/////////////////////////////
/////////////////////////////
///     SPATIAL SOUND.
/////////////////////////////
/////////////////////////////

/*!
  \defgroup OutputSpatialSound Spatial Sound
  \ingroup AudioOutput
  \addtogroup OutputSpatialSound
  \{
*/

/*!
  \brief Sets whether a sound output is enabled as a spatial sound.

  Enabling a sound output as a spatial sound will cause each of its channels to be rendered
  at a per-channel-specified position in 3D space. Spatial sounds also have other customizable
  per-channel properties such as direction, radiation, distance attenuation, etc. All these
  properties can be set whether or not a sound output is currently enabled as a spatial sound.
  Simulated acoustics for spatial sounds are defined by the client's Acoustic Scene. By default,
  sound outputs are not enabled as spatial sounds.

  \param[in] handle MLHandle of the sound output.
  \param[in] is_enabled If true, spatial audio will be enabled for a sound output.

  \retval MLResult_Ok Successfully set the value.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetSpatialSoundEnable(MLHandle handle, bool is_enabled);

/*!
  \brief Queries whether a sound output is enabled as a spatial sound.

  For a sound output enabled as a spatial sound, each of its channels will be rendered at
  a per-channel-specified position in 3D space. Spatial sounds also have other customizable
  per-channel properties such as direction, radiation, distance attenuation, etc. All these
  properties can be queried whether or not a sound output is currently enabled as a spatial sound.
  Simulated acoustics for spatial sounds are defined by the client's Acoustic Scene. By default,
  sound outputs are not enabled as spatial sounds.

  \param[in] handle MLHandle of the sound output.
  \param[out] out_is_enabled If true, spatial audio is be enabled for a sound output.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the value.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetSpatialSoundEnable(MLHandle handle, bool *out_is_enabled);

/*!
  \brief Sets the 3D position for one channel of a spatial sound.

  Each channel of a spatial sound is rendered at a position specified by an x,y,z point in
  cartesian coordinates. Positive x is to the right, positive y is up, and positive z is
  to the rear.

  Spatial sounds require each channel's parameters to be set individually. Channels are
  indexed starting at 0 and follow the track order defined by the audio content. For example,
  for a spatial sound with stereo content this function should be called twice, passing
  channel = 0 for left and channel = 1 for right. A sound output must be enabled as a spatial
  sound using MLAudioSetSpatialSoundEnable for this property to take effect.

  \param[in] handle MLHandle of the sound output.
  \param[in] channel Channel of the sound output.
  \param[in] position Struct to set the position.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully set the properties.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetSpatialSoundPosition(MLHandle handle, uint32_t channel, const MLVec3f *position);

/*!
  \brief Queries the 3D position of one channel of a spatial sound.

  Each channel of a spatial sound is rendered at a position specified by an x,y,z point in
  cartesian coordinates. Positive x is to the right, positive y is up, and positive z is
  to the rear.

  Spatial sounds require each channel's parameters to be queried individually. Channels are
  indexed starting at 0 and follow the track order defined by the audio content. For example,
  for a spatial sound with stereo content this function should be called twice, passing
  channel = 0 for left and channel = 1 for right. A sound output must be enabled as a spatial
  sound using MLAudioSetSpatialSoundEnable for this property to take effect.

  \param[in] handle MLHandle of the sound output.
  \param[in] channel Channel of the sound output.
  \param[out] out_position Struct to be filled with the position.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the properties.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetSpatialSoundPosition(MLHandle handle, uint32_t channel, MLVec3f *out_position);

/*!
  \brief Sets the 3D direction for one channel of a spatial sound.

  Each channel of a spatial sound radiates into 3D space with a pattern whose center is
  specified by the sound channel's direction. The radiation pattern can be set by calling
  MLAudioSetSpatialSoundRadiation. By default, sounds have billboarding enabled, which
  overrides the direction for every channel such that they always face the listener.
  Billboarding can be disabled by calling MLAudioSetSpatialSoundBillboarding.

  Spatial sounds require each channel's parameters to be set individually. Channels are
  indexed starting at 0 and follow the track order defined by the audio content. For example,
  for a spatial sound with stereo content this function should be called twice, passing
  channel = 0 for left and channel = 1 for right. A sound output must be enabled as a spatial
  sound using MLAudioSetSpatialSoundEnable for this property to take effect.

  \param[in] handle MLHandle of the sound output.
  \param[in] channel Channel of the sound output.
  \param[in] direction Struct to set the radiation direction.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully set the properties.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed to set radiation direction due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetSpatialSoundDirection(MLHandle handle, uint32_t channel, const MLQuaternionf *direction);

/*!
  \brief Queries the 3D direction of one channel of a spatial sound.

  Each channel of a spatial sound radiates into 3D space with a pattern whose center is
  specified by the sound channel's direction. The radiation pattern can be set by calling
  MLAudioSetSpatialSoundRadiation. By default, sounds have billboarding enabled, which
  overrides the direction for every channel such that they always face the listener.
  Billboarding can be disabled by calling MLAudioSetSpatialSoundBillboarding.

  Spatial sounds require each channel's parameters to be queried individually. Channels are
  indexed starting at 0 and follow the track order defined by the audio content. For example,
  for a spatial sound with stereo content this function should be called twice, passing
  channel = 0 for left and channel = 1 for right. A sound output must be enabled as a spatial
  sound using MLAudioSetSpatialSoundEnable for this property to take effect.

  \param[in] handle MLHandle of the sound output.
  \param[in] channel Channel of the sound output.
  \param[out] out_direction Struct to be filled with the radiation direction.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the properties.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetSpatialSoundDirection(MLHandle handle, uint32_t channel, MLQuaternionf *out_direction);

/*!
  \brief Enables or disables billboarding for all channels of a spatial sound.

  Billboarding causes each channel of a spatial sound to always face the listener. When
  billboarding is enabled, channel directions set using MLAudioSetSpatialSoundDirection
  are ignored. Billboarding gives the impression of an omnidirectional sound, while
  allowing radiation properties set using MLAudioSetSpatialSoundRadiation to affect this
  sound's contribution to dispersion and reverb. By default, billboarding is enabled on
  newly created sound outputs.

  \apilevel 20

  \param[in] handle MLHandle of the sound output.
  \param[in] is_billboarding If true, billboarding will be enabled.

  \retval MLResult_OK Successfully set the value.
  \retval MLAudioResult_HandleNotFound Unable to find resource handle.
  \retval MLAudioResult_OperationUnavailable Operation is unavailable for this sound output.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetSpatialSoundBillboarding(MLHandle handle, bool is_billboarding);

/*!
  \brief Queries whether billboarding is enabled for a spatial sound.

  Billboarding causes each channel of a spatial sound to always face the listener. When
  billboarding is enabled, channel directions set using MLAudioSetSpatialSoundDirection
  are ignored. Billboarding gives the impression of an omnidirectional sound, while
  allowing radiation properties set using MLAudioSetSpatialSoundRadiation to affect this
  sound's contribution to dispersion and reverb. By default, billboarding is enabled on
  newly created sound outputs.

  \apilevel 20

  \param[in] handle MLHandle of the sound output.
  \param[out] out_is_billboarding If true, billboarding is enabled.

  \retval MLResult_OK Successfully retrieved the value.
  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_OperationUnavailable Operation is unavailable for this sound output.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetSpatialSoundBillboarding(MLHandle handle, bool *out_is_billboarding);

/*!
  \brief Sets the direct path obstruction status for one channel of a spatial sound.

  THIS IS AN INTERNAL FUNCTION INTENDED FOR ENGINE DEVELOPMENT ONLY.

  Spatial sounds are subject to obstruction effects by real and virtual objects. Each
  channel of the spatial sound output contains a left and right ear MLAudioObstruction
  for the direct path, which can be set by repeated calls to this function. The obstruction
  effect for each channel of a spatial sound is determined by this set of MLAudioObstruction
  structs and a set of transmission properties. The MLAudioObstruction hit_point determines
  which transmission properties to apply and the MLAudioObstruction factor determines the
  extent to which these properties are applied. Transmission properties can be set globally
  for the scene using MLAudioSetAcousticSceneTransmissionDefault.

  Spatial sounds require each channel's parameters to be set individually. Channels are
  indexed starting at 0 and follow the track order defined by the audio content. For example,
  for a spatial sound with stereo content this function should be called twice, passing
  channel = 0 for left and channel = 1 for right. A sound output must be enabled as a spatial
  sound using MLAudioSetSpatialSoundEnable for this property to take effect.

  \apilevel 20

  \param[in] handle MLHandle of the sound output.
  \param[in] channel Channel of the sound output.
  \param[in] left_ear MLAudioObstruction struct to set the direct path obstruction properties for the left ear.
  \param[in] right_ear MLAudioObstruction struct to set the direct path obstruction properties for the right ear.

  \retval MLResult_Ok Successfully set the properties.
  \retval MLResult_InvalidParam If input parameter is invalid.
  \retval MLAudioResult_HandleNotFound Handle not found.
  \retval MLAudioResult_OperationUnavailable Operation is unavailable for this sound output.
  \retval MLResult_UnspecifiedFailure Internal error.
  \retval MLAudioResult_InternalConfigError Internal configuration error.
  \retval MLAudioResult_NotImplemented Internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetSpatialSoundObstruction(MLHandle handle, uint32_t channel, const MLAudioObstruction *left_ear, const MLAudioObstruction *right_ear);

/*!
  \brief Queries the direct path obstruction status for one channel of a spatial sound.

  THIS IS AN INTERNAL FUNCTION INTENDED FOR ENGINE DEVELOPMENT ONLY.

  Spatial sounds are subject to obstruction effects by real and virtual objects. Each
  channel of the spatial sound output contains a left and right ear MLAudioObstruction
  for the direct path, which can be queried by this function. The obstruction effect for
  each channel of a spatial sound is determined by this set of MLAudioObstruction structs
  and a set of transmission properties. The MLAudioObstruction hit_point determines which
  transmission properties to apply and the MLAudioObstruction factor determines the extent
  to which these properties are applied. Transmission properties can be set globally for
  the scene using MLAudioSetAcousticSceneTransmissionDefault.

  Spatial sounds require each channel's parameters to be queried individually. Channels are
  indexed starting at 0 and follow the track order defined by the audio content. For example,
  for a spatial sound with stereo content this function should be called twice, passing
  channel = 0 for left and channel = 1 for right. A sound output must be enabled as a spatial
  sound using MLAudioSetSpatialSoundEnable for this property to take effect.

  \apilevel 20

  \param[in] handle MLHandle of the sound output.
  \param[in] channel Channel of the sound output.
  \param[out] out_left_ear MLAudioObstruction struct to be filled with the obstruction properties for the left ear.
  \param[out] out_right_ear MLAudioObstruction struct to be filled with the obstruction properties for the right ear.

  \retval MLResult_Ok Successfully retrieved the properties.
  \retval MLResult_InvalidParam If input parameter is invalid.
  \retval MLAudioResult_HandleNotFound Handle not found.
  \retval MLAudioResult_OperationUnavailable Operation is unavailable for this sound output.
  \retval MLResult_UnspecifiedFailure Internal error.
  \retval MLAudioResult_InternalConfigError Internal config error.
  \retval MLAudioResult_NotImplemented Internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetSpatialSoundObstruction(MLHandle handle, uint32_t channel, MLAudioObstruction *out_left_ear, MLAudioObstruction *out_right_ear);

/*!
  \brief Sets the extent to which a spatial sound is exempt from obstruction effects.

  This function provides a way to prevent obstruction effects on specified spatial sounds. The
  extent to which a spatial sound is exempt from obstruction effects is specified per band using
  an MLAudioMultibandLevel struct. The value for each band determines that band's interpolation
  between its computed obstruction effect, represented by 0, and no obstruction effect, represented
  by 1. For example, to completely exempt a spatial sound from obstruction effects, set the override
  argument to [1,1,1,1], and to fully allow obstruction effects set to [0,0,0,0]. On newly created
  spatial sounds, obstruction override defaults to [0,0,0,0]. For multi-channel spatial sounds, all
  channels are affected equally by this function.

  \apilevel 20

  \param[in] handle MLHandle of the sound output.
  \param[in] override MLAudioMultibandLevel struct to set the override properties.

  \retval MLResult_OK Successfully set the properties.
  \retval MLResult_InvalidParam If input parameter is invalid.
  \retval MLAudioResult_HandleNotFound Unable to find resource handle.
  \retval MLAudioResult_OperationUnavailable Operation is unavailable for this sound output.
  \retval MLResult_UnspecifiedFailure Internal error.
  \retval MLAudioResult_InternalConfigError Internal config error.
  \retval MLAudioResult_NotImplemented Internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetSpatialSoundObstructionOverride(MLHandle handle, const MLAudioMultibandLevel *override);

/*!
  \brief Queries the extent to which a spatial sound is exempt from obstruction effects.

  Obstruction override provides a way to prevent obstruction effects on specified spatial sounds.
  The extent to which a spatial sound is exempt from obstruction effects is specified per band using
  an MLAudioMultibandLevel struct. The value for each band determines that band's interpolation
  between its computed obstruction effect, represented by 0, and no obstruction effect, represented
  by 1. For example, a spatial sound completely exempt from obstruction effects has an override value
  of [1,1,1,1], and a spatial sound fully subject to obstruction effects has an override value of
  [0,0,0,0]. For multi-channel spatial sounds, all channels are affected equally by the override value.

  \apilevel 20

  \param[in] handle MLHandle of the sound output.
  \param[out] out_override MLAudioMultibandLevel struct to be filled with the override properties.

  \retval MLResult_OK Successfully retrieved the properties.
  \retval MLResult_InvalidParam If input parameter is invalid.
  \retval MLAudioResult_HandleNotFound Unable to find resource handle.
  \retval MLAudioResult_OperationUnavailable Operation is unavailable for this sound output.
  \retval MLResult_UnspecifiedFailure Internal error.
  \retval MLAudioResult_InternalConfigError Internal config error.
  \retval MLAudioResult_NotImplemented Internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetSpatialSoundObstructionOverride(MLHandle handle, MLAudioMultibandLevel *out_override);

/*!
  \brief Sets the behavior by which a spatial sound is attenuated due to distance.

  The behavior for distance attenuation is specified by an MLAudioSpatialSoundDistanceProperties
  struct provided as the properties argument of this function. Within this struct the min_distance
  specifies the distance from the listener beyond which a spatial sound starts attenuating with
  distance. The max_distance specifies the distance from the listener beyond which no further
  attenuation occurs. Between min_distance and max_distance a spatial sound will be attenuated with
  distance according to the rolloff_factor. A rolloff_factor of 1 will produce distance attenuation
  that approximates real world distance attenuation. A rolloff_factor greater than 1 will produce
  distance attenuation that rolls off faster as distance increases, while less than 1 will produce
  distance attenuation that rolls off more gradually. If rolloff_factor is 0, no distance attenuation
  will be applied.

  Spatial sounds require each channel's parameters to be set individually. Channels are
  indexed starting at 0 and follow the track order defined by the audio content. For example,
  for a spatial sound with stereo content this function should be called twice, passing
  channel = 0 for left and channel = 1 for right. A sound output must be enabled as a spatial
  sound using MLAudioSetSpatialSoundEnable for this property to take effect.

  \apilevel 20

  \param[in] handle MLHandle of the sound output.
  \param[in] channel Channel of the sound output.
  \param[in] properties MLAudioSpatialSoundDistanceProperties struct to set the properties.

  \retval MLResult_InvalidParam If input parameter is invalid.
  \retval MLResult_Ok Successfully set the properties.
  \retval MLResult_UnspecifiedFailure Internal error.
  \retval MLAudioResult_HandleNotFound Handle not found.
  \retval MLAudioResult_InternalConfigError Internal config error.
  \retval MLAudioResult_NotImplemented Internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetSpatialSoundDistanceAttenuation(MLHandle handle, uint32_t channel, const MLAudioSpatialSoundDistanceProperties *properties);

/*!
  \brief Queries the behavior by which a spatial sound is attenuated due to distance.

  The behavior for distance attenuation is specified by an MLAudioSpatialSoundDistanceProperties
  struct reported by the out_properties argument of this function. Within this struct the
  min_distance specifies the distance from the listener beyond which a spatial sound starts
  attenuating with distance. The max_distance specifies the distance from the listener beyond
  which no further attenuation occurs. Between min_distance and max_distance a spatial sound will
  be attenuated with distance according to the rolloff_factor. A rolloff_factor of 1 will produce
  distance attenuation that approximates real world distance attenuation. A rolloff_factor greater
  than 1 will produce distance attenuation that rolls off faster as distance increases, while less
  than 1 will produce distance attenuation that rolls off more gradually. If rolloff_factor is 0,
  no distance attenuation will be applied.

  Spatial sounds require each channel's parameters to be queried individually. Channels are
  indexed starting at 0 and follow the track order defined by the audio content. For example,
  for a spatial sound with stereo content this function should be called twice, passing
  channel = 0 for left and channel = 1 for right. A sound output must be enabled as a spatial
  sound using MLAudioSetSpatialSoundEnable for this property to take effect.

  \apilevel 20

  \param[in] handle MLHandle of the sound output.
  \param[in] channel Channel of the sound output.
  \param[out] out_properties MLAudioSpatialSoundDistanceProperties struct to be filled with the properties.

  \retval MLResult_InvalidParam If input parameter is invalid.
  \retval MLResult_Ok Successfully retrieved the properties.
  \retval MLResult_UnspecifiedFailure Internal error.
  \retval MLAudioResult_HandleNotFound Handle not found.
  \retval MLAudioResult_InternalConfigError Internal config error.
  \retval MLAudioResult_NotImplemented Internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetSpatialSoundDistanceAttenuation(MLHandle handle, uint32_t channel, MLAudioSpatialSoundDistanceProperties *out_properties);

/*!
  \brief Sets a radiation pattern that describes the directionality for one channel of a spatial sound.

  Each channel of a spatial sound has a dual cone radiation pattern specified by an
  MLAudioSpatialSoundRadiationProperties struct. The radiation pattern is oriented toward the
  listener for all channels if billboarding is enabled, or in the direction set by
  MLAudioSetSpatialSoundDirection for each channel if billboarding is disabled. The default
  values for the MLAudioSpatialSoundRadiationProperties struct were chosen to model a human
  speaking.

  Spatial sounds require each channel's parameters to be set individually. Channels are
  indexed starting at 0 and follow the track order defined by the audio content. For example,
  for a spatial sound with stereo content this function should be called twice, passing
  channel = 0 for left and channel = 1 for right. A sound output must be enabled as a spatial
  sound using MLAudioSetSpatialSoundEnable for this property to take effect.


  \apilevel 20

  \param[in] handle MLHandle of the sound output.
  \param[in] channel Channel of the sound output.
  \param[in] properties MLAudioSpatialSoundRadiationProperties struct to set the properties.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully set the properties.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetSpatialSoundRadiation(MLHandle handle, uint32_t channel, const MLAudioSpatialSoundRadiationProperties *properties);

/*!
  \brief Queries the radiation pattern that describes the directionality for one channel of a spatial sound.

  Each channel of a spatial sound has a dual cone radiation pattern specified by an
  MLAudioSpatialSoundRadiationProperties struct. The radiation pattern is oriented toward the
  listener for all channels if billboarding is enabled, or in the direction set by
  MLAudioSetSpatialSoundDirection for each channel if billboarding is disabled.

  Spatial sounds require each channel's parameters to be queried individually. Channels are
  indexed starting at 0 and follow the track order defined by the audio content. For example,
  for a spatial sound with stereo content this function should be called twice, passing
  channel = 0 for left and channel = 1 for right. A sound output must be enabled as a spatial
  sound using MLAudioSetSpatialSoundEnable for this property to take effect.

  \apilevel 20

  \param[in] handle MLHandle of the sound output.
  \param[in] channel Channel of the sound output.
  \param[out] out_properties MLAudioSpatialSoundRadiationProperties struct to be filled with the properties.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the properties.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetSpatialSoundRadiation(MLHandle handle, uint32_t channel, MLAudioSpatialSoundRadiationProperties *out_properties);

/*!
  \brief Sets the gain and 3-band EQ on the Direct Path for one channel of a spatial sound.

  Naturally occurring sounds in a physical space are experienced as an initial arrival
  followed by an increasing number of reflections that tend toward a well-mixed reverberation
  over time. These reflections provide spatial cues that inform the listener as to the position
  of the sound and the characteristics of the environment in which it occurs. For spatial sounds,
  this progression is modeled across four stages: Direct Path, Reflections, Dispersion, and Reverb.
  The level of each of these stages can be manipulated to achieve the desired perceptual balance
  between them.

  The Direct Level is applied to the sound traveling directly from the source to the listener.
  The gain and 3-band EQ for this stage is specified by an MLAudioMultibandLevel struct.

  Spatial sounds require each channel's parameters to be set individually. Channels are
  indexed starting at 0 and follow the track order defined by the audio content. For example,
  for a spatial sound with stereo content this function should be called twice, passing
  channel = 0 for left and channel = 1 for right. A sound output must be enabled as a spatial
  sound using MLAudioSetSpatialSoundEnable for this property to take effect.

  \apilevel 20

  \param[in] handle MLHandle of the sound output.
  \param[in] channel Channel of the sound output.
  \param[in] level MLAudioMultibandLevel struct to set the gain and eq properties.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully set the properties.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetSpatialSoundDirectLevel(MLHandle handle, uint32_t channel, const MLAudioMultibandLevel *level);

/*!
  \brief Queries the gain and 3-band EQ on the Direct Path for one channel of a spatial sound.

  Naturally occurring sounds in a physical space are experienced as an initial arrival
  followed by an increasing number of reflections that tend toward a well-mixed reverberation
  over time. These reflections provide spatial cues that inform the listener as to the position
  of the sound and the characteristics of the environment in which it occurs. For spatial sounds,
  this progression is modeled across four stages: Direct Path, Reflections, Dispersion, and Reverb.
  The level of each of these stages can be manipulated to achieve the desired perceptual balance
  between them.

  The Direct Level is applied to the sound traveling directly from the source to the listener.
  The gain and 3-band EQ for this stage is specified by an MLAudioMultibandLevel struct.

  Spatial sounds require each channel's parameters to be queried individually. Channels are
  indexed starting at 0 and follow the track order defined by the audio content. For example,
  for a spatial sound with stereo content this function should be called twice, passing
  channel = 0 for left and channel = 1 for right. A sound output must be enabled as a spatial
  sound using MLAudioSetSpatialSoundEnable for this property to take effect.

  \apilevel 20

  \param[in] handle MLHandle of the sound output.
  \param[in] channel Channel of the sound output.
  \param[out] out_level MLAudioMultibandLevel struct to be filled with the gain and eq properties.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the properties.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetSpatialSoundDirectLevel(MLHandle handle, uint32_t channel, MLAudioMultibandLevel *out_level);

/*!
  \brief Sets a gain and 3-band EQ applied to all indirect paths for one channel of a spatial sound.

  Naturally occurring sounds in a physical space are experienced as an initial arrival
  followed by an increasing number of reflections that tend toward a well-mixed reverberation
  over time. These reflections provide spatial cues that inform the listener as to the position
  of the sound and the characteristics of the environment in which it occurs. For spatial sounds,
  this progression is modeled across four stages: Direct Path, Reflections, Dispersion, and Reverb.
  The level of each of these stages can be manipulated to achieve the desired perceptual balance
  between them.

  The Indirect Level is applied to the Reflections, Dispersion, and Reverb stages as a group,
  combining with the level specified for each individual stage. The Reflections stage consists of
  discrete reflections off of distinct surfaces. The Dispersion stage consists of clustered groups
  of late reflections smeared in time. The Reverb stage consists of the well-mixed reverberation tail
  of the sound. The gain and 3-band EQ applied to these stages as a group is specified by an
  MLAudioMultibandLevel struct.

  Spatial sounds require each channel's parameters to be set individually. Channels are
  indexed starting at 0 and follow the track order defined by the audio content. For example,
  for a spatial sound with stereo content this function should be called twice, passing
  channel = 0 for left and channel = 1 for right. A sound output must be enabled as a spatial
  sound using MLAudioSetSpatialSoundEnable for this property to take effect.

  \apilevel 20

  \param[in] handle MLHandle of the sound output.
  \param[in] channel Channel of the sound output.
  \param[in] level MLAudioMultibandLevel struct to set the gain and eq properties.

  \retval MLResult_InvalidParam If input parameter is invalid.
  \retval MLResult_Ok Successfully set the properties.
  \retval MLResult_UnspecifiedFailure Internal error.
  \retval MLAudioResult_HandleNotFound Handle not found.
  \retval MLAudioResult_InternalConfigError Internal config error.
  \retval MLAudioResult_NotImplemented Internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetSpatialSoundIndirectLevel(MLHandle handle, uint32_t channel, const MLAudioMultibandLevel *level);

/*!
  \brief Queries the gain and 3-band EQ applied to all indirect paths for one channel of a spatial sound.

  Naturally occurring sounds in a physical space are experienced as an initial arrival
  followed by an increasing number of reflections that tend toward a well-mixed reverberation
  over time. These reflections provide spatial cues that inform the listener as to the position
  of the sound and the characteristics of the environment in which it occurs. For spatial sounds,
  this progression is modeled across four stages: Direct Path, Reflections, Dispersion, and Reverb.
  The level of each of these stages can be manipulated to achieve the desired perceptual balance
  between them.

  The Indirect Level is applied to the Reflections, Dispersion, and Reverb stages as a group,
  combining with the level specified for each individual stage. The Reflections stage consists of
  discrete reflections off of distinct surfaces. The Dispersion stage consists of clustered groups
  of late reflections smeared in time. The Reverb stage consists of the well-mixed reverberation tail
  of the sound. The gain and 3-band EQ applied to these stages as a group is specified by an
  MLAudioMultibandLevel struct.

  Spatial sounds require each channel's parameters to be queried individually. Channels are
  indexed starting at 0 and follow the track order defined by the audio content. For example,
  for a spatial sound with stereo content this function should be called twice, passing
  channel = 0 for left and channel = 1 for right. A sound output must be enabled as a spatial
  sound using MLAudioSetSpatialSoundEnable for this property to take effect.

  \apilevel 20

  \param[in] handle MLHandle of the sound output.
  \param[in] channel Channel of the sound output.
  \param[out] out_level MLAudioMultibandLevel struct to be filled with the gain and eq properties.

  \retval MLResult_InvalidParam If input parameter is invalid.
  \retval MLResult_Ok Successfully retrieved the properties.
  \retval MLResult_UnspecifiedFailure Internal error.
  \retval MLAudioResult_HandleNotFound Handle not found.
  \retval MLAudioResult_InternalConfigError Internal config error.
  \retval MLAudioResult_NotImplemented Internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetSpatialSoundIndirectLevel(MLHandle handle, uint32_t channel, MLAudioMultibandLevel *out_level);

/*!
  \brief Sets the gain and 3-band EQ on the Dispersion stage for one channel of a spatial sound.

  Naturally occurring sounds in a physical space are experienced as an initial arrival
  followed by an increasing number of reflections that tend toward a well-mixed reverberation
  over time. These reflections provide spatial cues that inform the listener as to the position
  of the sound and the characteristics of the environment in which it occurs. For spatial sounds,
  this progression is modeled across four stages: Direct Path, Reflections, Dispersion, and Reverb.
  The level of each of these stages can be manipulated to achieve the desired perceptual balance
  between them.

  The Dispersion stage consists of clustered groups of late reflections smeared in time. The gain
  and 3-band EQ for this stage is specified by an MLAudioMultibandLevel struct.

  This 'SpatialSoundSendLevel' API sets the amount of signal that a particular sound feeds into
  a shared acoustic processing effect. To set the properties of the processing effect itself,
  see the corresponding 'AcousticScene' API which is MLAudioSetAcousticSceneDispersionDefault.

  Spatial sounds require each channel's parameters to be set individually. Channels are
  indexed starting at 0 and follow the track order defined by the audio content. For example,
  for a spatial sound with stereo content this function should be called twice, passing
  channel = 0 for left and channel = 1 for right. A sound output must be enabled as a spatial
  sound using MLAudioSetSpatialSoundEnable for this property to take effect.

  \apilevel 20

  \param[in] handle MLHandle of the sound output.
  \param[in] channel Channel of the sound output.
  \param[in] level MLAudioMultibandLevel struct to set the gain and eq properties.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully set the properties.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/

ML_API MLResult ML_CALL MLAudioSetSpatialSoundDispersionSendLevel(MLHandle handle, uint32_t channel, const MLAudioMultibandLevel *level);

/*!
  \brief Queries the gain and 3-band EQ on the Dispersion stage for one channel of a spatial sound.

  Naturally occurring sounds in a physical space are experienced as an initial arrival
  followed by an increasing number of reflections that tend toward a well-mixed reverberation
  over time. These reflections provide spatial cues that inform the listener as to the position
  of the sound and the characteristics of the environment in which it occurs. For spatial sounds,
  this progression is modeled across four stages: Direct Path, Reflections, Dispersion, and Reverb.
  The level of each of these stages can be manipulated to achieve the desired perceptual balance
  between them.

  The Dispersion stage consists of clustered groups of late reflections smeared in time. The gain
  and 3-band EQ for this stage is specified by an MLAudioMultibandLevel struct.

  This 'SpatialSoundSendLevel' API queries the amount of signal that a particular sound feeds into
  a shared acoustic processing effect. To query the properties of the processing effect itself,
  see the corresponding 'AcousticScene' API which is MLAudioGetAcousticSceneDispersionDefault.

  Spatial sounds require each channel's parameters to be queried individually. Channels are
  indexed starting at 0 and follow the track order defined by the audio content. For example,
  for a spatial sound with stereo content this function should be called twice, passing
  channel = 0 for left and channel = 1 for right. A sound output must be enabled as a spatial
  sound using MLAudioSetSpatialSoundEnable for this property to take effect.

  \apilevel 20

  \param[in] handle MLHandle of the sound output.
  \param[in] channel Channel of the sound output.
  \param[out] out_level MLAudioMultibandLevel struct to be filled with the gain and eq properties.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the properties.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetSpatialSoundDispersionSendLevel(MLHandle handle, uint32_t channel, MLAudioMultibandLevel *out_level);

/*!
  \brief Sets the gain and 3-band EQ on the Reverb stage for one channel of a spatial sound.

  Naturally occurring sounds in a physical space are experienced as an initial arrival
  followed by an increasing number of reflections that tend toward a well-mixed reverberation
  over time. These reflections provide spatial cues that inform the listener as to the position
  of the sound and the characteristics of the environment in which it occurs. For spatial sounds,
  this progression is modeled across four stages: Direct Path, Reflections, Dispersion, and Reverb.
  The level of each of these stages can be manipulated to achieve the desired perceptual balance
  between them.

  The Reverb stage consists of the well-mixed reverberation tail of the sound. The gain and 3-band
  EQ for this stage is specified by an MLAudioMultibandLevel struct.

  This 'SpatialSoundSendLevel' API sets the amount of signal that a particular sound feeds into
  a shared acoustic processing effect. To set the properties of the processing effect itself,
  see the corresponding 'AcousticScene' API which is MLAudioSetAcousticSceneReverbDefault.

  Spatial sounds require each channel's parameters to be set individually. Channels are
  indexed starting at 0 and follow the track order defined by the audio content. For example,
  for a spatial sound with stereo content this function should be called twice, passing
  channel = 0 for left and channel = 1 for right. A sound output must be enabled as a spatial
  sound using MLAudioSetSpatialSoundEnable for this property to take effect.

  \apilevel 20

  \param[in] handle MLHandle of the sound output.
  \param[in] channel Channel of the sound output.
  \param[in] level MLAudioMultibandLevel struct to set the gain and eq properties.

  \retval MLResult_InvalidParam If input parameter is invalid.
  \retval MLResult_Ok Successfully set the properties.
  \retval MLResult_UnspecifiedFailure Internal error.
  \retval MLAudioResult_HandleNotFound Handle not found.
  \retval MLAudioResult_InternalConfigError Internal config error.
  \retval MLAudioResult_NotImplemented Internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetSpatialSoundReverbSendLevel(MLHandle handle, uint32_t channel, const MLAudioMultibandLevel *level);

/*!
  \brief Queries the gain and 3-band EQ on the Reverb stage for one channel of a spatial sound.

  Naturally occurring sounds in a physical space are experienced as an initial arrival
  followed by an increasing number of reflections that tend toward a well-mixed reverberation
  over time. These reflections provide spatial cues that inform the listener as to the position
  of the sound and the characteristics of the environment in which it occurs. For spatial sounds,
  this progression is modeled across four stages: Direct Path, Reflections, Dispersion, and Reverb.
  The level of each of these stages can be manipulated to achieve the desired perceptual balance
  between them.

  The Reverb stage consists of the well-mixed reverberation tail of the sound. The gain and 3-band
  EQ for this stage is specified by an MLAudioMultibandLevel struct.

  This 'SpatialSoundSendLevel' API queries the amount of signal that a particular sound feeds into
  a shared acoustic processing effect. To query the properties of the processing effect itself,
  see the corresponding 'AcousticScene' API which is MLAudioGetAcousticSceneReverbDefault.

  Spatial sounds require each channel's parameters to be queried individually. Channels are
  indexed starting at 0 and follow the track order defined by the audio content. For example,
  for a spatial sound with stereo content this function should be called twice, passing
  channel = 0 for left and channel = 1 for right. A sound output must be enabled as a spatial
  sound using MLAudioSetSpatialSoundEnable for this property to take effect.

  \apilevel 20

  \param[in] handle MLHandle of the sound output.
  \param[in] channel Channel of the sound output.
  \param[out] out_level MLAudioMultibandLevel struct to be filled with the gain and eq properties.

  \retval MLResult_InvalidParam If input parameter is invalid.
  \retval MLResult_Ok Successfully retrieved the properties.
  \retval MLResult_UnspecifiedFailure Internal error.
  \retval MLAudioResult_HandleNotFound Handle not found.
  \retval MLAudioResult_InternalConfigError Internal config error.
  \retval MLAudioResult_NotImplemented Internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetSpatialSoundReverbSendLevel(MLHandle handle, uint32_t channel, MLAudioMultibandLevel *out_level);

/*!
  \brief Sets whether the position and direction for a spatial sound are interpreted in head-relative coordinates.

  A head-relative coordinate system has an origin and orientation locked to the user's head
  center and forward direction. For spatial sounds with head-relative enabled, the position
  and direction as specified by MLAudioSetSpatialSoundPosition and MLAudioSetSpatialSoundDirection
  (and reported by MLAudioGetSpatialSoundPosition and MLAudioGetSpatialSoundDirection) are
  interpreted within such a coordinate system. For spatial sounds with head-relative disabled,
  the position and direction are interpreted within the world coordinate system defined by the
  platform. By default, head-relative is disabled for spatial sounds.

  \apilevel 7

  \param[in] handle MLHandle of the sound output.
  \param[in] is_head_relative If true, coordinates will be head-relative.

  \retval MLResult_Ok Successfully set the value.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown failure.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetSpatialSoundHeadRelative(MLHandle handle, bool is_head_relative);

/*!
  \brief Queries whether the position and direction for a spatial sound are interpreted in head-relative coordinates.

  A head-relative coordinate system has an origin and orientation locked to the user's head
  center and forward direction. For spatial sounds with head-relative enabled, the position
  and direction as specified by MLAudioSetSpatialSoundPosition and MLAudioSetSpatialSoundDirection
  (and reported by MLAudioGetSpatialSoundPosition and MLAudioGetSpatialSoundDirection) are
  interpreted within such a coordinate system. For spatial sounds with head-relative disabled,
  the position and direction are interpreted within the world coordinate system defined by the
  platform. By default, head-relative is disabled for spatial sounds.

  \apilevel 20

  \param[in] handle MLHandle of the sound output.
  \param[out] out_is_head_relative If true, coordinates are head-relative.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the value.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown failure.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetSpatialSoundHeadRelative(MLHandle handle, bool *out_is_head_relative);

/*!
  \brief Queries a list of ID-tracked requests for raycast operations.

  For a custom spatial audio to physics engine integration, typically handled by audio plugins,
  this function provides a list of raycasts to be performed by the physics engine.

  \note This function is not intended to be called directly by developers.
  \note The caller is responsible for deallocating the memory containing the raycast requests.

  \apilevel 20

  \param[out] out_raycast_requests MLAudioRaycastRequest struct to be filled with requests for raycast operation.
  \param[out] out_request_count Value to be filled with number of raycast operations requested.

  \retval MLResult_Ok Successfully set the properties.
  \retval MLResult_InvalidParam If input parameter is invalid.
  \retval MLResult_UnspecifiedFailure Internal error.
  \retval MLAudioResult_InternalConfigError Internal config error.
  \retval MLAudioResult_NotImplemented Internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetSpatialRaycastRequests(MLAudioRaycastRequest ** out_raycast_requests, uint32_t *out_request_count);

/*!
  \brief Sets the ID-tracked results for previously requested raycast operations.

  For a custom spatial audio to physics engine integration, typically handled by audio plugins,
  this function reports the results of raycasts performed by the physics engine.

  \note This function is not intended to be called directly by developers.

  \apilevel 20

  \param[in] raycast_results MLAudioRaycastResult struct to set the list of raycast operation results.
  \param[in] result_count Sets the number of raycast results.

  \retval MLResult_Ok Successfully retrieved the properties.
  \retval MLResult_InvalidParam If input parameter is invalid.
  \retval MLResult_UnspecifiedFailure Internal error.
  \retval MLAudioResult_InternalConfigError Internal config error.
  \retval MLAudioResult_NotImplemented Internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetSpatialRaycastResults(MLAudioRaycastResult * raycast_results, uint32_t result_count);
/*! \} */

/////////////////////////////
/////////////////////////////
///       BUFFERING.
/////////////////////////////
/////////////////////////////

/*!
  \defgroup OutputBuffering Buffering
  \ingroup AudioOutput
  \addtogroup OutputBuffering
  \{
*/

/*!
  \brief Queries the minimum and recommended settings for buffered sound outputs.

  This function is typically called before MLAudioCreateSoundWithBufferedOutput. It queries
  the minimum and recommended buffer sizes for the specified settings of channel count, sample
  rate, and 'max pitch change'. The max pitch change parameter determines the additional buffer
  size required to support pitch values greater than 1. Applying a pitch change to a buffered
  output that is greater than the specified max pitch change can lead to undesirable results.

  \apilevel 7

  \param[in] channel_count Number of audio channels.
  \param[in] samples_per_second Sample rate for the buffered output.
  \param[in] max_pitch_change Top pitch (1.0 - 2.0) for this sound output.
  \param[out] out_format MLAudioBufferFormat struct to be filled with recommended format properties.
  \param[out] out_recommended_size_in_bytes Retrieved recommended size.
  \param[out] out_min_size_in_bytes Retrieved minimum allowable size.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the properties.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_InvalidChannelCount Failed due to an invalid channel count.
  \retval MLAudioResult_InvalidSampleRate Failed due to an invalid sample rate.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetBufferedOutputDefaults(uint32_t channel_count, uint32_t samples_per_second, float max_pitch_change, MLAudioBufferFormat *out_format, uint32_t *out_recommended_size_in_bytes, uint32_t *out_min_size_in_bytes);

/*!
  \brief Queries the latency for a buffered sound output.

  The latency for a buffered sound output is the time between when a buffer is enqueued via
  MLAudioReleaseOutputBuffer and when the corresponding audio is heard from the active audio
  output device. Note that output latency may change depending on which output device is active
  (for example, Bluetooth earbuds typically add latency compared to the built-in speakers in
  the headset).

  \apilevel 7

  \param[in] handle MLHandle of the sound output.
  \param[out] out_latency_in_msec Retrieved latency in milliseconds.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the value.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.
  \retval MLAudioResult_OperationUnavailable Failed because operation is unavailable.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetBufferedOutputLatency(MLHandle handle, float *out_latency_in_msec);

/*!
  \brief Queries the number of audio frames played by a buffered output.

  This call queries the number of audio frames played by a buffered output since the last call
  to MLAudioStartSound. A subsequent call to MLAudioStartSound sets the count back to 0.

  \apilevel 7

  \param[in] handle MLHandle of the sound output.
  \param[out] out_frames_played Retrieved number of audio frames played.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the value.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetBufferedOutputFramesPlayed(MLHandle handle, uint64_t *out_frames_played);

/*!
  \brief Retrieves an empty buffer for writing audio data for a buffered sound output.

  Standard usage is to call this function by polling or within a callback of type
  MLAudioBufferCallback registered with MLAudioCreateSoundWithBufferedOutput. This call
  returns MLAudioResult_BufferNotReady if a buffer is not available for writing audio
  data, informing the caller to wait. Once filled, the buffer must be released by calling
  MLAudioReleaseOutputBuffer.

  \apilevel 7

  \param[in] handle MLHandle of the sound output.
  \param[out] out_buf Retrieved MLAudioBuffer struct pointer to buffer for writing audio data.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the buffer.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_BufferNotReady Failed because buffer was not ready.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.
  \retval MLAudioResult_OperationUnavailable Failed because operation is unavailable.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetOutputBuffer(MLHandle handle, MLAudioBuffer *out_buf);

/*!
  \brief Releases a filled audio output buffer for playback through a buffered sound output.

  After filling a buffer retrieved by MLAudioGetOutputBuffer, the buffer must be released
  using this function in order to be played through a sound output.

  \param[in] handle MLHandle of the sound output.

  \apilevel 7

  \retval MLResult_Ok Successfully released the buffer.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_BufferNotReady Failed because buffer was not ready.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.
  \retval MLAudioResult_OperationUnavailable Failed because operation is unavailable.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioReleaseOutputBuffer(MLHandle handle);
/*! \} */

/////////////////////////////
/////////////////////////////
///      MASTER VOLUME.
/////////////////////////////
/////////////////////////////

/*!
  \defgroup OutputMasterVolume Master Volume
  \ingroup AudioOutput
  \addtogroup OutputMasterVolume
  \{
*/

/*!
  \brief Queries the master volume.

  The range of the volume is 0-100, with 0 being silent and 100 being full volume.

  \param[out] out_volume Retrieved master volume.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the value.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/

ML_API MLResult ML_CALL MLAudioGetMasterVolume(float *out_volume);

/*!
  \brief Registers a callback for changes to the master volume.

  \param[in] callback Callback function pointer.
  \param[in] context Generic data pointer passed back through the callback.

  \retval MLResult_AllocFailed Failed due to memory allocation failure.
  \retval MLResult_Ok Successfully registered the callback.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetMasterVolumeCallback(MLAudioMasterVolumeChangedCallback callback, void *context);

/*!
  \brief Queries the state of the global output mute.

  \apilevel 20

  \param[out] bool out_is_muted If true, global output is muted.

  \retval MLResult_Ok Successfully retrieved the value.
  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown failure.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetOutputMute(bool *out_is_muted);

/*!
  \brief Registers a callback for changes to the global output mute.

  \apilevel 8

  \param[in] callback Callback function pointer.
  \param[in] context Generic data pointer passed back through the callback.

  \retval MLResult_AllocFailed Failed due to memory allocation failure.
  \retval MLResult_Ok Successfully registered the callback.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioSetOutputMuteCallback(MLAudioOutputMuteChangedCallback callback, void *context);
/*! \} */
/*! \} */

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
///                              AUDIO INPUT.
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

/*!
  \defgroup AudioInput Audio Input
  \ingroup Audio
  \addtogroup AudioInput
  \{
*/

/////////////////////////////
/////////////////////////////
///       ALLOCATION.
/////////////////////////////
/////////////////////////////

/*!
  \defgroup InputAllocation Allocation
  \ingroup AudioInput
  \addtogroup InputAllocation
  \{
*/

/*!
  \brief Creates a new sound input that provides audio from the wearable microphones.

  The various mic capture streams represent different configurations of the input from
  the wearable microphones, intended for different purposes. The 'format' argument must
  be populated with the correct settings for the mic capture type being requested:

  MLAudioMicCaptureType_VoiceComm is intended for remote communications, and uses a
  channel count of 1 and a sample rate of 16,000.

  MLAudioMicCaptureType_VoiceCapture is intended for device-local applications involving
  user voice, and uses a channel count of 1 and a sample rate of 48,000.

  MLAudioMicCaptureType_WorldCapture provides a stereo capture of the user's physical
  environment, and uses a channel count of 2 and a sample rate of 48,000.

  MLAudioMicCaptureType_RawMicsAndAECRef provides a 6-channel capture comprising all 4
  mics (unprocessed) plus the AEC reference signal from the amplifier, and uses a channel
  count of 6 and a sample rate of 48,000.

  After creation, the input is started by calling MLAudioStartInput. After the input
  has been started, the next available full buffer is retrieved by calling
  MLAudioGetInputBuffer. This can be done on a polling basis, or a callback can be set
  using the 'callback' argument of the present function to notify when a buffer is available.
  After retrieving and consuming the next available buffer, MLAudioReleaseInputBuffer must
  be called to indicate that the buffer has been consumed and is ready to be refilled.
  MLAudioGetInputBuffer and MLAudioReleaseInputBuffer are valid to call within the callback.
  The 'buffer_size' argument will use the recommended size if 0 is passed in.

  \apilevel 20

  \param[in] mic_capture_type MLAudioMicCaptureType enum specifying the type of mic capture created.
  \param[in] format MLAudioBufferFormat struct specifying the format properties.
  \param[in] buffer_size Requested size in bytes for each of the two stream buffers.
  \param[in] callback Callback function pointer.
  \param[in] context Generic data pointer passed back through the callback.
  \param[out] out_handle MLHandle to be used in subsequent calls.

  \retval MLResult_AllocFailed Failed due to memory allocation failure.
  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully created a sound input.
  \retval MLResult_PermissionDenied Failed due to lack of permission.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_InvalidBitsPerSample Failed due to an invalid bits per sample.
  \retval MLAudioResult_InvalidBufferSize Failed due to an invalid buffer size.
  \retval MLAudioResult_InvalidChannelCount Failed due to an invalid channel count.
  \retval MLAudioResult_InvalidSampleFormat Failed due to an invalid sample format.
  \retval MLAudioResult_InvalidSampleRate Failed due to an invalid sample rate.
  \retval MLAudioResult_InvalidValidBits Failed due to an invalid valid bits per sample.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions android.permission.RECORD_AUDIO (protection level: dangerous)
*/
ML_API MLResult ML_CALL MLAudioCreateInputFromMicCapture(MLAudioMicCaptureType mic_capture_type, const MLAudioBufferFormat *format, uint32_t buffer_size_in_bytes, MLAudioBufferCallback callback, void *context, MLHandle *out_handle);

/*!
  \brief Creates a new sound input that provides a virtual capture stream.

  The Virtual Capture stream is a stereo stream capturing the combined audio output mix of
  the capture-eligible sounds (typically app-generated) currently being played by the
  audio rendering engine. The 'format' argument must be populated with the correct settings
  for virtual capture, which uses a channel count of 2 and a sample rate of 48,000.

  After creation, the input is started by calling MLAudioStartInput. After the input
  has been started, the next available full buffer is retrieved by calling
  MLAudioGetInputBuffer. This can be done on a polling basis, or a callback can be set
  using the 'callback' argument of the present function to notify when a buffer is available.
  After retrieving and consuming the next available buffer, MLAudioReleaseInputBuffer must
  be called to indicate that the buffer has been consumed and is ready to be refilled.
  MLAudioGetInputBuffer and MLAudioReleaseInputBuffer are valid to call within the callback.
  The 'buffer_size' argument will use the recommended size if 0 is passed in.

  \param[in] format MLAudioBufferFormat struct specifying the format properties.
  \param[in] buffer_size Requested size in bytes of the buffers.
  \param[in] callback Callback function pointer.
  \param[in] context Generic data pointer passed back through the callback.
  \param[out] out_handle MLHandle to be used in subsequent calls.

  \retval MLResult_AllocFailed Failed due to memory allocation failure.
  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully created sound input.
  \retval MLResult_PermissionDenied Failed due to lack of permission.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_InvalidBitsPerSample Failed due to an invalid bits per sample.
  \retval MLAudioResult_InvalidBufferSize Failed due to an invalid buffer size.
  \retval MLAudioResult_InvalidChannelCount Failed due to an invalid channel count.
  \retval MLAudioResult_InvalidSampleFormat Failed due to an invalid sample format.
  \retval MLAudioResult_InvalidSampleRate Failed due to an invalid sample rate.
  \retval MLAudioResult_InvalidValidBits Failed due to an invalid valid bits per sample.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions android.permission.RECORD_AUDIO (protection level: dangerous)
*/
ML_API MLResult ML_CALL MLAudioCreateInputFromVirtualCapture(const MLAudioBufferFormat *format, uint32_t buffer_size, MLAudioBufferCallback callback, void *context, MLHandle *out_handle);

/*!
  \brief Creates a new sound input that provides a mixed capture stream.

  The Mixed Capture stream is intended for capturing the audible user experience, including
  both sounds from the physical environment and sounds produced by the device. The stream
  includes a mix  of the 'Virtual Capture' stream, the MLAudioMicCaptureType_VoiceCapture
  stream, and the MLAudioMicCaptureType_WorldCapture stream. By default the World Capture
  stream is silent and the other two streams are full volume. These levels can be adjusted
  by calling MLAudioSetMixedCaptureMix. Independent of the specified MixedCaptureMix, the
  Voice Capture and World Capture mic signals are scaled on a curve based on the current
  setting of Master Volume to keep the real and virtual signals in good balance. The Mixed
  Capture stream uses a channel count of 2 and a sample rate of 48,000.

  After creation, the input is started by calling MLAudioStartInput. After the input
  has been started, the next available full buffer is retrieved by calling
  MLAudioGetInputBuffer. This can be done on a polling basis, or a callback can be set
  using the 'callback' argument of the present function to notify when a buffer is available.
  After retrieving and consuming the next available buffer, MLAudioReleaseInputBuffer must
  be called to indicate that the buffer has been consumed and is ready to be refilled.
  MLAudioGetInputBuffer and MLAudioReleaseInputBuffer are valid to call within the callback.
  The 'buffer_size' argument will use the recommended size if 0 is passed in.

  \param[in] format MLAudioBufferFormat struct specifying the format properties.
  \param[in] buffer_size Requested size in bytes of the buffers.
  \param[in] callback Callback function pointer.
  \param[in] context Generic data pointer passed back through the callback.
  \param[out] out_handle MLHandle to be used in subsequent calls.

  \retval MLResult_AllocFailed Failed due to memory allocation failure.
  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully created sound input.
  \retval MLResult_PermissionDenied Failed due to lack of permission.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_InvalidBitsPerSample Failed due to an invalid bits per sample.
  \retval MLAudioResult_InvalidBufferSize Failed due to an invalid buffer size.
  \retval MLAudioResult_InvalidChannelCount Failed due to an invalid channel count.
  \retval MLAudioResult_InvalidSampleFormat Failed due to an invalid sample format.
  \retval MLAudioResult_InvalidSampleRate Failed due to an invalid sample rate.
  \retval MLAudioResult_InvalidValidBits Failed due to an invalid valid bits per sample.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions android.permission.RECORD_AUDIO (protection level: dangerous)
*/
ML_API MLResult ML_CALL MLAudioCreateInputFromMixedCapture(const MLAudioBufferFormat *format, uint32_t buffer_size, MLAudioBufferCallback callback, void *context, MLHandle *out_handle);

/*!
  \brief Destroys a sound input.

  \param[in] handle MLHandle of the sound input.

  \retval MLResult_Ok Successfully destroyed a sound input.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioDestroyInput(MLHandle handle);
/*! \} */

/////////////////////////////
/////////////////////////////
///        CONTROL.
/////////////////////////////
/////////////////////////////

/*!
  \defgroup InputControl Control
  \ingroup AudioInput
  \addtogroup InputControl
  \{
*/

/*!
  \brief Starts a sound input.

  Calling this function on a playing input has no effect and returns success.

  \param[in] handle MLHandle of the sound input.

  \retval MLResult_Ok Sound input is started, or continues if already playing.
  \retval MLResult_PermissionDenied Failed due to lack of permission.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioStartInput(MLHandle handle);

/*!
  \brief Stops a sound input.

  Calling this function on a stopped input has no effect and returns success.

  \param[in] handle MLHandle of the sound input.

  \retval MLResult_Ok Sound input is stopped, or remains stopped if already stopped.
  \retval MLResult_PermissionDenied Failed due to lack of permission.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioStopInput(MLHandle handle);

/*!
  \brief Queries the activity state of a sound input.

  The state of sound inputs can be either MLAudioState_Playing or MLAudioState_Stopped,
  depending on whether MLAudioStartInput or MLAudioStopInput was called most recently.
  When an input is stopped and restarted, its buffers are emptied and buffering begins
  again from a clean slate.

  \param[in] handle MLHandle of the sound input.
  \param[out] out_state MLAudioState enum of the sound input.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the properties.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetInputState(MLHandle handle, MLAudioState *out_state);
/*! \} */

/////////////////////////////
/////////////////////////////
///       BUFFERING.
/////////////////////////////
/////////////////////////////

/*!
  \defgroup InputBuffering Buffering
  \ingroup AudioInput
  \addtogroup InputBuffering
  \{
*/

/*!
  \brief Queries the minimum and recommended settings for buffered sound inputs.

  This function is typically called before one of the MLAudioCreateInput... calls.
  It queries the minimum and recommended buffer sizes for the specified settings of
  channel count and sample rate.

  \param[in] channel_count Number of audio channels.
  \param[in] samples_per_second Sample rate for the buffered input.
  \param[out] out_format MLAudioBufferFormat struct to be filled with recommended format properties.
  \param[out] out_recommended_size_in_bytes Retrieved recommended size.
  \param[out] out_min_size_in_bytes Retrieved minimum allowable size.

  \apilevel 7

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the properties.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InvalidChannelCount Failed due to an invalid channel count.
  \retval MLAudioResult_InvalidSampleRate Failed due to an invalid sample rate.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetBufferedInputDefaults(uint32_t channel_count, uint32_t samples_per_second, MLAudioBufferFormat *out_format, uint32_t *out_recommended_size_in_bytes, uint32_t *out_min_size_in_bytes);

/*!
  \brief Queries the latency for a sound input.

  The latency for a sound input is the time between when a sound is picked up at
  the microphone and when the corresponding audio becomes available via a call to
  MLAudioGetInputBuffer.

  \param[in] handle MLHandle of the sound input.
  \param[out] out_latency_in_msec Retrieved latency in milliseconds.

  \apilevel 7

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the value.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.
  \retval MLAudioResult_OperationUnavailable Failed because operation is unavailable.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetBufferedInputLatency(MLHandle handle, float *out_latency_in_msec);

/*!
  \brief Retrieves a full buffer of audio data from a sound input.

  Standard usage is to call this function by polling or within a callback of type
  MLAudioBufferCallback registered with one of the MLAudioCreateInput... calls.
  This call returns MLAudioResult_BufferNotReady if a buffer is not available for
  reading audio data, informing the caller to wait. Once consumed, the buffer must
  be released by calling MLAudioReleaseInputBuffer.

  \apilevel 7

  \param[in] handle MLHandle of the sound input.
  \param[out] out_buf Retrieved MLAudioBuffer struct pointer to buffer for reading audio data.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the buffer.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_BufferNotReady Failed because buffer was not ready.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.
  \retval MLAudioResult_OperationUnavailable Failed because operation is unavailable.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetInputBuffer(MLHandle handle, MLAudioBuffer *out_buf);

/*!
  \brief Releases an input buffer once it has been consumed.

  After consuming a buffer retrieved by MLAudioGetInputBuffer, the buffer must be
  released using this function in order to indicate that the buffer has been consumed
  and can now be refilled.

  \apilevel 7

  \param[in] handle MLHandle of the sound input.

  \retval MLResult_Ok Successfully released the buffer.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_BufferNotReady Failed because buffer was not ready.
  \retval MLAudioResult_HandleNotFound Failed due to a missing handle.
  \retval MLAudioResult_InternalConfigError Failed due to an internal configuration error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.
  \retval MLAudioResult_OperationUnavailable Failed because operation is unavailable.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioReleaseInputBuffer(MLHandle handle);
/*! \} */

/////////////////////////////
/////////////////////////////
///       MIC MUTING.
/////////////////////////////
/////////////////////////////

/*!
  \defgroup InputMicMuting Mic Muting
  \ingroup AudioInput
  \addtogroup InputMicMuting
  \{
*/

/*!
  \brief Sets the global input mute state for all input streams.

  The global input mute applies to all input streams, including microphones, Virtual Capture
  and Mixed Capture. Any app with capture privileges can set it, and it will apply for all apps.

  \param[in] is_muted If true, capture streams will be muted globally.

  \retval MLResult_Ok Successfully set the value.
  \retval MLResult_PermissionDenied Failed due to lack of permission.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions android.permission.RECORD_AUDIO (protection level: dangerous)
*/
ML_API MLResult ML_CALL MLAudioSetMicMute(bool is_muted);

/*!
  \brief Queries the global input mute state for all input streams.

  The global input mute applies to all input streams, including microphones, Virtual Capture
  and Mixed Capture. Any app with capture privileges can set it, and it will apply for all apps.

  \apilevel 20

  \param[out] out_is_muted If true, capture streams are muted globally.

  \retval MLResult_AllocFailed Failed due to memory allocation failure.
  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the value.
  \retval MLResult_PermissionDenied Failed due to lack of permission.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions android.permission.RECORD_AUDIO (protection level: dangerous)
*/
ML_API MLResult ML_CALL MLAudioGetMicMute(bool *out_is_muted);

/*!
  \brief Registers a callback for changes to the global input mute state.

  \param[in] callback Callback function pointer.
  \param[in] context Generic data pointer passed back through the callback.

  \retval MLResult_AllocFailed Failed due to memory allocation failure.
  \retval MLResult_Ok Successfully registered the callback.
  \retval MLResult_PermissionDenied Failed due to lack of permission.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_NotImplemented Failed because feature has not been implemented yet.

  \permissions android.permission.RECORD_AUDIO (protection level: dangerous)
*/
ML_API MLResult ML_CALL MLAudioSetMicMuteCallback(MLAudioMicMuteCallback callback, void *context);
/*! \} */

/////////////////////////////
/////////////////////////////
///       ANALYSIS.
/////////////////////////////
/////////////////////////////

/*!
  \defgroup InputAnalysis Analysis
  \ingroup AudioInput
  \addtogroup InputAnalysis
  \{
*/

/*!
  \brief Starts a trait analysis of the energy contained in the mic signals.

  A trait analysis measures the characteristics of an audio stream, producing a
  single value representing the result of the analysis at a point in time. This
  function creates a new trait analysis, initializes its connection to the device
  microphones as the audio data source, and returns a handle in the 'out_handle'
  argument. The 'target' argument specifies the type of trait analysis, which implies
  the type of audio content to be analyzed. Results may be acquired either on a
  polling basis by calling MLAudioGetTraitAnalysis, or via a callback set by the
  optional 'callback' argument of this function, triggered whenever a new value
  is available.

  \apilevel 20

  \param[in] target MLAudioTraitAnalysisTarget enum specifying the type of analysis requested.
  \param[in] callback Callback function pointer.
  \param[in] context Generic data pointer passed back through the callback.
  \param[out] out_handle MLHandle to be used in subsequent calls.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully began analysis.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioBeginTraitAnalysisFromMicCapture(MLAudioTraitAnalysisTarget target, MLAudioTraitAnalysisCallback callback, void *context, MLHandle *out_handle);

/*!
  \brief Queries the current value of the trait analysis.

  \apilevel 20

  \param[in] handle MLHandle of the analysis.
  \param[out] out_value Retrieved value of trait analysis.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved the value.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_NotImpelmented return control frequencies because feature has not been implemented yet.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetTraitAnalysis(MLHandle handle, float *out_value);

/*!
  \brief Stops a trait analysis.

  \apilevel 20

  \param[in] handle MLHandle of the analysis.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully ended analysis.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioEndTraitAnalysis(MLHandle handle);

/*!
  \brief Starts a spectral analysis of the energy contained in the mic signals.

  A spectral analysis measures the characteristics of an audio stream on a
  per-frequency-band basis. This function creates a new spectral analysis, initializes
  its connection to the device microphones as the audio data source, and returns a
  handle in the 'out_handle' argument. The 'target' argument specifies the type of
  spectral analysis, which implies the type of audio content to be analyzed. Spectral
  analysis results are returned in the MLAudioSpectralAnalysis struct, which contains
  a time window of spectral analysis values. Results may be acquired either on a polling
  basis by calling MLAudioGetSpectralAnalysis, or via a callback set by the optional
  'callback' argument of this function, triggered whenever new values are available.
  Cleanup of the MLAudioSpectralAnalysis struct passed in the optional callback is
  handled by the audio system; i.e., the caller is not responsible for deallocating
  memory if the callback is used.

  \apilevel 20

  \param[in] target MLAudioSpectralAnalysisTarget enum specifying type of analysis requested.
  \param[in] callback Callback function pointer.
  \param[in] context Generic data pointer passed back through the callback.
  \param[out] out_handle MLHandle to be used in subsequent calls.

  \retval MLResult_OK Successfully began analysis.
  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioBeginSpectralAnalysisFromMicCapture(MLAudioSpectralAnalysisTarget target, MLAudioSpectralAnalysisCallback callback, void *context, MLHandle *out_handle);

/*!
  \brief Queries the current values of a spectral analysis.

  To store the values being queried, this function allocates a memory block which is pointed
  to by the 'values' field of the MLAudioSpectralAnalysis struct passed as the 'out_values'
  argument. The format of the data in this memory block can vary based on the selected
  MLAudioSpectralAnalysisTarget associated with the specified handle. The caller is
  responsible for deallocating this memory after each call to MLAudioGetSpectralAnalysis.

  \apilevel 20

  \param[in] handle MLHandle of the spectral analysis.
  \param[out] out_values MLAudioSpectralAnalysis struct to be filled with the results properties.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retrieved analysis.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLAudioResult_OperationUnavailable Failed because operation is unavailable.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioGetSpectralAnalysis(MLHandle handle, MLAudioSpectralAnalysis *out_values);

/*!
  \brief Stops a spectral analysis.

  \apilevel 20

  \param[in] handle MLHandle of the spectral analysis.

  \retval MLResult_OK Successfully stopped analysis.
  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.

  \permissions None
*/
ML_API MLResult ML_CALL MLAudioEndSpectralAnalysis(MLHandle handle);

/*! \} */
/*! \} */
/*! \} */

ML_EXTERN_C_END
