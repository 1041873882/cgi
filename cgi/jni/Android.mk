LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libmisc
LOCAL_SRC_FILES := libs/libmisc.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libtinyxml
LOCAL_SRC_FILES := libs/libtinyxml.a
include $(PREBUILT_STATIC_LIBRARY)

# main.cgi
include $(LOCAL_PATH)/cgi.mk
LOCAL_SRC_FILES := $(LOCAL_HTTP_SRC) obj/main.cpp
LOCAL_MODULE := main.cgi
include $(BUILD_EXECUTABLE)

# menu.cgi
include $(LOCAL_PATH)/cgi.mk
LOCAL_MODULE := menu.cgi
LOCAL_SRC_FILES := $(LOCAL_HTTP_SRC) obj/menu.cpp
include $(BUILD_EXECUTABLE)

# logout.cgi
include $(LOCAL_PATH)/cgi.mk
LOCAL_MODULE := logout.cgi
LOCAL_SRC_FILES := $(LOCAL_HTTP_SRC) obj/logout.cpp
include $(BUILD_EXECUTABLE)

# voip.cgi
include $(LOCAL_PATH)/cgi.mk
LOCAL_MODULE := voip.cgi
LOCAL_SRC_FILES := $(LOCAL_HTTP_SRC) obj/voip.cpp
include $(BUILD_EXECUTABLE)

# network.cgi
include $(LOCAL_PATH)/cgi.mk
LOCAL_MODULE := network.cgi
LOCAL_SRC_FILES := $(LOCAL_HTTP_SRC) obj/network.cpp
include $(BUILD_EXECUTABLE)

# room.cgi
include $(LOCAL_PATH)/cgi.mk
LOCAL_MODULE := room.cgi
LOCAL_SRC_FILES := $(LOCAL_HTTP_SRC) obj/room.cpp
include $(BUILD_EXECUTABLE)

# ipc.cgi
include $(LOCAL_PATH)/cgi.mk
LOCAL_MODULE := ipc.cgi
LOCAL_SRC_FILES := $(LOCAL_HTTP_SRC) obj/ipc.cpp
include $(BUILD_EXECUTABLE)

# advanced2.cgi
include $(LOCAL_PATH)/cgi.mk
LOCAL_MODULE := advanced2.cgi
LOCAL_SRC_FILES := $(LOCAL_HTTP_SRC) obj/advanced2.cpp
include $(BUILD_EXECUTABLE)

# jsapi.cgi
include $(LOCAL_PATH)/cgi.mk
LOCAL_MODULE := jsapi.cgi
LOCAL_SRC_FILES := $(LOCAL_HTTP_SRC) jsapi.cpp
include $(BUILD_EXECUTABLE)

# other.cgi
include $(LOCAL_PATH)/cgi.mk
LOCAL_MODULE := other.cgi
LOCAL_SRC_FILES := $(LOCAL_HTTP_SRC) obj/other.cpp
include $(BUILD_EXECUTABLE)

# advanced.cgi
include $(LOCAL_PATH)/cgi.mk
LOCAL_MODULE := advanced.cgi
LOCAL_SRC_FILES := $(LOCAL_HTTP_SRC) obj/advanced.cpp
include $(BUILD_EXECUTABLE)

# settime.cgi
include $(LOCAL_PATH)/cgi.mk
LOCAL_MODULE := time.cgi
LOCAL_SRC_FILES := $(LOCAL_HTTP_SRC) obj/time.cpp
include $(BUILD_EXECUTABLE)

# capture.cgi
include $(LOCAL_PATH)/cgi.mk
LOCAL_MODULE := capture.cgi
LOCAL_SRC_FILES := $(LOCAL_HTTP_SRC) obj/capture.cpp
include $(BUILD_EXECUTABLE)

# calllogs.cgi
include $(LOCAL_PATH)/cgi.mk
LOCAL_MODULE := calllogs.cgi
LOCAL_SRC_FILES := $(LOCAL_HTTP_SRC) obj/calllogs.cpp
include $(BUILD_EXECUTABLE)


