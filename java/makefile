ALL_CLASS=onlyfun/caterpillar/Point2D.class UsePackage.class
all: $(ALL_CLASS)
onlyfun/caterpillar/Point2D.class: Point2D.java
	javac -d . $<
UsePackage.class: UsePackage.java
	javac -d . $<


DescentPackage/HelloWorld.class: DescentPackage/HelloWorld.java
	javac DescentPackage/HelloWorld.java

HelloWorld.jar: 
	jar -cvmf manifest.txt HelloWorld.jar  DescentPackage/*.class 
	# run the jar file: java -jar ./HelloWorld.jar

clean:
	rm -rf $(ALL_CLASS) DescentPackage/*.class *.jar
