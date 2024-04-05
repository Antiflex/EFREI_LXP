// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
// Copyright (c) 2021 Magic Leap, Inc. All Rights Reserved.
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
  \addtogroup ZI
  \sharedobject zi.magicleap
  \brief APIs for the Zero Iteration on Host OS Platforms.
  \attention These APIs are meant to enable a better integration to ZI for
             engines running on Host OS Platforms. These APIs are not available
             on device.

  - This header supports general Zero Iteation state queries.
  \{
*/

/*!
  \brief Checks to see if the Zero Iteration server is running
  and configured properly to use by a host application.

  \apilevel 20

  \param[out] out_is_configured Pointer to a bool indicating whether the ZI
              server is running and is configured properly.

  \retval MLResult_InvalidParam is_configured parameter is not valid (null).
  \retval MLResult_Ok If query was successful.
  \retval MLResult_Timeout The ZI server could not be reached.
  \retval MLResult_UnspecifiedFailure There was an unknown error submitting the query.

  \permissions None
*/

ML_API MLResult ML_CALL MLZIIsServerConfigured(bool *out_is_configured);

/*!
  \brief Set the human-readable label of the current project or library,
  to be used in UI display and diagnostic logs to indicate what is running.

  When unset, The Lab and the ZI runtime refer to a program running under
  ZI by its process / executable name.

  A label must be set before the program calls one of the MLGraphicsCreate()
  functions in order to be reflected.

  \apilevel 20

  \param[in] in_label Pointer to a C string indicating the label to use
  for the running program, or NULL or "" to reset the label.
  The string is copied.  It is interpreted as UTF-8.

  \retval MLResult_Ok If label was accepted (always).

  \permissions None
*/

ML_API MLResult ML_CALL MLZISetProgramLabel(const char *in_label);

/*! \} */

ML_EXTERN_C_END
