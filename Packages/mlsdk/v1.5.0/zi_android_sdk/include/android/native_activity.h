/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Modifications Copyright (c) 202x Magic Leap, Inc. (COMPANY) All Rights Reserved.
 *
 * The changes here reflect the minimum set of functionality from the original
 * Android header to support Magic Leap Zero Iteration.
 */

/**
 * @addtogroup NativeActivity Native Activity
 * @{
 */

/**
 * @file native_activity.h
 */

#ifndef ANDROID_NATIVE_ACTIVITY_H
#define ANDROID_NATIVE_ACTIVITY_H

#include "zi_sdk_api.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ANativeActivity;
typedef struct ANativeActivity ANativeActivity;

/**
 * Call to cleanly shut down a ZI application.
 *
 * If not used, you must send APP_CMD_STOP and APP_CMD_DESTROY
 * events from The Lab's System Events UI.
 */
ZI_API void ANativeActivity_finish(ANativeActivity* activity);

#ifdef __cplusplus
};
#endif

#endif  // ANDROID_NATIVE_ACTIVITY_H

/** @} */
