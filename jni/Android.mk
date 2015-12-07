LOCAL_PATH := $(call my-dir)

####################################### ����client.so begin ##################################
include $(CLEAR_VARS)
LOCAL_MODULE    := client 
LOCAL_SRC_FILES := ./NativeClient.cpp
LOCAL_LDLIBS := -llog
LOCAL_LDLIBS += -landroid
#�������������쳣����
LOCAL_CPPFLAGS := -fexceptions

include $(BUILD_SHARED_LIBRARY)
####################################### ����client.so end #####################################

####################################### ����Diagnose.so begin ##################################
include $(CLEAR_VARS)
LOCAL_MODULE    := Diagnose 
LOCAL_SRC_FILES := ./Diagnose.cpp, CommWithDisplayBase.cpp
LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_LDLIBS := -llog
LOCAL_LDLIBS += -landroid
#�������������쳣����
LOCAL_CPPFLAGS := -fexceptions

include $(BUILD_SHARED_LIBRARY)
####################################### ����Diagnose.so end #####################################