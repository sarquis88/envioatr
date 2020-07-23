make:
	cd main && $(MAKE)
	cd sender && $(MAKE)
	cd receiver && $(MAKE)

clean:
	cd main && $(MAKE) clean
	cd sender && $(MAKE) clean
	cd receiver && $(MAKE) clean