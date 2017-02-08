#include "gincu/gapplication.h"
#include "gincu/grenderengine.h"
#include "gincu/gresourcemanager.h"
#include "gincu/geventprocessor.h"
#include "gincu/gscenemanager.h"
#include "gincu/gheappool.h"
#include "gincu/gutil.h"
#include "gincu/glog.h"

#include "cpgf/tween/gtweenlist.h"

#include <chrono>
#include <thread>

namespace gincu {

namespace {
	GApplication * instance = nullptr;
}

GApplication * GApplication::getInstance()
{
	return instance;
}

GApplication::GApplication()
	:
		finished(false),
		frameCount(0),
		frameRate(60),
		renderFrameRate(60),
		frameMilliseconds(1)
{
	instance = this;
}

GApplication::~GApplication()
{
}

void GApplication::run()
{
	this->initialize();
	this->processMainLoop();
	this->finalize();
}

void GApplication::finish()
{
	this->finished = true;
}

void GApplication::initialize()
{
	this->renderEngine.reset(new GRenderEngine());
	this->renderEngine->inititialize();

	this->resourceManager.reset(new GResourceManager());

	this->sceneManager.reset(new GSceneManager());
	
	this->eventProcessor.reset(new GEventProcessor(this));
	
	this->doInitialize();
}

void GApplication::finalize()
{
	this->doFinalize();
}

void GApplication::processMainLoop()
{
	const unsigned int millisecondsPerFrame = 1000 / this->configInfo.framesPerSecond;
	const unsigned int millisecondsPerRenderFrame = 1000 / this->configInfo.renderFramesPerSecond;

	this->frameCount = 0;

	unsigned int lastTweenTime = getMilliseconds();
	unsigned int lastRenderTime = 0;

	unsigned int lastFpsTime = getMilliseconds();
	int fps = 0;
	int renderFps = 0;

	unsigned int milliseconds;

	while(! this->finished && this->renderEngine->isAlive()) {
		++this->frameCount;

		const unsigned int frameBeginTime = getMilliseconds();

		this->eventProcessor->processEvents();

		this->updaterList();

		if(this->configInfo.renderFramesPerSecond < 0
			|| getMilliseconds() - lastRenderTime >= millisecondsPerRenderFrame) {
			lastRenderTime = getMilliseconds();
			this->renderEngine->render();
			
			++renderFps;
		}

		milliseconds = getMilliseconds();
		cpgf::GTweenList::getInstance()->tick((cpgf::GTweenNumber)(milliseconds - lastTweenTime));
		lastTweenTime = milliseconds;

		if(millisecondsPerFrame > 0) {
			while(getMilliseconds() < frameBeginTime + millisecondsPerFrame - 1) {
				sleepMilliseconds(1);
			}
		}

		++fps;

		milliseconds = getMilliseconds();
		this->frameMilliseconds = milliseconds - frameBeginTime;

		if(milliseconds - lastFpsTime >= 1000) {
			this->frameRate = fps;
			this->renderFrameRate = renderFps;
			lastFpsTime = milliseconds;
			fps = 0;
			renderFps = 0;

			G_LOG_VERBOSE("FPS: %d RenderFPS: %d", this->frameRate, this->renderFrameRate);
		}
	}
}

void GApplication::addUpdater(const FrameUpdater & updater)
{
	this->updaterList.add(updater);
}

void GApplication::removeUpdater(const FrameUpdater & updater)
{
	this->updaterList.remove(updater);
}

void GApplication::doInitialize()
{
}

void GApplication::doFinalize()
{
}


} //namespace gincu