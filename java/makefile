ALL_CLASS=onlyfun/caterpillar/Point2D.class UsePackage.class
all: $(ALL_CLASS)
onlyfun/caterpillar/Point2D.class: Point2D.java
	javac -d . $<
UsePackage.class: UsePackage.java
	javac -d . $<
clean:
	rm -rf $(ALL_CLASS)
