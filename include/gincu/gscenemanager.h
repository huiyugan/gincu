#ifndef GSCENEMANAGER_H
#define GSCENEMANAGER_H

#include "cpgf/gcallback.h"

#include <memory>
#include <string>
#include <map>

namespace gincu {

class GScene;
struct GTouchEvent;

class GSceneManager
{
public:
	typedef cpgf::GCallback<GScene * ()> SceneCreator;

public:
	GSceneManager();
	~GSceneManager();

	void switchScene(GScene * scene);
	void switchScene(const std::string & sceneName, const SceneCreator & creator);

	void handleTouchEvent(const GTouchEvent & touchEvent);

	GScene * getCurrentScene() const { return currentScene.get(); }

private:
	void doSwitchScene(GScene * scene, const bool keepScene);
	void onUpdate();
	void render();

private:
	std::unique_ptr<GScene> currentScene;
	bool keepCurrentScene;
	std::map<std::string, std::unique_ptr<GScene> > sceneNameMap;
	std::unique_ptr<GScene> sceneToSwitchTo;
	std::string sceneNameToSwitchTo;
	SceneCreator sceneCreatorToSwitchTo;
};


} //namespace gincu

#endif