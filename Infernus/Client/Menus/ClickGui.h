#pragma once
#include "../../Other/VComponent.h"
#include "../../Other/RenderUtils.h"

class ClickGui : public VModule {
public:
	ClickGui() : VModule::VModule("ClickGui", "Renders a UI which can be used to manage modules", 0x2D) {};
	void onRender();
	void onKey(uint64_t key, bool isDown, bool* cancel) { 
		if (key == VK_ESCAPE) {
			isEnabled = false;
		};
		*cancel = true;
	};
	void onEnable();
	void onDisable();
private:
	std::vector<VWindow*> Windows;
};

void ClickGui::onRender() {
	for (auto Window : Windows) {
		Window->render();
	};
	
	//Minecraft::GetClientInstance()->releaseMouse();
};

void ClickGui::onEnable() {
	if (Windows.empty()) {

		int indexSpace = 0;
		GuiData* Data = Minecraft::GetClientInstance()->GuiData();
		float scale = Data->ScaledResolution.x / (Data->GuiScale() * 3);
		for (auto Category : ClientHandler::GetCategories()) {
			float toRight = scale * indexSpace;

			VWindow* newWindow = new VWindow(Category->name, Vec4(toRight + 10, 100, toRight + 110, 0), 1.0f, MC_Colour(255, 110, 30), MC_Colour(50, 50, 50), MC_Colour(50, 50, 50), 1.0f, .3f);

			for (auto Module : Category->modules) {
				VWindowButton* newObject = new VWindowButton(Module->name, &Module->isEnabled);
				for (auto VObj : Module->WindowObjects) {
					newObject->addExpandedItem(VObj);
				};
				newWindow->addObject(newObject);
			};
			Windows.push_back(newWindow);
			indexSpace++;
		};
	};
	Minecraft::GetClientInstance()->releaseMouse();
};

void ClickGui::onDisable() {
	if(Minecraft::GetLocalPlayer() != nullptr) Minecraft::GetClientInstance()->grabMouse();
};