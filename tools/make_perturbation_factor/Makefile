CXX = g++
#CXX = icc
TOP_DIR  = ../../frendy
CXXFLAGS = -Wall -O2 -MMD -MP -I${TOP_DIR}/  -std=c++11

SRC_DIR = \
${TOP_DIR}/CommonUtils \
./

SRC_DIR_CPPS := $(sort $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.cpp)))
SRCS := $(SRC_DIR_CPPS)
OBJS := $(patsubst %.cpp,%.o_m,$(SRCS))
DEPS := $(patsubst %.cpp,%.d,$(SRCS))

AR = ar
ARFLAGS = crsv

LIB_FRENDY = libperturbfactor.a_m

TARGET = make_perturbation_factor.exe

.PHONY: all clean distclean

all: $(OBJS) $(LIB_FRENDY) $(TARGET)

%.o_m: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(LIB_FRENDY): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^
	ranlib $@

MakePerturbationFactorMain.o_m: MakePerturbationFactorMain.cpp

$(TARGET): MakePerturbationFactorMain.o_m $(LIB_FRENDY)
	$(CXX) -o $@ $^ -L. 

clean:
	rm -rf $(OBJS) $(DEPS) MakePerturbationFactorMain.o_m MakePerturbationFactorMain.d $(LIB_FRENDY)

distclean:
	rm -rf $(OBJS) $(DEPS) MakePerturbationFactorMain.o_m MakePerturbationFactorMain.d $(LIB_FRENDY) $(TARGET)

-include $(DEPS)

