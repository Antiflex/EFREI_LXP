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
  \defgroup Common Common
  \addtogroup Common
  \brief Common APIs types.

  \{
*/

/*! 2D vector represented with X and Y floats. */
typedef struct MLVec2f {
  float x;
  float y;
} MLVec2f;

/*!
  \brief Internal structure used to simplify access of MLVec3f. Do not create
  this structure directly and always use MLVec3f instead.
*/
typedef struct MLXYZf {
  float x;
  float y;
  float z;
} MLXYZf;

/*! 3D vector represented with X, Y, and Z floats. */
typedef struct MLVec3f {
  /// \cond DEV
  union {
    MLXYZf xyz;
    float values[3];
    struct {
  /// \endcond
      float x;
      float y;
      float z;
  /// \cond DEV
    };
  };
  /// \endcond
} MLVec3f;

/*! Quaternion stored as X, Y, Z, W floats. */
typedef struct MLQuaternionf {
  /// \cond DEV
  union {
    /*! Values of the quaternions laid out as X, Y, Z, W. */
    float values[4];
    struct {
  /// \endcond
      float x;
      float y;
      float z;
      float w;
  /// \cond DEV
    };
  };
  /// \endcond
} MLQuaternionf;

/*! Information used to transform from one coordinate frame to another. */
typedef struct MLTransform {
  /*! The rotation of the coordinate frame to apply after the translation. */
  MLQuaternionf rotation;
  /*! The translation to apply to get to the coordinate frame in the proper
      location. */
  MLVec3f position;
} MLTransform;

/*! An arbitrary 4x4 matrix represented with an array of floats. */
typedef struct MLMat4f {
  float matrix_colmajor[16];
} MLMat4f;

/*! A 2D float rectangle. */
typedef struct MLRectf {
  float x;
  float y;
  float w;
  float h;
} MLRectf;

/*! A 2D integer rectangle. */
typedef struct MLRecti {
  int32_t x;
  int32_t y;
  int32_t w;
  int32_t h;
} MLRecti;

/*! Color represented by 4 unsigned bytes. */
typedef struct MLColor32 {
  /// \cond DEV
  union {
    struct {
  /// \endcond
      uint8_t a;
      uint8_t b;
      uint8_t g;
      uint8_t r;
  /// \cond DEV
    };
    uint32_t rgba;
  };
  /// \endcond
} MLColor32;

/*! Color represented by 4 floats. */
typedef struct MLColor4f {
  float r;
  float g;
  float b;
  float a;
} MLColor4f;

/*! Universally Unique Identifier. */
typedef struct MLUUID {
  /// \cond DEV
  union {
    struct {
  /// \endcond
      uint32_t time_low;
      uint16_t time_mid;
      uint16_t time_hi_and_version;
      uint8_t clock_seq_hi_and_reserved;
      uint8_t clock_seq_low;
      uint8_t node[6];
  /// \cond DEV
    };
    uint8_t data[16];
  };
  /// \endcond
} MLUUID;

/*! Represents an ML API wide timestamp in nanoseconds that is not guaranteed to be synced with any system time. */
typedef int64_t MLTime;

/*! Geometric relationship between two coordinate frames. */
typedef struct MLPose {
  /*!
    \brief 6-DoF transformation between the two coordinate frames that can be
    directly used to express source frame coordinates in destination frame
    coordinates.
  */
  MLTransform transform;
  /*!
    \brief Indicate if this pose has derivative values.
  */
  bool has_derivatives;
  /*!
    \brief The linear velocity in meters per second.
  */
  MLVec3f linear_velocity;
  /*!
    \brief The linear acceleration in meters per second squared.
  */
  MLVec3f linear_acceleration;
  /*!
    \brief Angular velocity in radians per second.
  */
  MLVec3f angular_velocity;
  /*!
    \brief Angular accleration in radians per second squared.
  */
  MLVec3f angular_acceleration;

  /*! Time when this relationship was measured. */
  MLTime origin_time_ns;
  /*!
    \brief Time to which this relationship has been predicted.
    May be equal to origin_time_ns.
  */
  MLTime predict_time_ns;
} MLPose;

/*! \} */

ML_EXTERN_C_END
