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

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#if defined(_MSC_VER) && _MSC_VER
#ifdef ML_EXPORT
#define ML_API __declspec(dllexport)
#else
#define ML_API __declspec(dllimport)
#endif
#define ML_CALL __cdecl
#if defined(ML_NO_DEPRECATION_WARNING)
#define ML_DEPRECATED_MSG(msg)
#define ML_DEPRECATED
#if !defined(ML_NO_DEPRECATION_DISABLED_MSG)
#pragma message("Magic Leap C SDK - API deprecation warnings are disabled.")
#endif
#else
#define ML_DEPRECATED_MSG(msg) __declspec(deprecated(msg))
#define ML_DEPRECATED __declspec(deprecated)
#endif
#define ML_STATIC_INLINE __inline
#else
#define ML_API
#define ML_CALL
#if defined(ML_NO_DEPRECATION_WARNING)
#define ML_DEPRECATED_MSG(msg)
#define ML_DEPRECATED
#if !defined(ML_NO_DEPRECATION_DISABLED_MSG)
#pragma message("Magic Leap C SDK - API deprecation warnings are disabled.")
#endif
#else
#define ML_DEPRECATED_MSG(msg) __attribute__((deprecated(msg)))
#define ML_DEPRECATED __attribute__((deprecated))
#endif
#define ML_STATIC_INLINE static inline
#endif

#ifdef __cplusplus
#define ML_EXTERN_C_BEGIN extern "C" {
#define ML_EXTERN_C_END }
#else
#define ML_EXTERN_C_BEGIN
#define ML_EXTERN_C_END
#endif

#include "ml_coordinate_frame_uid.h"
#include "ml_version.h"

ML_EXTERN_C_BEGIN

/*!
  \addtogroup Platform
  \sharedobject capi.magicleap
  \brief APIs for information regarding the platform.
  \{
*/



/*!
  \brief Integer handle type used to reference many things returned by the API, instead of
  returning pointers directly. Use MLHandleIsValid() to check if a handle is valid or not.
*/
typedef uint64_t MLHandle;

enum {
  /*! Value of an invalid handle. To test if a handle is invalid use MLHandleIsValid(). */
  ML_INVALID_HANDLE = 0xFFFFFFFFFFFFFFFF
};

enum {
  /*! Maximum character length of MLVersion build ID. */
  MLVersion_BuildIdMaxLength = 128
};

/*! SDK version: '[major].[minor].[revision].[build_id]'. */
typedef struct MLVersion {
  /*! Major version. */
  uint32_t major;
  /*! Minor version. */
  uint32_t minor;
  /*! Revision. */
  uint32_t revision;
  /*! Build ID. */
  char build_id[MLVersion_BuildIdMaxLength];
} MLVersion;

/*! Macro to set a the prefix bytes of an API specific MLResult code. */
#define MLRESULT_PREFIX(val) (val << 16)

enum {
  /*! Defines the prefix for global MLResult codes. */
  MLResultAPIPrefix_Global = MLRESULT_PREFIX(0),
};

/*! Global MLResult codes that any API can optionally return. */
typedef enum MLResultGlobal {
  /*! Operation completed successfully. */
  MLResult_Ok = MLResultAPIPrefix_Global,
  /*! Asynchronous operation has not completed. */
  MLResult_Pending,
  /*! Operation has timed out. */
  MLResult_Timeout,
  /*! Request to lock a shared resource that is already locked. */
  MLResult_Locked,
  /*! Operation failed due to an unspecified internal error. */
  MLResult_UnspecifiedFailure,
  /*! Operation failed due to an invalid parameter being supplied. */
  MLResult_InvalidParam,
  /*! Operation failed because memory failed to be allocated. */
  MLResult_AllocFailed,
  /*! Operation failed because a required permission has not been granted. */
  MLResult_PermissionDenied,
  /*! Operation failed because it is not currently implemented. */
  MLResult_NotImplemented,
  /*! Operation failed because the client count exceeded the number of clients available. */
  MLResult_ClientLimitExceeded,
  /*! Operation failed because the requested pose is not available. */
  MLResult_PoseNotFound,
  /*! Operation failed because feature isn't supported on current device version. */
  MLResult_IncompatibleSKU,
  /*! Operation failed because the Perception System was not started. */
  MLResult_PerceptionSystemNotStarted,
  /*! Operation failed because it has been invoked at the wrong time. */
  MLResult_IllegalState,
  /*! Operation failed because of missing/incompatible license. */
  MLResult_LicenseError,
  /*! Operation failed because the timestamp parameter was outside the expected range. */
  MLResult_InvalidTimestamp,
  /*! Operation failed because the user authentication did not pass. */
  MLResult_Unauthenticated,
  /*! Ensure enum is represented as 32 bits. */
  MLResult_Ensure32Bits = 0x7FFFFFFF
} MLResultGlobal;

