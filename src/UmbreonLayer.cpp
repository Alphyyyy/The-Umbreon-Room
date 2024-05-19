#include "UmbreonLayer.h"
#include <Geode/ui/GeodeUI.hpp>
UmbreonLayer* UmbreonLayer::create() {
    auto ret = new UmbreonLayer();
    if (ret && ret->init()) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}
bool UmbreonLayer::init() {
    auto backgroundSprite = CCSprite::create("GJ_gradientBG.png");
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto size = backgroundSprite->getContentSize(); 
    
    backgroundSprite->setScaleX(winSize.width / size.width);
    backgroundSprite->setScaleY(winSize.height / size.height);
    backgroundSprite->setID("background"_spr);
    
    backgroundSprite->setAnchorPoint({0, 0});
    backgroundSprite->setColor({ 1, 31, 70 });
    
    backgroundSprite->setZOrder(-2);
    addChild(backgroundSprite);
    auto backBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_03_001.png"),
        this,
        menu_selector(UmbreonLayer::onBack)
    );
    backBtn->setID("exit-button"_spr);
    auto menuBack = CCMenu::create();
    menuBack->addChild(backBtn);
    menuBack->setPosition({25, winSize.height - 25});
    menuBack->setID("exit-menu"_spr);
    CCMenu* buttonsMenu = CCMenu::create();
    buttonsMenu->ignoreAnchorPointForPosition(false);
    auto leftBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
        this,
        menu_selector(UmbreonLayer::onPage)
    );
    leftBtn->setTag(-1);
    leftBtn->setPosition({100, winSize.height/2});
    leftBtn->setZOrder(3);
    buttonsMenu->addChild(leftBtn);

    auto rightBtn = CCMenuItemSpriteExtra::create(
        CCSprite::create("GJ_arrowright_01_001.png"_spr),
        this,
        menu_selector(UmbreonLayer::onPage)
    );
    rightBtn->setTag(1);
    rightBtn->setPosition({winSize.width - 100, winSize.height/2});
    rightBtn->setZOrder(3);
    buttonsMenu->addChild(rightBtn);
    auto infoBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png"),
        this,
        menu_selector(UmbreonLayer::onInfo)
    );
    infoBtn->setPosition({winSize.width-16,16});
    infoBtn->setZOrder(2);
    buttonsMenu->addChild(infoBtn);
    CCSprite* m_cornerBL = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    m_cornerBL->setPosition({0,0});
    m_cornerBL->setAnchorPoint({0,0});
    addChild(m_cornerBL, -1);
    m_cornerBL->setID("corner-bl"_spr);

    CCSprite* m_cornerTR = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    m_cornerTR->setPosition({winSize.width,winSize.height});
    m_cornerTR->setAnchorPoint({1,1});
    m_cornerTR->setFlipX(true);
    m_cornerTR->setFlipY(true);
    m_cornerTR->setID("corner-ur"_spr);
    addChild(m_cornerTR, -1);

    addChild(menuBack);
    addChild(buttonsMenu);

    CCSprite* titleSprite = CCSprite::create("umbreon-logo.png"_spr);
    titleSprite->setPosition({winSize.width/2, winSize.height-40});
    titleSprite->setScale(0.8f);
    titleSprite->setZOrder(1);
    addChild(titleSprite);

    auto squareSprite = CCScale9Sprite::create("GJ_square01.png",{0,0,80,80});
    squareSprite->setContentSize({300,200});
    squareSprite->setZOrder(2);
    squareSprite->setPosition({winSize.width/2,winSize.height/2 - 8.0f});
    addChild(squareSprite);

    std::string text = "Look at the boys! (Page " + std::to_string(page) +  ")";
    auto label = CCLabelBMFont::create(text.c_str(), "goldFont.fnt");
	label->setPosition(winSize.width / 2, winSize.height - 80);
    label->setScale(0.6f);
    label->setZOrder(3);
    label->setID("bre-title");
	this->addChild(label);
    updateBree();
    setKeypadEnabled(true);
    return true;
}
void UmbreonLayer::keyBackClicked() {
    CCScene* scene = CreatorLayer::scene();
    auto transition = CCTransitionFade::create(0.5f, scene);
    CCDirector::sharedDirector()->pushScene(transition);
}
void UmbreonLayer::onPage(CCObject* sender) {
    page += sender->getTag();
    if (page <= 1) {
        page = 1;
    }
    if (page > 6) {
        page = 6;
    }
    updateBree();
    static_cast<CCLabelBMFont*>(getChildByID("bre-title"))->setString(fmt::format("Look at the boys! (Page {})",page).c_str());
    
}
void UmbreonLayer::updateBree() {
    auto scale = 1.0f;
    switch (page) {
        default: {
            scale = 1.0f;
            link = "https://www.deviantart.com/kirajayy";
            break;
        }
        case 1: {
            scale = 0.5f;
            link = "https://www.deviantart.com/kirajayy";
            break;
        }
        case 2: {
            scale = 0.3f;
            link = "https://x.com/naircatt";
            break;
        }
        case 3: {
            scale = 0.5f;
            link = "https://x.com/LuckyRumiDraws";
            break;
        }
        case 4: {
            scale = 0.5f;
            link = "https://x.com/SmolSammichOwO";
            break;
        }
        case 5: {
            scale = 0.3f;
            link = "https://x.com/Nemirune";
            break;
        }
        case 6: {
            scale = 1.0f;
            link = "https://x.com/Vulpeku";
            break;
        }
    }
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    removeChildByID("twitter");
    removeChildByID("bre");
    removeChildByID("Tbtn");
    auto twMenu = CCMenu::create();
    CCSprite* bree = CCSprite::create(fmt::format("alpha.alpha/bree_{}.png",page).c_str());
    bree->setPosition({winSize.width/2,winSize.height/2 - 8.0f});
    bree->setZOrder(3);
    bree->setScale(scale);
    bree->setID("bre");
    addChild(bree);
    auto tw = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_paintBtn_001.png"),
        this,
        menu_selector(UmbreonLayer::onArtist)
    );
    twMenu->addChild(tw);
    twMenu->setZOrder(4);
    twMenu->setID("Tbtn");
    twMenu->setPosition({winSize.width/2 + 120.0f, winSize.height/2 - 80.0f});
    this->addChild(twMenu);
    auto tw_title = CCLabelBMFont::create("Artist:","bigFont.fnt");
    tw_title->setZOrder(3);
    tw_title->setPosition(
        twMenu->getPositionX(),
        twMenu->getPositionY() + 20.0f
    );
    tw_title->setScale(0.3f);
    tw_title->setID("twitter");
    addChild(tw_title);
}
void UmbreonLayer::onBack(CCObject* object) {
    keyBackClicked();
}
void UmbreonLayer::onInfo(CCObject* object) {
    FLAlertLayer::create(
        "Info",
        "This is <cy>The Umbreon Room</c>.\nYou're welcome.",
        "Thanks"
    )->show();
}
void UmbreonLayer::onArtist(CCObject* object){
    geode::createQuickPopup(
        "Open Browser",
        "Open the <cy>browser</c> to check this <co>cool artist</c>?",
        "Not yet", "Hell yeah",
        [&](auto,bool btn2) {
            if (btn2) {
                geode::utils::web::openLinkInBrowser(link);
            }
        }
    );
}
CCScene* UmbreonLayer::scene() {
    auto layer = UmbreonLayer::create();
    auto scene = CCScene::create();
    scene->addChild(layer);
    return scene;
}