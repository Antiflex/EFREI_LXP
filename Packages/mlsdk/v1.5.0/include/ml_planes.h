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
  \addtogroup Planes
  \sharedobject perception.magicleap

  \brief APIs for the Planes system.
  \{
*/

/*! Control flags for plane queries. */
typedef enum MLPlanesQueryFlags {
  /*! Include planes whose normal is perpendicular to gravity. */
  MLPlanesQueryFlag_Vertical         = 1 << 0,
  /*! Include planes whose normal is parallel to gravity. */
  MLPlanesQueryFlag_Horizontal       = 1 << 1,
  /*! Include planes with arbitrary normals. */
  MLPlanesQueryFlag_Arbitrary        = 1 << 2,
  /*! Include all plane orientations. */
  MLPlanesQueryFlag_AllOrientations  = MLPlanesQueryFlag_Vertical |
                                       MLPlanesQueryFlag_Horizontal |
                                       MLPlanesQueryFlag_Arbitrary,
  /*!
    \brief For non-horizontal planes, setting this flag will result in the top of
    the plane rectangle being perpendicular to gravity.
  */
  MLPlanesQueryFlag_OrientToGravity  = 1 << 3,
  /*!
    \brief If this flag is set, inner planes will be returned; if it is not set,
    outer planes will be returned.
  */
  MLPlanesQueryFlag_Inner            = 1 << 4,
  /*! Include planes semantically tagged as ceiling. */
  MLPlanesQueryFlag_Semantic_Ceiling = 1 << 6,
  /*! Include planes semantically tagged as floor. */
  MLPlanesQueryFlag_Semantic_Floor   = 1 << 7,
  /*! Include planes semantically tagged as wall. */
  MLPlanesQueryFlag_Semantic_Wall    = 1 << 8,
  /*! Include all planes that are semantically tagged. */
  MLPlanesQueryFlag_Semantic_All     = MLPlanesQueryFlag_Semantic_Ceiling |
                                       MLPlanesQueryFlag_Semantic_Floor |
                                       MLPlanesQueryFlag_Semantic_Wall,
  /*!
    \brief Include polygonal planes.

      When this flag is set:

      - MLPlanesQueryGetResultsWithBoundaries returns polygons along with other
        applicable rectangular planes. MLPlanesReleaseBoundariesList MUST be
        called before the next call to MLPlanesQueryGetResultsWithBoundaries,
        otherwise UnspecifiedFailure will be returned.

      When this flag is not set:

      - MLPlanesQueryGetResultsWithBoundaries returns just rectangular planes.
      No need to call MLPlanesReleaseBoundariesList.

    \apilevel 2
  */
  MLPlanesQueryFlag_Polygons    = 1 << 9,
  /*! Ensure enum is represented as 32 bits. */
  MLPlanesQueryFlags_Ensure32Bits = 0x7FFFFFFF
} MLPlanesQueryFlags;

/*! A plane with width and height. */
typedef struct MLPlane {
  /*! Plane center. */
  MLVec3f position;
  /*! Plane rotation. */
  MLQuaternionf rotation;
  /*! Plane width. */
  float width;
  /*! Plane height. */
  float height;
  /*! Flags which describe this plane. */
  uint32_t flags;
  /*!
    \brief Plane ID. All inner planes within an outer plane will have the
    same ID (outer plane's ID). These IDs are persistent across
    plane queries unless a map merge occurs. On a map merge, IDs
    could be different.
  */
  MLHandle id;
} MLPlane;

/*!
  \brief Coplanar connected line segments representing the outer boundary of a polygon,
         an _n_-sided polygon where _n_ is the number of vertices.

  \apilevel 2
*/
typedef struct MLPolygon {
  /*! Vertices of all line segments. */
  MLVec3f *vertices;
  /*! Number of vertices. */
  uint32_t vertices_count;
} MLPolygon;

/*!
  \brief Type used to represent a region boundary on a 2D plane.

  \apilevel 2
*/
typedef struct MLPlaneBoundary {
  /*! The polygon that defines the region, the boundary vertices in MLPolygon will be in CCW order. */
  MLPolygon *polygon;
  /*! A polygon may contains multiple holes, the boundary vertices in MLPolygon will be in CW order. */
  MLPolygon *holes;
  /*! Count of the holes. */
  uint32_t holes_count;
} MLPlaneBoundary;

/*!
  \brief Type to represent multiple regions on a 2D plane.

  \apilevel 2
*/
typedef struct MLPlaneBoundaries {
  /*! Plane ID, the same value associating to the ID in #MLPlane if they belong to the same plane. */
  MLHandle id;
  /*! The boundaries in a plane. */
  MLPlaneBoundary *boundaries;
  /*! Count of boundaries. A plane may contain multiple boundaries each of which defines a region. */
  uint32_t boundaries_count;
} MLPlaneBoundaries;

/*!
  \brief Type to represent polygons of all returned planes.

  \apilevel 2
*/
typedef struct MLPlaneBoundariesList {
  uint32_t version;
  /*!
    \brief List of #MLPlaneBoundaries.

    \apilevel 2
  */
  MLPlaneBoundaries *plane_boundaries;
  /*!
    \brief Count of #MLPlaneBoundaries in the array.

    \apilevel 2
  */
  uint32_t plane_boundaries_count;
} MLPlaneBoundariesList;

/*!
  \brief Initializes an MLPlaneBoundariesList structure.
  \param[in,out] inout_boundaries_list Pointer to a #MLPlaneBoundariesList structure
                 which is initialize with default values.

  \apilevel 2
*/
ML_STATIC_INLINE void MLPlaneBoundariesListInit(MLPlaneBoundariesList *inout_boundaries_list) {
  inout_boundaries_list->version = 1;
  inout_boundaries_list->plane_boundaries = NULL;
  inout_boundaries_list->plane_boundaries_count = 0u;
}

/*!
  \brief Type used to represent a plane query.

  \apilevel 20
*/
typedef struct MLPlanesQuery {
  /*! The flags to apply to this query. */
  uint32_t flags;
  /*! The center of the bounding box which defines where planes extraction should occur. */
  MLVec3f bounds_center;
  /*! The rotation of the bounding box where planes extraction will occur. */
  MLQuaternionf bounds_rotation;
  /*!
    \brief The size of the bounding box where planes extraction will occur.
    Only planes within 10 meters of the device will be extracted.
    The maximum value is 20 meters in each direction.
    A value of (0, 0, 0) will be treated as (20, 20, 20).
  */
  MLVec3f bounds_extents;
  /*!
    \brief The maximum number of results that should be returned. This is also
    the minimum expected size of the array of results passed to the
    MLPlanesGetResult function.
    In the case where the number of rectangular planes exceed this value, only the largest max_results
    planes will be returned. This can cause the number of polygons returned to be smaller than
    max_results, as there can be multiple inner planes per planar surface but only one polygon, and
    if the rectangular plane of a planar surface is not being returned because max_results have been
    reached, the corresponding polygon won't be returned.
  */
  uint32_t max_results;
  /*!
    \brief The minimum area (in squared meters) of planes to be returned. This value
    cannot be lower than 0.04 (lower values will be capped to this minimum).
    A good default value is 0.25.
  */
  float min_plane_area;
} MLPlanesQuery;

/*!
  \brief Creates a planes tracker.
  \param[out] out_handle A pointer to an #MLHandle which will contain the handle to the planes tracker.
              If this operation fails, out_handle will be #ML_INVALID_HANDLE.

  \retval MLResult_InvalidParam Failed to create planes tracker due to an invalid input parameter.
  \retval MLResult_Ok Successfully created planes tracker.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.
  \retval MLResult_PermissionDenied The application lacks permission.
  \retval MLResult_UnspecifiedFailure Failed to create planes tracker due to an unknown reason.

  \permissions com.magicleap.permission.SPATIAL_MAPPING (protection level: dangerous)
*/
ML_API MLResult ML_CALL MLPlanesCreate(MLHandle *out_handle);

/*!
  \brief Destroys a planes tracker.

  \param[in] planes_tracker #MLHandle to planes tracker to destroy.

  \retval MLResult_Ok Successfully destroyed planes tracker.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.

  \permissions None
*/
ML_API MLResult ML_CALL MLPlanesDestroy(MLHandle planes_tracker);

/*!
  \brief Initiates a plane query.
  One of the following flags must be set for the query to be considered valid:
    - MLPlanesQueryFlag_Vertical flag.
    - MLPlanesQueryFlag_Horizontal flag.
    - MLPlanesQueryFlag_Arbitrary flag.
    - MLPlanesQueryFlag_Semantic_Ceiling flag.
    - MLPlanesQueryFlag_Semantic_Floor flag.
    - MLPlanesQueryFlag_Semantic_Wall flag.

  \apilevel 20

  \param[in] planes_tracker Handle produced by MLPlanesCreate().
  \param[in] query Pointer to #MLPlanesQuery structure containing query parameters.
  \param[out] out_handle A pointer to an #MLHandle which will contain the handle to the query.
              If this operation fails, out_handle will be #ML_INVALID_HANDLE.

  \retval MLResult_InvalidParam Failed to initiate plane query due to an invalid input parameter.
  \retval MLResult_Ok Successfully initiated plane query.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.

  \permissions None
*/
ML_API MLResult ML_CALL MLPlanesQueryBegin(MLHandle planes_tracker, const MLPlanesQuery *query, MLHandle *out_handle);

/*!
  \brief Gets the result of a plane query with boundaries on each plane.
  After this function has returned successfully, the handle is invalid and should be discarded.
  Also check MLPlanesQueryFlag_Polygons description for this API's further behavior.

  \apilevel 2

  \param[in] planes_tracker Handle produced by MLPlanesCreate().
  \param[in] planes_query Handle produced by MLPlanesQueryBegin().
  \param[out] out_results An array of #MLPlane structures.
  \param[out] out_num_results The count of results pointed to by out_results.
  \param[out] out_boundaries A pointer to #MLPlaneBoundariesList for the returned polygons.
              If out_boundaries is NULL, the function call will not return any polygons,
              otherwise *out_boundaries must be zero initialized.

  \retval MLResult_Ok Successfully completed query.
  \retval MLResult_Pending Query completion is pending. This is not a failure.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.
  \retval MLResult_Timeout Query timed out due to unknown reason. Make a new query.
  \retval MLResult_UnspecifiedFailure Failed to complete query due to an unknown error.

  \permissions None
*/
ML_API MLResult ML_CALL MLPlanesQueryGetResultsWithBoundaries(MLHandle planes_tracker, MLHandle planes_query, MLPlane *out_results, uint32_t *out_num_results, MLPlaneBoundariesList *out_boundaries);

/*!
  \brief Releases the polygons data owned by the #MLPlaneBoundariesList.
  Also, check MLPlanesQueryFlag_Polygons description for this API's further behavior.

  \apilevel 2

  \param[in] planes_tracker Handle produced by MLPlanesCreate().
  \param[in] plane_boundaries Polygons pointer to the #MLPlaneBoundariessList.

  \retval MLResult_InvalidParam Failed to release memory due to an invalid input parameter.
  \retval MLResult_Ok Successfully released memory.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.

  \permissions None
*/
ML_API MLResult ML_CALL MLPlanesReleaseBoundariesList(MLHandle planes_tracker, MLPlaneBoundariesList *plane_boundaries);

/*! \} */

ML_EXTERN_C_END
