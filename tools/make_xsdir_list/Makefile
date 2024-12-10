CXX = g++
#CXX = icc
TOP_DIR  = ../../frendy
CXXFLAGS = -Wall -O2 -MMD -MP -I${TOP_DIR}/ -std=c++11

SRC_DIR = \
${TOP_DIR}/CommonUtils \
${TOP_DIR}/TabUtils \
${TOP_DIR}/ContinuousEnergyXSUtils/AceDataCompare \
${TOP_DIR}/ContinuousEnergyXSUtils/AceDataGenerator \
${TOP_DIR}/ContinuousEnergyXSUtils/AceDataObject \
${TOP_DIR}/ContinuousEnergyXSUtils/AceDataParser \
${TOP_DIR}/ContinuousEnergyXSUtils/AceDataWriter \
${TOP_DIR}/ContinuousEnergyXSUtils/OtherUtils \
${TOP_DIR}/DopplerBroadening \
${TOP_DIR}/EndfUtils/Endf6Converter \
${TOP_DIR}/EndfUtils/Endf6Parser \
${TOP_DIR}/EndfUtils/Endf6Writer \
${TOP_DIR}/EndfUtils/EndfFileReader \
${TOP_DIR}/EndfUtils/EndfFileWriter \
${TOP_DIR}/EndfUtils/MFxxMTyyyConverter \
${TOP_DIR}/EndfUtils/MFxxMTyyyConverter/ResonanceData \
${TOP_DIR}/EndfUtils/MFxxMTyyyParser \
${TOP_DIR}/EndfUtils/MFxxMTyyyWriter \
${TOP_DIR}/EndfUtils/OtherUtils \
${TOP_DIR}/MathUtils \
${TOP_DIR}/FrendyUtils \
${TOP_DIR}/NjoyUtils \
${TOP_DIR}/NuclearDataProcessor \
${TOP_DIR}/NuclearDataUtils \
${TOP_DIR}/NuclearDataUtils/CovarianceDataContainer \
${TOP_DIR}/NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData \
${TOP_DIR}/NuclearDataUtils/NuclearDataCalculator \
${TOP_DIR}/NuclearDataUtils/NuclearDataContainer \
${TOP_DIR}/NuclearDataUtils/NuclearDataContainer/ResonanceData \
${TOP_DIR}/NuclearDataUtils/OtherUtils \
${TOP_DIR}/NuclearDataUtils/ProbabilityDataContainer \
${TOP_DIR}/ReconResonance \
${TOP_DIR}/ReconResonance/RmatrixLimited/endf \
${TOP_DIR}/ReconResonance/RmatrixLimited/numeric \
${TOP_DIR}/ReconResonance/RmatrixLimited/rml \
${TOP_DIR}/ReconResonance/RmatrixLimited/run \
${TOP_DIR}/ThermalScatter \
${TOP_DIR}/UnresoUtils \
${TOP_DIR}/GasProduction

SRC_DIR_CPPS := $(sort $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.cpp)))
SRCS := $(SRC_DIR_CPPS)
# SRCS := $(sort $(shell find src -name *.cpp))
OBJS := $(patsubst %.cpp,%.o_m,$(SRCS))
DEPS := $(patsubst %.cpp,%.d,$(SRCS))

AR = ar
ARFLAGS = crsv

LIB_FRENDY = libperturb.a_m

TARGET = make_xsdir_list.exe

.PHONY: all clean distclean

all: $(OBJS) $(LIB_FRENDY) $(TARGET)

%.o_m: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(LIB_FRENDY): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^
	ranlib $@

MakeXsdirList.o_m: MakeXsdirList.cpp

$(TARGET): MakeXsdirList.o_m $(LIB_FRENDY)
	$(CXX) -o $@ $^ -L. -llapack -lblas

clean:
	rm -rf $(OBJS) $(DEPS) MakeXsdirList.o_m MakeXsdirList.d $(LIB_FRENDY)

distclean:
	rm -rf $(OBJS) $(DEPS) MakeXsdirList.o_m MakeXsdirList.d $(LIB_FRENDY) $(TARGET)

-include $(DEPS)

