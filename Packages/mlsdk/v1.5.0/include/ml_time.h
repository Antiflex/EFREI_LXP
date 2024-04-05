// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
// Copyright (c) 2022 Magic Leap, Inc. All Rights Reserved.
// Use of this file is governed by the Software License Agreement,
// located here: https://www.magicleap.com/software-license-agreement-ml2
// Terms and conditions applicable to third-party materials accompanying
// this distribution may also be found in the top-level NOTICE file
// appearing herein.
// %COPYRIGHT_END%
// ---------------------------------------------------------------------
// %BANNER_END%

#pragma once

#include <time.h>
#include "ml_api.h"
#include "ml_types.h"

ML_EXTERN_C_BEGIN

/*!
  \defgroup Time Time
  \addtogroup Time
  \sharedobject perception.magicleap
  \brief APIs for the MLTime.

  Please note that the MLTime data type cannot be filled with std::chrono timestamps.
  For example to generate an MLTime time from the current time you can use the code below.

  \code
  timespec time_spec{};
  clock_gettime(CLOCK_MONOTONIC, &time_spec);
  MLTime converted_ml_time{};
  if (MLResult_Ok != MLTimeConvertSystemTimeToMLTime(&time_spec, &converted_ml_time)) {
    ML_LOG_ERROR("Failed to convert to MLTime timestamp");
  }
  \endcode

  \{
*/

/*!
  \brief Converts timestamps from MLTime to system time.

  See #MLTime for more details.
  System time is equivalent to the systems monotonic clock.
  This can be used to calculate duration between two MLTime values by converting them both to a timespec
  and subtracting the subsequent values.

  \apilevel 20

  \param[in] ml_time Timestamp received from elsewhere in the ML system.
  \param[out] out_timespec_time Pointer to a converted equivalent timestamp as if received
  from clock_gettime using CLOCK_MONOTONIC.

  \retval MLResult_Ok Successfully converted timestamp.
  \retval MLResult_InvalidParam NULL passed for timespec_time.
  \retval MLResult_UnspecifiedFailure Failed to convert timestamp with unknown error.

  \permissions None
*/
ML_API MLResult ML_CALL MLTimeConvertMLTimeToSystemTime(MLTime ml_time, struct timespec *out_timespec_time);

/*!
  \brief Converts timestamps from system time to MLTime.

  See #MLTime for more details.
  System time is equivalent to the systems monotonic clock.

  \apilevel 20

  \param[in] timespec_time System clock timestamp as received from clock_gettime using CLOCK_MONOTONIC.
  \param[out] out_ml_time Pointer to system timestamp equivalent in MLTime.

  \retval MLResult_Ok Successfully converted timestamp.
  \retval MLResult_InvalidParam NULL passed for ml_time.
  \retval MLResult_UnspecifiedFailure Failed to convert timespec with unknown error.

  \permissions None
*/
ML_API MLResult ML_CALL MLTimeConvertSystemTimeToMLTime(const struct timespec *timespec_time, MLTime *out_ml_time);

/*! \} */
ML_EXTERN_C_END