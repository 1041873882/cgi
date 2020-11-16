#!/bin/bash

./html/html2c ./html/main.html > ./jni/obj/main.cpp
./html/html2c ./html/menu.html > ./jni/obj/menu.cpp
./html/html2c ./html/logout.html > ./jni/obj/logout.cpp
./html/html2c ./html/voip.html > ./jni/obj/voip.cpp
./html/html2c ./html/network.html > ./jni/obj/network.cpp
./html/html2c ./html/room.html > ./jni/obj/room.cpp
./html/html2c ./html/ipc.html > ./jni/obj/ipc.cpp
./html/html2c ./html/advanced2.html > ./jni/obj/advanced2.cpp
./html/html2c ./html/other.html > ./jni/obj/other.cpp
./html/html2c ./html/advanced.html > ./jni/obj/advanced.cpp
./html/html2c ./html/time.html > ./jni/obj/time.cpp
./html/html2c ./html/capture.html > ./jni/obj/capture.cpp
./html/html2c ./html/calllog.html > ./jni/obj/calllog.cpp