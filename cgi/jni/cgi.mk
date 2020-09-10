
include $(CLEAR_VARS)

LOCAL_HTTP_SRC := http/cgivars.cpp http/cgi_main.cpp http/eHttp.cpp

LOCAL_CFLAGS += -pie -fPIE -Wall -Wno-unused-parameter -Wno-unused-function -Wno-sign-compare -g

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/http \
	$(LOCAL_PATH)/include

LOCAL_LDFLAGS := -pie -fPIE

LOCAL_SHARED_LIBRARIES := libcutils liblog
LOCAL_STATIC_LIBRARIES := libmisc libtinyxml

LOCAL_MODULE_TAGS := optional
