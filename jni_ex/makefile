HelloWorld.class: HelloWorld.java
	javac HelloWorld.java

HelloWorld.h: HelloWorld.java
	javah -jni HelloWorld

libHelloWorld.so: HelloWorld.cpp HelloWorld.h
	gcc -fPIC -shared -o $@ $< -I/usr/lib/jvm/java-7-openjdk-i386/include/

clean:
	rm -rf *.so *.class HelloWorld.h
