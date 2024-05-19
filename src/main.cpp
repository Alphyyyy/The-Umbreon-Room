#include <Geode/Geode.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include "UmbreonLayer.h"
using namespace geode::prelude;


class $modify(MyLayer, CreatorLayer) {
    void onMyButton(CCObject* obj) {
        CCScene* scene = UmbreonLayer::scene();
        auto transition = CCTransitionFade::create(0.5f, scene);
		CCDirector::sharedDirector()->pushScene(transition);
    }
    bool init() {
        
        if (!CreatorLayer::init()) return false;
        auto menu = this->getChildByID("bottom-left-menu");
        auto spr = CCSprite::create("ModBreButton.png"_spr);
        auto button = CCMenuItemSpriteExtra::create(
            spr, this,
            menu_selector(MyLayer::onMyButton));
        button->setID("bre-button"_spr);

		auto winSize = CCDirector::sharedDirector()->getWinSize();
		
		if(auto menu = this->getChildByID("bottom-menu")){
			menu->addChild(button);
			menu->updateLayout();
		}
        menu->addChild(button);
		menu->setZOrder(3);
        menu->updateLayout();
        this->addChild(menu);

        return true;
    }
    
    
};