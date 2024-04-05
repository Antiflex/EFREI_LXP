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

#include "android_native_app_glue.h"

#include "android/log.h"
#include "android/looper_event_reader_writer.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "threaded_app", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "threaded_app", __VA_ARGS__))

/* For debug builds, always enable the debug traces in this library */
#ifndef NDEBUG
#  define LOGV(...)  ((void)__android_log_print(ANDROID_LOG_VERBOSE, "threaded_app", __VA_ARGS__))
#else
#  define LOGV(...)  ((void)0)
#endif

static void free_saved_state(android_app* app) {
  if (app->savedState) {
    free(app->savedState);
    app->savedState = nullptr;
    app->savedStateSize = 0;
  }
}

void android_app_pre_exec_cmd(struct android_app* app, int8_t cmd) {
  switch (cmd) {
    case APP_CMD_INPUT_CHANGED:
      LOGV("APP_CMD_INPUT_CHANGED\n");
      break;

    case APP_CMD_INIT_WINDOW:
      LOGV("APP_CMD_INIT_WINDOW\n");
      // We currently provide a dummy value for this opaque type to prevent the
      // avoid usage of ifdef's in app code when checking for this variable.
      app->window = (ANativeWindow *)1;
      break;

    case APP_CMD_TERM_WINDOW:
      LOGV("APP_CMD_TERM_WINDOW\n");
      break;

    case APP_CMD_RESUME:
    case APP_CMD_START:
    case APP_CMD_PAUSE:
    case APP_CMD_STOP:
      LOGV("activityState=%d\n", cmd);
      app->activityState = cmd;
      break;

    case APP_CMD_CONFIG_CHANGED:
      LOGV("APP_CMD_CONFIG_CHANGED\n");
      break;

    case APP_CMD_DESTROY:
      LOGV("APP_CMD_DESTROY\n");
      app->destroyRequested = 1;
      break;
  }
}

void android_app_post_exec_cmd(struct android_app* app, int8_t cmd) {
  switch (cmd) {
    case APP_CMD_TERM_WINDOW:
      LOGV("APP_CMD_TERM_WINDOW\n");
      app->window = nullptr;
      break;

    case APP_CMD_SAVE_STATE:
      LOGV("APP_CMD_SAVE_STATE\n");
      app->stateSaved = 1;
      break;

    case APP_CMD_RESUME:
      free_saved_state(app);
      break;
  }
}

int8_t android_app_read_cmd(android_app* android_app) {
  int8_t cmd;
  if (auto* reader = LooperEventReaderWriter::GetPointer(android_app->msgread)) {
    if (reader->HasEvent()) {
      cmd = reader->ReadEvent();
      switch (cmd) {
        case APP_CMD_SAVE_STATE:
          free_saved_state(android_app);
          break;
      }
      return cmd;
    } else {
      LOGE("No data on command pipe!");
    }
  } else {
    LOGE("No pointer to event reader!");
  }
  return -1;
}

static void process_cmd(android_app* app, android_poll_source* source) {
  // Unused params; kept to match the original function signature from the Android implementation
  (void)source;

  int8_t cmd = android_app_read_cmd(app);
  android_app_pre_exec_cmd(app, cmd);
  if (app->onAppCmd) {
    app->onAppCmd(app, cmd);
  }
  android_app_post_exec_cmd(app, cmd);
}

static void android_app_destroy(android_app* app) {
  LOGV("android_app_destroy!");
  free_saved_state(app);
  app->destroyed = 1;
}

static void* android_app_entry(android_app* app) {
  app->cmdPollSource.id = LOOPER_ID_MAIN;
  app->cmdPollSource.app = app;
  app->cmdPollSource.process = process_cmd;

  LooperEventReaderWriter eventReader;
  ALooper* looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
  ALooper_addFd(looper, app->msgread, LOOPER_ID_MAIN, ALOOPER_EVENT_INPUT, nullptr,
                &app->cmdPollSource);
  app->looper = looper;

  app->running = 1;

  android_main(app);

  android_app_destroy(app);
  return nullptr;
}

static android_app* android_app_create(int argc, const char** argv, const char* appInstallDir, const char* appWritableDir, const char* externalFilesDir) {
  android_app* app = new android_app{};

  app->argc = argc;
  app->argv = argv;

  app->applicationInstallDir = appInstallDir;
  app->applicationWritableDir = appWritableDir;
  app->externalFilesDir = externalFilesDir;

  // just for symmetry with ANativeActivity_finish()
  app->activity = (ANativeActivity*) app;

  LooperEventReaderWriter readerWriter;
  app->msgread = readerWriter.GetHandle();

  android_app_entry(app);

  return app;
}

void OnAppLaunchZIv2(int argc, const char** argv, const char* appInstallDir, const char* appWritableDir, const char* externalFilesDir) {
  android_app_create(argc, argv, appInstallDir, appWritableDir, externalFilesDir);
}

#ifdef _MSC_VER
#pragma comment(linker, "/export:OnAppLaunchZIv2")
#endif
