
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // add a label shows "Hello World"
    auto label = LabelTTF::create("Drawiders", "Arial", 50);
    label->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    /*auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);*/
    /*listener->onTouchBegan = [](Touch* touch, Event* event){
            // event->getCurrentTarget() returns the *listener's* sceneGraphPriority node.
            auto target = static_cast<Sprite*>(event->getCurrentTarget());

            //Get the position of the current point relative to the button
            Point locationInNode = target->convertToNodeSpace(touch->getLocation());
            Point locationInScreen = touch->getLocation();
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);

            //Check the click area
            if (rect.containsPoint(locationInNode)) {
                log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
                log("sprite began screen ... x = %f, y = %f", locationInScreen.x, locationInScreen.y);
                //target->setOpacity(20);
                target->setPosition(locationInScreen.x, locationInScreen.y);
                return true;
            }
            return false;
        };*/

    /*listener->onTouchMoved = [](Touch* touch, Event* event){
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            log("touch moved... delta x = %f, delta y = %f", touch->getDelta().x, touch->getDelta().y);
            target->setPosition(target->getPosition() + touch->getDelta());
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, sprite);*/

    Device::setAccelerometerEnabled(true);
    auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(HelloWorld::onAcceleration, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, sprite);

    this->addChild(sprite, 0);

    return true;
}

void HelloWorld::onAcceleration(Acceleration* acc, Event* event) {
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	target->setPosition(acc->x, acc->y);
}

void HelloWorld::menuCloseCallback(Ref* pSender) {
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
		MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
		return;
	#endif

		Director::getInstance()->end();

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
}
