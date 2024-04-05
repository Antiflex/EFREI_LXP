// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
// Copyright (c) 2023 Magic Leap, Inc. All Rights Reserved.
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

#include <string.h>

ML_EXTERN_C_BEGIN

/*!
  \defgroup Occlusion Occlusion
  \addtogroup Occlusion
  \sharedobject perception.magicleap
  \brief APIs for the Occlusion system.
  \experimental This is an experimental API which may be modified or removed without
  any prior notice.

  - The Occlusion system is for generating a mesh representation of the near field objects,
    so they can be easily used for occlusion of in-app objects for greater immersion.

  - By default occlusion system generates the mesh representation of the near field objects at 5Hz.
    When MLOcclusionSettings::max_distance is set to be less or equal to 0.9m the mesh is generated at 30Hz.
  \{
*/

/*!
  \brief Mesh Settings for the underlying system.

  \apilevel 28
*/
typedef struct MLOcclusionSettings {
  /*! Struct version. */
  uint32_t version;
  /*!
    \brief Minimum distance in meters to occlude objects.
    Possible values ranges from 0.3m up to 7.5m.
  */
  float min_distance;
  /*!
    \brief Maximum distance in meters to occlude objects.
    Possible values ranges from 0.3m up to 7.5m.
  */
  float max_distance;
} MLOcclusionSettings;

/*!
  \brief Initialize the occlusion settings with system defaults.

  \apilevel 28

  \param[in,out] inout_settings The initial settings to be used for occlusion.

  \permissions None
*/
ML_STATIC_INLINE void MLOcclusionSettingsInit(MLOcclusionSettings *inout_settings) {
  if (inout_settings) {
    memset(inout_settings, 0, sizeof(MLOcclusionSettings));
    inout_settings->version = 1;
    inout_settings->min_distance = 0.3f;
    inout_settings->max_distance = 5.f;
  }
}

/*!
  \brief Structure for occlusion mesh data.

  \apilevel 28
*/
typedef struct MLOcclusionMesh {
  /*! Struct version. */
  uint32_t version;
  /*! The timestamp when data was generated. */
  MLTime timestamp;
  /*! The number of indices in index buffer. */
  uint32_t index_count;
  /*! The number of vertices in vertex buffer. */
  uint32_t vertex_count;
  /*!
    \brief Pointer to the vertex buffer.
    All vertices are placed w.r.t. world origin.
  */
  MLVec3f *vertex;
  /*!
    \brief Pointer to index buffer.
    In the index buffer each value is the index of a vertex in the vertex
    buffer. Three indices define one triangle. For example, the first triangle
    will have the vertices: vertex[index[0]], vertex[index[1]], vertex[index[2]].
    Index order is CW.
  */
  uint32_t *index;
} MLOcclusionMesh;

/*!
  \brief Initialize the occlusion mesh with system defaults.

  \apilevel 28

  \param[in,out] inout_mesh The initial mesh structure.

  \permissions None
*/
ML_STATIC_INLINE void MLOcclusionMeshInit(MLOcclusionMesh *inout_mesh) {
  if (inout_mesh) {
    memset(inout_mesh, 0, sizeof(MLOcclusionMesh));
    inout_mesh->version = 1;
  }
}

/*!
  \brief Structure for occlusion mesh query.

  \apilevel 28
*/
typedef struct MLOcclusionMeshQuery {
  /*! Struct version. */
  uint32_t version;
} MLOcclusionMeshQuery;

/*!
  \brief Initialize the occlusion mesh query with system defaults.

  \apilevel 28

  \param[in,out] inout_mesh_query The initial mesh query structure.

  \permissions None
*/
ML_STATIC_INLINE void MLOcclusionMeshQueryInit(MLOcclusionMeshQuery *inout_mesh_query) {
  if (inout_mesh_query) {
    memset(inout_mesh_query, 0, sizeof(MLOcclusionMeshQuery));
    inout_mesh_query->version = 1;
  }
}

/*!
  \brief Create the occlusion client.

  \apilevel 28

  \param[in] settings The initial settings to be used for occlusion.
  \param[out] out_client_handle The handle to the created client.

  \retval MLResult_InvalidParam Occlusion client was not created due to an invalid parameter.
  \retval MLResult_Ok Occlusion client was created successfully.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.
  \retval MLResult_PermissionDenied Missing required permission(s).
  \retval MLResult_UnspecifiedFailure Occlusion client was not created due to an unknown error.

  \permissions com.magicleap.permission.SPATIAL_MAPPING (protection level: dangerous)
*/
ML_API MLResult ML_CALL MLOcclusionCreateClient(const MLOcclusionSettings *settings, MLHandle *out_client_handle);

/*!
  \brief Free the client resources.

  \apilevel 28

  \param[in] client_handle The client to destroy.

  \retval MLResult_InvalidParam Occlusion client was not destroyed due to an invalid parameter.
  \retval MLResult_Ok Occlusion client was destroyed successfully.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.

  \permissions None
*/
ML_API MLResult ML_CALL MLOcclusionDestroyClient(MLHandle client_handle);

/*!
  \brief Update the occlusion settings at runtime.

  \apilevel 28

  \param[in] handle The handle to the created client.
  \param[in] settings The updated settings to be used for occlusion.

  \retval MLResult_InvalidParam Settings were not updated due to an invalid parameter.
  \retval MLResult_Ok Settings were updated successfully.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.

  \permissions None
*/
ML_API MLResult ML_CALL MLOcclusionUpdateSettings(MLHandle handle, const MLOcclusionSettings *settings);

/*!
  \brief Get the latest occlusion mesh.

  Returns #MLOcclusionMesh with its latest data. When doing consecutive calls
  and there was no mesh update, the same data will be returned. The memory is
  owned by the system. Application should copy the data it needs to cache.

  Every call to #MLOcclusionGetLatestMesh() must be followed by a matching
  call to #MLOcclusionReleaseMesh(), otherwise this method will return an error.

  \apilevel 28

  \param[in] handle The handle to the created client.
  \param[in] mesh_query The pointer to intialized #MLOcclusionMeshQuery struct.
  \param[out] out_mesh_data The pointer to intialized #MLOcclusionMesh struct.

  \retval MLResult_IllegalState Current mesh must be released before acquiring the next one.
  \retval MLResult_InvalidParam Mesh data was not returned due to an invalid parameter.
  \retval MLResult_Ok Mesh data was returned successfully.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.

  \permissions None
*/
ML_API MLResult ML_CALL MLOcclusionGetLatestMesh(MLHandle handle, const MLOcclusionMeshQuery* mesh_query, MLOcclusionMesh *out_mesh_data);

/*!
  \brief Releases specified #MLOcclusionMesh object.

  This function should be called exactly once for each call to #MLOcclusionGetLatestMesh().
  After a successful call, the contents of #mesh_data are no longer valid and should not
  be used.

  \apilevel 28

  \param[in] handle The handle to the created client.
  \param[in] mesh_data Pointer to a filled #MLOcclusionMesh struct.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Successfully released mesh data.
  \retval MLResult_UnspecifiedFailure Failed due to an internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLOcclusionReleaseMesh(MLHandle handle, MLOcclusionMesh *mesh_data);

/*! \} */

ML_EXTERN_C_END
