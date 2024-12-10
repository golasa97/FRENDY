CXX = g++
#CXX = icc
TOP_DIR = ../../frendy
#CXXFLAGS = -Wall -O2 -MMD -MP -I${TOP_DIR}/
CXXFLAGS = -Wall -O2 -fopenmp -MMD -MP -I${TOP_DIR}/ -std=c++11
#CXXFLAGS = -fsanitize=address -Wall -O2 -MMD -MP -I${TOP_DIR}/

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
${TOP_DIR}/EndfUtils/GendfParser \
${TOP_DIR}/EndfUtils/GendfWriter \
${TOP_DIR}/MathUtils \
${TOP_DIR}/FrendyUtils \
${TOP_DIR}/NjoyUtils \
${TOP_DIR}/NuclearDataUtils \
${TOP_DIR}/NuclearDataUtils/CovarianceDataContainer \
${TOP_DIR}/NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceData \
${TOP_DIR}/NuclearDataUtils/NuclearDataCalculator \
${TOP_DIR}/NuclearDataUtils/NuclearDataContainer \
${TOP_DIR}/NuclearDataUtils/NuclearDataContainer/ResonanceData \
${TOP_DIR}/NuclearDataUtils/OtherUtils \
${TOP_DIR}/NuclearDataUtils/ProbabilityDataContainer \
${TOP_DIR}/ReconResonance \
${TOP_DIR}/ReconResonance/RmatrixLimited/basics \
${TOP_DIR}/ReconResonance/RmatrixLimited/endf \
${TOP_DIR}/ReconResonance/RmatrixLimited/numeric \
${TOP_DIR}/ReconResonance/RmatrixLimited/rml \
${TOP_DIR}/ReconResonance/RmatrixLimited/run \
${TOP_DIR}/ThermalScatter \
${TOP_DIR}/UnresoUtils \
${TOP_DIR}/GasProduction \
${TOP_DIR}/NuclearDataModifier \
${TOP_DIR}/MGXSUtils/FMGenerator \
${TOP_DIR}/MGXSUtils/InputUtils \
${TOP_DIR}/MGXSUtils/MatxsUtils \
${TOP_DIR}/MGXSUtils/KramUtils \
${TOP_DIR}/MGXSUtils/OtherUtils \
${TOP_DIR}/MGXSUtils/MGUtils \
${TOP_DIR}/Plotter \
${TOP_DIR}/NuclearDataProcessor \
${TOP_DIR}/../tools/frendy_parallel

SRC_DIR_CPPS := $(sort $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.cpp)))
SRCS := $(SRC_DIR_CPPS)
# SRCS := $(sort $(shell find src -name *.cpp))
OBJS := $(patsubst %.cpp,%.o_m,$(SRCS))
DEPS := $(patsubst %.cpp,%.d,$(SRCS))

AR = ar
ARFLAGS = crsv

LIB_FRENDY = libfrendy.a_m

TARGET = frendy_parallel.exe

.PHONY: all clean distclean

all: $(OBJS) $(LIB_FRENDY) $(TARGET)

%.o_m: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(LIB_FRENDY): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^
	ranlib $@

main_frendy_parallel.o_m: main_frendy_parallel.cpp

$(TARGET): main_frendy_parallel.o_m $(LIB_FRENDY)
	$(CXX) -fopenmp -o $@ $^ -L. -llapack -lblas -lboost_timer -lboost_system
	@echo "### Completed to make FRENDY (parallel) ###"

clean:
	rm -rf $(OBJS) $(DEPS) main_frendy_parallel.o_m main_frendy_parallel.d $(LIB_FRENDY)

distclean:
	rm -rf $(OBJS) $(DEPS) main_frendy_parallel.o_m main_frendy_parallel.d $(LIB_FRENDY) $(TARGET)

-include $(DEPS)

