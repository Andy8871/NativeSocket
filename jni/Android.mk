LOCAL_PATH := $(call my-dir)

####################################### ±‡“Îclient.so begin ##################################
include $(CLEAR_VARS)
LOCAL_MODULE    := client 
LOCAL_SRC_FILES := ./NativeClient.cpp
LOCAL_LDLIBS := -llog
LOCAL_LDLIBS += -landroid
#ø™∆Ù±‡“Î∆˜µƒ“Ï≥£≤∂ªÒ
LOCAL_CPPFLAGS := -fexceptions

include $(BUILD_SHARED_LIBRARY)
####################################### ±‡“Îclient.so end #####################################

####################################### ±‡“ÎDiagnose.so begin ##################################
include $(CLEAR_VARS)
LOCAL_MODULE    := Diagnose 
LOCAL_SRC_FILES := ./Diagnose.cpp, CommWithDisplayBase.cpp
LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_LDLIBS := -llog
LOCAL_LDLIBS += -landroid
#ø™∆Ù±‡“Î∆˜µƒ“Ï≥£≤∂ªÒ
LOCAL_CPPFLAGS := -fexceptions

include $(BUILD_SHARED_LIBRARY)
####################################### ±‡“ÎDiagnose.so end #####################################