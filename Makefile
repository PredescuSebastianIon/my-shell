TARGET := myshell

.PHONY: build run clean
	
build:
	$(MAKE) -C src

run: build
	$(MAKE) -C src run

clean:
	$(MAKE) -C src clean
