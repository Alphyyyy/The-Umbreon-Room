#pragma once
#include <Geode/Geode.hpp>
#include <Geode/Bindings.hpp>
using namespace geode::prelude;
class UmbreonLayer : public cocos2d::CCLayer {
protected:
    virtual bool init();
    virtual void keyBackClicked();
    void onPage(cocos2d::CCObject*);
    void updateBree();
    void onBack(cocos2d::CCObject*);
    void onArtist(cocos2d::CCObject*);
    void onInfo(cocos2d::CCObject*);
public:
    int page = 1;
    std::string link = "https://www.deviantart.com/kirajayy";
    static UmbreonLayer* create();
    static cocos2d::CCScene* scene();
};