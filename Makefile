# main Makefile

make:
	@cd main && $(MAKE)
	@cd sender && $(MAKE)
	@cd receiver && $(MAKE)

debug:
	@cd main && $(MAKE) debug
	@cd sender && $(MAKE) debug
	@cd receiver && $(MAKE) debug

clean:
	@cd main && $(MAKE) clean
	@cd sender && $(MAKE) clean
	@cd receiver && $(MAKE) clean