LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Audio.cpp\
                   ../../Classes/BlinkTitle.cpp\
                   ../../Classes/CallAndroidMethod.cpp\
                   ../../Classes/Chinese.cpp\
                   ../../Classes/Creep.cpp\
                   ../../Classes/GameData.cpp\
                   ../../Classes/GameHUD.cpp\
                   ../../Classes/GameLayer.cpp\
                   ../../Classes/GameOverLayer.cpp\
                   ../../Classes/GameOverScene.cpp\
                   ../../Classes/GameScene.cpp\
                   ../../Classes/GameState.cpp\
                   ../../Classes/LevelSelectLayer.cpp\
                   ../../Classes/Projectile.cpp\
                   ../../Classes/StartScene.cpp\
                   ../../Classes/TopMenu.cpp\
                   ../../Classes/Tower.cpp\
                   ../../Classes/TowerDamage.cpp\
                   ../../Classes/TowerSpeed.cpp\
                   ../../Classes/Wave.cpp\
                   ../../Classes/WayPoint.cpp\                    

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
