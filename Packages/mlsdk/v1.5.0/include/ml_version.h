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

#define MLSDK_VERSION_MAJOR 1
#define MLSDK_VERSION_MINOR 5
#define MLSDK_VERSION_REVISION 0
#define MLSDK_VERSION_BUILD_ID "20231215r"
#define MLSDK_STRINGIFYX(x) MLSDK_STRINGIFY(x)
#define MLSDK_STRINGIFY(x) #x
#define MLSDK_VERSION_NAME \
  MLSDK_STRINGIFYX(MLSDK_VERSION_MAJOR) \
  "." MLSDK_STRINGIFYX(MLSDK_VERSION_MINOR) \
  "." MLSDK_STRINGIFYX(MLSDK_VERSION_REVISION) \
  "." MLSDK_VERSION_BUILD_ID
