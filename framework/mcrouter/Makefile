mcrouter_PROJECT_NAME := mcrouter

mcrouter_BASE       := $(AREG_BASE)/mcrouter
mcrouter_TARGET_BIN :=
mcrouter_OUTPUT_OBJ := $(AREG_OUTPUT_OBJ)/$(mcrouter_PROJECT_NAME)

mcrouter_SRC  :=
mcrouter_OBJS := 

include $(mcrouter_BASE)/app/private/Makefile
include $(mcrouter_BASE)/tcp/private/Makefile

mcrouter_CXXFLAGS := -I$(AREG_BASE)
ifeq ($(AREG_BINARY), shared)
	mcrouter_CXXFLAGS += -DIMP_AREG_DLL
else
	mcrouter_CXXFLAGS += -DIMP_AREG_LIB
endif

mcrouter_LDFLAGS  := $(AREG_TOOL_FLAGS)
mcrouter_TARGET_BIN := $(mcrouter_PROJECT_NAME)$(AREG_BIN_EXT)

mcrouter: $(AREG_OUTPUT_BIN)/$(mcrouter_TARGET_BIN)

# define one target for each source file
$(foreach cpp, $(mcrouter_SRC), $(eval $(call obj, $(cpp), $(mcrouter_OUTPUT_OBJ), mcrouter_OBJS, $(mcrouter_CXXFLAGS))))

DEPS = $(mcrouter_OBJS:%.o=%.d)
-include $(DEPS)

$(AREG_OUTPUT_BIN)/$(mcrouter_TARGET_BIN): $(areg_TARGET_PATH) $(mcrouter_OBJS) $(AREG_DEPEND)
	@echo "Linking mcrouter ..."
	@mkdir -p $(dir $@)
	$(AREG_TOOLCHAIN) $(CXXFLAGS) $(mcrouter_CXXFLAGS) $(mcrouter_OBJS) -o $@ $(mcrouter_LDFLAGS)
