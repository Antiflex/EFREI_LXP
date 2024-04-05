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
  \defgroup MediaPlayer Media Player
  \addtogroup MediaPlayer
  \sharedobject  media_ccparser.magicleap

  \warning THIS API IS DEPRECATED IN FAVOR OF STANDARD ANDROID SDK MEDIA APIs:
            https://developer.android.com/reference/android/media/MediaFormat#MIMETYPE_TEXT_CEA_608
            Developers are encouraged to use ExoPlayer for all media playback needs.

  \brief APIs for CEA608 Closed Captions Parser.

  Stringify the error codes returned by these APIs, call MLMediaResultGetString.

  \{
*/

/*!
  \brief Cea608 Caption Dimension constants.

  \apilevel 2
*/
typedef enum MLCea608CaptionDimension {
  MLCea608_CCMaxRows = 15,
  MLCea608_CCMaxCols = 32,
  MLCea608_CCMaxRowsPlus2 = 17,
  MLCea608_CCMaxColsPlus2 = 34,
  /*! Ensure enum is represented as 32 bits. */
  MLCea608_CCMaxRowsCols_Ensure32Bits = 0x7FFFFFFF
} MLCea608CaptionDimension;

/*!
  \brief Cea608 caption color code.

  \apilevel 2
*/
typedef enum MLCea608CaptionColor {
  MLCea608CaptionColor_White        = 0,
  MLCea608CaptionColor_Green        = 1,
  MLCea608CaptionColor_Blue         = 2,
  MLCea608CaptionColor_Cyan         = 3,
  MLCea608CaptionColor_Red          = 4,
  MLCea608CaptionColor_Yellow       = 5,
  MLCea608CaptionColor_Magenta      = 6,
  MLCea608CaptionColor_Invalide     = 7,
  /*! Ensure enum is represented as 32 bits. */
  MLCea608CaptionColor_Ensure32Bits = 0x7FFFFFFF
} MLCea608CaptionColor;

/*!
  \brief Cea608 caption style code.

  \apilevel 2
*/
typedef enum MLCea608CaptionStyle {
  MLCea608CaptionStyle_Italics      = 0x00000001,
  MLCea608CaptionStyle_Underline    = 0x00000002,
  MLCea608CaptionStyle_Ensure32Bits = 0x7FFFFFFF
} MLCea608CaptionStyle;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Cea608 caption style and color.

  \apilevel 2
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLCea608CaptionStyleColor {
  uint32_t style;
  uint32_t color;
} MLCea608CaptionStyleColor;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Cea608 caption preamble address code.

  \apilevel 2
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLCea608CaptionPAC {
  MLCea608CaptionStyleColor styleColor;
  uint32_t row;
  uint32_t col;
} MLCea608CaptionPAC;

enum {
  /*! NO-BREAK SPACE. */
  MLCea608_TS = 0x00A0
};

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Cea608 caption line structure.

  \apilevel 8
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLCea608CaptionLineEx {
  uint16_t display_chars[2 * MLCea608_CCMaxColsPlus2];
  MLCea608CaptionStyleColor *mid_row_styles[MLCea608_CCMaxColsPlus2];
  MLCea608CaptionPAC *pac_styles[MLCea608_CCMaxColsPlus2];
} MLCea608CaptionLineEx;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Cea608 caption segment structure.

  \apilevel 8
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLCea608CaptionSegmentEx {
  uint32_t version;
  MLCea608CaptionLineEx *cc_line[MLCea608_CCMaxRowsPlus2];
} MLCea608CaptionSegmentEx;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Create internal closed caption parser object.

  \apilevel 2

  \param[out] out_handle A pointer to an #MLHandle which will contain the handle to the CC parser.
              If this operation fails, out_handle will be #ML_INVALID_HANDLE.

  \retval MLResult_Ok Internal closed caption parser object was created successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaCCParserCreate(MLHandle *out_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Return closed caption for display.

  \apilevel 8

  \param[in] cc_handle A handle to a CC parser.
  \param[in] subtitle_data Subtitle data of MLMediaPlayerSubtitleData structure returned from
             MLMediaPlayerGetSubtitleEx function.
  \param[in] subtitle_data_size Subtitle data size of MLMediaPlayerSubtitleData structure returned
             from MLMediaPlayerGetSubtitleEx function.
  \param[out] out_cc_seg The returned MLCea608CaptionSegmentEx pointer for CC display.
              NOTE that user doesn't own this memory.

  \retval MLResult_InvalidParam one of the arguements is incorrect.
  \retval MLResult_Ok CC is ready to display and content is stored in out_ccSeg.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_NoInit CC parser was not properly built or initialized.
  \retval MLMediaGenericResult_NotEnoughData more data is required and no displayable CC for now.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaCCParserGetDisplayableEx(MLHandle cc_handle, const uint8_t *subtitle_data, int32_t subtitle_data_size, const MLCea608CaptionSegmentEx **out_cc_seg);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Release internal CC parser object.

  \apilevel 2

  \param[in] cc_handle A handle to a CC parser.

  \retval MLResult_Ok internal CC parser object was released successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaCCParserDestroy(MLHandle cc_handle);

/*!
  \brief Callback signature called when Cea608 displayable is changed.

  \apilevel 8

  \param[in] cc_handle #MLHandle is a CC Parser instance for which callback was called.
  \param[in] cc_seg #MLCea608CaptionSegmentEx conveys caption displayble to be rendered.
  \param[in] data Custom data to be returned when callback is fired.
*/
typedef void(*MLMediaCCParserDisplayChangedCallback)(MLHandle cc_handle, const MLCea608CaptionSegmentEx *cc_seg, void *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Set callback to get notified when a caption displayable has changed.

  Setting this callback saves application from handling raw subtitle data. Caption will be delivered in this callback at displayable time.

  \apilevel 8

  \param[in] cc_handle A handle to a CC parser.
  \param[in] on_display_changed_callback Function pointer for display changed callback.
            See MLMediaCCParserDisplayChangedCallback() callback typedef declaration and comments
            for explanation on expected callback parameters.
            This can be 'NULL' to unset the callback.
  \param[in] data Custom data to be returned when callback is fired.

  \retval MLResult_InvalidParam Passed \c cc_handle handle was not found.
  \retval MLResult_Ok Callback was successfully set.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaCCParserSetDisplayChangedCallback(MLHandle cc_handle, MLMediaCCParserDisplayChangedCallback on_display_changed_callback, void *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Provide Cea608 parser with subtitle raw data for parsing.
  If the callback has been set by MLMediaCCParserSetDisplayChangedCallback, then its issued to notify the CC Data.

  \apilevel 8

  \param[in] cc_handle A handle to a Cea608 parser.
  \param[in] subtitle_data Subtitle data of MLMediaPlayerSubtitleData.
  \param[in] subtitle_data_size Subtitle data size of MLMediaPlayerSubtitleData.

  \retval MLResult_InvalidParam the input parameter(s) is(are) wrong.
  \retval MLResult_Ok the operation was successful.
  \retval MLMediaGenericResult_NoInit Cea708 parser was not properly built or initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaCCParserParse(MLHandle cc_handle, const uint8_t *subtitle_data, uint32_t subtitle_data_size);

/*! \} */

ML_EXTERN_C_END
