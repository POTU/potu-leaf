LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/GameManager.cpp \
				   ../../Classes/GameScene.cpp \
				   ../../Classes/GB2ShapeCache-x.cpp \
				   ../../Classes/Helpers.cpp \
				   ../../Classes/StartUpScene.cpp \
				   ../../Classes/TileableWorld.cpp \
				   ../../Classes/WorldTile.cpp \
				   ../../Classes/Chlorophyll.cpp \
				   ../../Classes/EndScene.cpp \
				   ../../Classes/GlobalManager.cpp \
				   ../../Classes/MenuScene.cpp \
				   ../../Classes/Obstacle.cpp \
				   ../../Classes/PauseScene.cpp \
				   ../../Classes/Player.cpp \
				   ../../Classes/Rock.cpp \
				   ../../Classes/RotatingLog.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
