// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
//
// Copyright (c) 202x Magic Leap, Inc. (COMPANY) All Rights Reserved.
// Magic Leap, Inc. Confidential and Proprietary
//
// NOTICE: All information contained herein is, and remains the property
// of COMPANY. The intellectual and technical concepts contained herein
// are proprietary to COMPANY and may be covered by U.S. and Foreign
// Patents, patents in process, and are protected by trade secret or
// copyright law. Dissemination of this information or reproduction of
// this material is strictly forbidden unless prior written permission is
// obtained from COMPANY. Access to the source code contained herein is
// hereby forbidden to anyone except current COMPANY employees, managers
// or contractors who have executed Confidentiality and Non-disclosure
// agreements explicitly covering such access.
//
// The copyright notice above does not evidence any actual or intended
// publication or disclosure of this source code, which includes
// information that is confidential and/or proprietary, and is a trade
// secret, of COMPANY. ANY REPRODUCTION, MODIFICATION, DISTRIBUTION,
// PUBLIC PERFORMANCE, OR PUBLIC DISPLAY OF OR THROUGH USE OF THIS
// SOURCE CODE WITHOUT THE EXPRESS WRITTEN CONSENT OF COMPANY IS
// STRICTLY PROHIBITED, AND IN VIOLATION OF APPLICABLE LAWS AND
// INTERNATIONAL TREATIES. THE RECEIPT OR POSSESSION OF THIS SOURCE
// CODE AND/OR RELATED INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS
// TO REPRODUCE, DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE,
// USE, OR SELL ANYTHING THAT IT MAY DESCRIBE, IN WHOLE OR IN PART.
//
// %COPYRIGHT_END%
// --------------------------------------------------------------------
// %BANNER_END%

/**
 * A convenience class that allows reading/ writing of events through the
 * Android looper API.
 *
 * The GetHandle() method is a replacement for the file descriptor argument
 * that is passed to the looper APIs.
 *
 * Intended to be used by applications that are targeting Zero Iteration.
 */

#pragma once

#include "zi_sdk_api.h"

#include <memory>
#include <unordered_map>

class LooperEventReaderWriter {
public:
  ZI_API LooperEventReaderWriter();
  ZI_API ~LooperEventReaderWriter();

  ZI_API int GetHandle() const;
  ZI_API static LooperEventReaderWriter* GetPointer(int handle);

  ZI_API bool HasEvent() const;
  ZI_API int ReadEvent();

  ZI_API void WriteEvent(int event);
private:
  class LooperEventReaderWriterImpl;
  std::unique_ptr<LooperEventReaderWriterImpl> impl_;
  static std::unordered_map<int, LooperEventReaderWriter *> handleToPointerMap_;
};
