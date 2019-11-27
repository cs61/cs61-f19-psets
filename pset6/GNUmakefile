# Default optimization level
O ?= 2

all: simpong61 pong61

WANT_TSAN = 1
-include build/rules.mk

LIBS = -lpthread -lm

%.o: %.cc $(BUILDSTAMP)
	$(call run,$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) $(O) -o $@ -c,COMPILE,$<)

simpong61: simpong61.o helpers.o
	$(call run,$(CXX) $(CXXFLAGS) $(O) -o $@ $^ $(LDFLAGS) $(LIBS),LINK $@)

pong61: pong61.o helpers.o
	$(call run,$(CXX) $(CXXFLAGS) $(O) -o $@ $^ $(LDFLAGS) $(LIBS),LINK $@)

check: always
	@if test "$(SAN)" != 1; then (echo; echo '** WARNING: Please run `make SAN=1 check` instead.'; echo) 1>&2; fi
	perl checksim.pl

clean: clean-main
clean-main:
	$(call run,rm -rf pong61 *.o *~ *.bak core *.core,CLEAN)
	$(call run,rm -rf out *.dSYM $(DEPSDIR))

.PRECIOUS: %.o
.PHONY: all clean clean-main clean-hook distclean run check check-% prepare-check
