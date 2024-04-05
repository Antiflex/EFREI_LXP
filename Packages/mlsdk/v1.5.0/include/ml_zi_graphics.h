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
#include "ml_types.h"
#include "ml_graphics.h"

ML_EXTERN_C_BEGIN

/*!
  \addtogroup ZI
  \sharedobject graphics.magicleap
  \brief APIs for the Zero Iteration on Host OS Platforms.
  \attention These APIs are meant to enable a better integration to ZI for
             engines running on Host OS Platforms. These APIs are not available
             on device.

  - Provides ZI support for host-specific MLGraphics APIs.
  \{
*/


#ifdef VK_VERSION_1_0
/*!
  \brief Returns a list of required VkInstance extensions.

  If out_required_extension_properties is null then the number of required extension is returned in out_extension_property_count.
  Otherwise, out_extension_property_count must point to a variable set to the number of elements in the out_required_extension_properties
  array, and on return the variable is overwritten with the number of strings actually written to out_required_extension_properties.

  \param[out] out_required_extension_properties Either null or a pointer to an array of VkExtensionProperties.
  \param[out] out_extension_property_count Is a pointer to an integer related to the number of extensions required or queried.

  \retval MLResult_InvalidParam If input parameter is invalid.
  \retval MLResult_Ok If query was successful.
  \retval MLResult_UnspecifiedFailure There was an unknown error submitting the query.

  \permissions None
*/
ML_API MLResult ML_CALL MLZIGraphicsEnumerateRequiredVkInstanceExtensions(VkExtensionProperties *out_required_extension_properties, uint32_t *out_extension_property_count);

/*!
  \brief Returns a list of required VkDevice extensions.

  If out_required_extension_properties is null then the number of required extension is returned in out_extension_property_count.
  Otherwise, out_extension_property_count must point to a variable set to the number of elements in the out_required_extension_properties
  array, and on return the variable is overwritten with the number of strings actually written to out_required_extension_properties.

  \param[out] out_required_extension_properties Either null or a pointer to an array of VkExtensionProperties.
  \param[out] out_extension_property_count Is a pointer to an integer related to the number of extensions required or queried.

  \retval MLResult_InvalidParam If input parameter is invalid.
  \retval MLResult_Ok If query was successful.
  \retval MLResult_UnspecifiedFailure There was an unknown error submitting the query.

  \permissions None
*/
ML_API MLResult ML_CALL MLZIGraphicsEnumerateRequiredVkDeviceExtensions(VkExtensionProperties *out_required_extension_properties, uint32_t *out_extension_property_count);

#endif


#ifdef __OBJC__
#import <Metal/Metal.h>

/*!
  \brief The client creation parameters for MLZIGraphicsCreateClientMTL().

  \apilevel 20
*/
typedef struct MLZIGraphicsCreateClientMTLParams {
  /*! Struct API version. */
  uint32_t version;
  /*! The graphics options for resource creation. */
  MLGraphicsOptions *options;
  /*! The Metal(R) device to use for resource creation. */
  id<MTLDevice> metal_device;
} MLZIGraphicsCreateClientMTLParams;

/*!
  \brief Initializes a MLZIGraphicsCreateClientMTLParams with the default parameters.

  \apilevel 20

  \param[in] params The object to initialize with default settings.
*/
ML_STATIC_INLINE void MLZIGraphicsCreateClientMTLParamsInit(MLZIGraphicsCreateClientMTLParams *params) {
  if (!params) return;
  params->version      = 1;
  params->options      = NULL;
  params->metal_device = NULL;
}

/*!
  \brief Create the Metal(R) graphics client for the macOS(R) platform integration only.

  Create a graphics client for use with Metal(R) API.
  The created client handle complies the usage pattern defined in ml_graphics.h on macOS(R) platform.

  \apilevel 20

  \param[in] params The graphics parameters for client creation.
  \param[out] out_graphics_client The handle to the created graphics client. Only valid if result is MLResult_Ok.

  \retval MLResult_InvalidParam Graphics Client was not created due to an invalid parameter.
  \retval MLResult_Ok Graphics Client was created successfully.
  \retval MLResult_UnspecifiedFailure Graphics Client was not created due to an unknown error.

  \permissions None
*/
ML_API MLResult ML_CALL MLZIGraphicsCreateClientMTL(const MLZIGraphicsCreateClientMTLParams *params, MLHandle *out_graphics_client);

/*!
  \brief Convert MLSurfaceFormat to Metal(R) internal format.

  \apilevel 20

  \param[in] format The MLSurfaceFormat to convert.

  \return The returned internal format.

  \permissions None
*/
ML_API MTLPixelFormat ML_CALL MLZIGraphicsMTLFormatFromMLSurfaceFormat(MLSurfaceFormat format);

/*!
  \brief Convert Metal(R) internal format to MLSurfaceFormat.

  \apilevel 20

  \param[in] format The internal format to convert.

  \return The returned MLSurfaceFormat.

  \permissions None
*/
ML_API MLSurfaceFormat ML_CALL MLZIGraphicsMLSurfaceFormatFromMTLFormat(MTLPixelFormat format);

/*!
  \brief Signal the sync object provided for each virtual camera for Metal(R) clients.

  Required for each frame, after rendering each virtual camera (or multiple if stereo rendering)
  to signal the sync object in order to inform the graphics system that the rendering for the
  camera(s) has completed. This function should be invoked in the completion callback of MTLCommandBuffer.
  All sync objects can be signaled after rendering all cameras, but results in lower fidelity in the graphics system.

  \apilevel 20

  \param[in] graphics_client The graphics client owning the sync object.
  \param[in] sync_object The sync object to be signaled.

  \retval MLResult_InvalidParam Sync Object was not signaled due to an invalid parameter.
  \retval MLResult_Ok Sync Object was signaled successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_API MLResult ML_CALL MLZIGraphicsSignalSyncObjectMTL(MLHandle graphics_client, MLHandle sync_object);

#endif

/*! \} */

ML_EXTERN_C_END
