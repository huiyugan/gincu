#ifndef GAPPLICATION_H
#define GAPPLICATION_H

#include "gincu/ggeometry.h"
#include "gincu/gconfiginfo.h"

#include "cpgf/gcallbacklist.h"

#include <memory>
#include <string>
#include <cstdint>

namespace gincu {

class GRenderEngine;
class GResourceManager;
class GSceneManager;
class GEvent;
class GEventQueue;
class GWorker;
class GDeviceContext;
class GRenderContext;

typedef cpgf::GCallback<void ()> FrameUpdater;

class GApplication
{
public:
	static GApplication * getInstance();

public:
	GApplication();
	virtual ~GApplication();

	GApplication(const GApplication &) = delete;
	GApplication & operator = (const GApplication &) = delete;

	void run();
	
	void finish();

	void executeWorkerTask(const cpgf::GCallback<void ()> & task);

	const GConfigInfo & getConfigInfo() const { return this->configInfo; }
	GSize getScreenSize() const;

	GSceneManager * getSceneManager() const { return this->sceneManager.get(); }
	GEventQueue * getEventQueue() const { return this->eventQueue.get(); }

	int64_t getFrameCount() const { return this->frameCount; }
	int getFrameRate() const { return this->frameRate; }
	int getRenderFrameRate() const { return this->renderFrameRate; }
	unsigned int getFrameMilliseconds() const { return this->frameMilliseconds; }
	unsigned int getRenderMilliseconds() const { return this->renderMilliseconds; }

protected:
	void setConfigInfo(const GConfigInfo & configInfo);

private:
	void initialize();
	void finalize();
	void processMainLoop();
	void processEvents();
	void onEvent(const GEvent & event);
	void doRender(GRenderContext * renderContext);

private:
	virtual void doInitialize();
	virtual void doFinalize();

private:
	GConfigInfo configInfo;

	std::unique_ptr<GDeviceContext> deviceContext;
	GRenderContext * renderContext;
	std::unique_ptr<GResourceManager> resourceManager;
	std::unique_ptr<GSceneManager> sceneManager;
	std::unique_ptr<GEventQueue> eventQueue;
	std::unique_ptr<GWorker> worker;

	bool finished;

	GSize screenSize;
	int64_t frameCount;
	int frameRate;
	int renderFrameRate;
	unsigned int frameMilliseconds;
	unsigned int renderMilliseconds;
};


} //namespace gincu

#endif
