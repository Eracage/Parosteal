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
 */
#include <jni.h>
#include <errno.h>
#include <android_native_app_glue.h>

struct AndroidEngine
{
	android_app* app;

	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
	EGLConfig config;

	umath::vector2 resolution;
};

int displayInit(AndroidEngine* androidengine)
{
	const EGLint attribs[] =
	{
		EGL_RENDERABLE_TYPE, EGL_OPENGLES2_BIT,
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_ALPHA_SIZE, 8,
		EGL_NONE
	};

	EGLint attribList[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, 2
		EGL_NONE
	};

	EGLint dummy, format, numConfigs;

	androidengine->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	eglInitialize(androidengine->display,0,0);

	eglChooseConfig(androidengine->display, attribs, &androidengine->config, 1, &numConfigs);
	eglGetConfigAttrib(androidengine->display, androidengine->config, EGL_NATIVE_VISUAL_ID, &format);

	ANativeWindow_setBuffersGeomety(androidengine->app->window, 0, 0, format);

	androidengine->surface = eglCreateWindowSurface(androidengine->display, androidengine->surface, androidengine->app->window, NULL);
	androidengine->context = eglCreateContext(androidengine->display, config, NULL, attribList);

	if(eglMakeCurrent(androidengine->display, androidengine->surface, androidengine->surface, androidengine->context) == FALSE)
	{
		WriteLog("eglMakeCurrent failed");
		return -1;
	}

	eglQuerySurface(androidengine->display, androidengine->surface, EGL_WIDTH, androidengine->resolution.x);
	eglQuerySurface(androidengine->display, androidengine->surface, EGL_HEIGHT, androidengine->resolution.y);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glViewport(0,0,androidengine->resolution.x,androidengine->resolution.y);

	return 0;
}

void displayDestroy(AndroidEngine* androidengine)
{
	if(androidengine->display != EGL_NO_DISPLAY)
	{
		eglMakeCurrent(androidengine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		if(androidengine->display != EGL_NO_DISPLAY)
		{
			eglDestroyContext(engine->display, engine->context);
		}
		if (engine->surface != EGL_NO_SURFACE)
		{
			eglDestroySurface(engine->display, engine->surface);
		}
		eglTerminate(engine->display);
	}
	androidengine->display = EGL_NO_DISPLAY;
	andoridengine->context = EGL_NO_CONTEXT;
	androidengine->surface = EGL_NO_SURFACE;
}

int handle_input(android_app* app, AInputEvent* event)
{
	AndroidEngine* androidengine = (AndroidEngine*)app->userData;
	//Input should be places here
	return 0;
}

void handle_cmd(android_app* app, int cmd)
{
	AndroidEngine* androidengine = (AndroidEngine*)app->userData;

	switch (cmd)
	{
	case APP_CMD_SAVE_STATE:
		break;
	case APP_CMD_INIT_WINDOW:
		if (androidengine->app->window != NULL)
		{
			init_display(androidengine);
			draw_frame(androidengine);
		}
		break;
	case APP_CMD_TERM_WINDOW:
		terminate_display(androidengine);
		break;
	case APP_CMD_LOST_FOCUS:
		draw_frame(androidengine);
		break;
	}
}

void android_main(android_app* state)
{
	app_dummy();

	AndroidEngine* androidengine;
	memset(&androidengine, 0, sizeof(AndroidEngine));

	state->userData = &androidengine;
	state->onAppCmd = handle_cmd;
	state->onInputEvent = handle_input;

	androidengine.app = state;

	while(1)
	{
		int ident;
		int events;
		android_poll_source* source;

		while ((ident=ALooper_pollAll(0, NULL, &events,(void**)&source)) >= 0)
		{
			//Insteads of these two 'if' statement proper exit should be placed
			if (source != NULL)
			{
				source->process(state, source);
			}
			if (state->destroyRequested != 0)
			{
				terminate_display(&androidengine);
				return;
			}
		}

		if(androidengine->display == NULL)
		{
			;//Do nothing
		}
		else
		{
			//engine->Update();
		}
	}
}