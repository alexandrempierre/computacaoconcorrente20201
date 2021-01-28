a: clean Lab7.class
	java Lab7 5 1 1
b: clean Lab7.class
	java Lab7 5 1 5
c: clean Lab7.class
	java Lab7 5 5 1
d: clean Lab7.class
	java Lab7 5 5 5
Lab7.class: clean
	javac Lab7.java Producer.java Consumer.java Buffer.java
clean:
	find . -maxdepth 1 -name "*.class" -delete