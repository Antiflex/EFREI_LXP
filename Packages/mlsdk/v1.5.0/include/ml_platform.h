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

ML_EXTERN_C_BEGIN

/*!
  \addtogroup Platform
  \sharedobject platform.magicleap
  \brief APIs for information regarding the platform.
  \{
*/

/*! Current API Level supported by this Magic Leap SDK. */
#define ML_PLATFORM_API_LEVEL 32

/*!
  \brief Query the OS for which Platform API Level is supported.

  \param[out] out_api_level Pointer to an integer that will store the API level.

  \retval MLResult_Ok Operation completed successfully.
  \retval MLResult_InvalidParam out_platform_level was not valid (null).
  \retval MLResult_UnspecifiedError Operation failed.

  \permissions None
*/
ML_API MLResult ML_CALL MLPlatformGetAPILevel(uint32_t *out_api_level);

/*! \} */

ML_EXTERN_C_END
