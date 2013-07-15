// ref: http://87showmin.blogspot.tw/2009/06/java-java-native-interfacejni.html
#include <jni.h>
#include <stdio.h>
#include "HelloWorld.h"

JNIEXPORT void JNICALL
Java_HelloWorld_print(JNIEnv *env, jobject obj)
{
  printf("Hello World!\n");
  return;
}
         
