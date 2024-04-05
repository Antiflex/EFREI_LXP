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

  - These APIs support requesting and checking permissions
  from the C API rather than requiring ZI to emulate a full JNI layer.
  Programs should conditionally use these APIs when building for
  host instead of using Android APIs in order to simulate
  permissions requests and management.

  \{
*/

/*!
  \brief Start the ZI permissions system.  This must be called before other permissions calls.

  \apilevel 20

  \retval MLResult_Ok If query was successful.
  \retval MLResult_UnspecifiedFailure There was an unknown error.

  \permissions None
*/
ML_API MLResult ML_CALL MLZIPermissionsStart();

/*!
  \brief Stop the ZI permission system. Call to clean up the ZI permission system at application termination.

  \apilevel 20

  \retval MLResult_Ok If query was successful.
  \retval MLResult_UnspecifiedFailure There was an unknown error.

  \permissions None
*/
ML_API MLResult ML_CALL MLZIPermissionsStop();

/*!
  \brief Asks if the application has the given permission granted.

  \apilevel 20

  \see https://developer.android.com/training/permissions/requesting

  \param[in] permission_name The permission name.

  \retval MLResult_InvalidParam The permission_name parameter is not valid (or null).
  \retval MLResult_Ok The permission is granted.
  \retval MLResult_PermissionDenied If permission denied.
  \retval MLResult_Pending If permission request has not been resolved.
  \retval MLResult_UnspecifiedFailure There was an unknown error.

  \permissions Any
*/
ML_API MLResult ML_CALL MLZIPermissionsIsGranted(const char *permission_name);

/*!
  \brief Request the given permission (blocking if pending until user either allows or denies permission).
  Client code can poll the permission state to see if the permission was granted, denied or still pending.

  \apilevel 20

  \see https://developer.android.com/training/permissions/requesting

  \param[in] permission_name The permission name.

  \retval MLResult_InvalidParam The permission_name parameter is not valid (or null).
  \retval MLResult_Ok The query was successful.
  \retval MLResult_UnspecifiedFailure There was an unknown error.

  \permissions None
*/
ML_API MLResult ML_CALL MLZIPermissionsRequest(const char *permission_name);

ML_EXTERN_C_END