/*! MLResult type that all functions in the APIs return. */
typedef int32_t MLResult;

/*!
  \brief Returns an ASCII string for MLResultGlobal codes.
  \param[in] result_code The input MLResult enum from ML API functions.
  \return ASCII string containing readable version of result code.

  \permissions None
*/
ML_STATIC_INLINE const char* ML_CALL MLGetResultString(MLResult result_code) {
  switch (result_code) {
    case MLResult_Ok: return "MLResult_Ok";
    case MLResult_Pending: return "MLResult_Pending";
    case MLResult_Timeout: return "MLResult_Timeout";
    case MLResult_Locked: return "MLResult_Locked";
    case MLResult_UnspecifiedFailure: return "MLResult_UnspecifiedFailure";
    case MLResult_InvalidParam: return "MLResult_InvalidParam";
    case MLResult_AllocFailed: return "MLResult_AllocFailed";
    case MLResult_PermissionDenied: return "MLResult_PermissionDenied";
    case MLResult_NotImplemented: return "MLResult_NotImplemented";
    case MLResult_ClientLimitExceeded: return "MLResult_ClientLimitExceeded";
    case MLResult_IncompatibleSKU: return "MLResult_IncompatibleSKU";
    case MLResult_PoseNotFound: return "MLResult_PoseNotFound";
    case MLResult_PerceptionSystemNotStarted: return "MLResult_PerceptionSystemNotStarted";
    case MLResult_IllegalState: return "MLResult_IllegalState";
    case MLResult_LicenseError: return "MLResult_LicenseError";
    case MLResult_InvalidTimestamp: return "MLResult_InvalidTimestamp";
    case MLResult_Unauthenticated: return "MLResult_Unauthenticated";
    default: return "Unknown";
  }
}

/*!
  \brief Returns an ASCII string for MLResult codes.

  \apilevel 20

  \param[in] result_code The input MLResult enum from ML API functions.
  \return ASCII string containing readable version of result code.

  \permissions None
*/
ML_API  const char* ML_CALL MLGlobalGetResultString(MLResult result_code);

/*!
  \brief Check if a handle is valid.
  \param[in] handle The handle to check.
  \return \c true if the handle is valid.

  \permissions None
*/
ML_STATIC_INLINE bool MLHandleIsValid(MLHandle handle) {
  return handle != ML_INVALID_HANDLE;
}

/*!
  \brief Get SDK version as c-style string.
  \return SDK version as c-style string.

  \permissions None
*/
ML_STATIC_INLINE const char *ML_CALL MLGetVersionName() {
  return MLSDK_VERSION_NAME;
}

/*!
  \brief Get SDK version as a struct with major, minor, revision, and build_id.
  \return SDK version as a struct.

  \permissions None
*/
ML_STATIC_INLINE MLVersion MLGetVersion() {
  MLVersion version = {MLSDK_VERSION_MAJOR,
                       MLSDK_VERSION_MINOR,
                       MLSDK_VERSION_REVISION,
                       MLSDK_VERSION_BUILD_ID};
  return version;
}

/*! \} */

ML_EXTERN_C_END
