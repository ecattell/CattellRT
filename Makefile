# This is the makefile for my raytracer
# Let me know if this runs into any issues on your system
CC = g++

WARN = -Wall
CCFLAGS = -c $(WARN)

LDFLAGS =
EXECUTABLE = RaytracerDemo

SRCS = $(wildcard src/Accelerators/*.cpp src/BoundingVolumes/*.cpp src/Cameras/*.cpp src/ImagePlanes/*.cpp src/ImageUtil/*.cpp src/Lights/*.cpp src/Main/*.cpp src/Materials/*.cpp src/MathUtil/*.cpp src/Objects/*.cpp src/Ray/*.cpp src/Sequence/*.cpp src/Scene/*.cpp src/Shapes/*.cpp src/Transform/*.cpp)

OBJS  = $(addprefix obj/, $(subst /,_, $(subst src/,,$(SRCS:.cpp=.o))))

all: main

# Link
mkdirs: /bin/mkdir -p bin obj output

main: $(SRCS) $(EXECUTABLE)
	@echo "Linking $(EXECUTABLE)"

# Linker
$(EXECUTABLE): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

obj/Accelerators_%.o: src/Accelerators/%.cpp
	@echo "Building $@"
	@$(CC) $(CCFLAGS) -o $@ -c $<

obj/BoundingVolumes_%.o: src/BoundingVolumes/%.cpp
	@echo "Building $@"
	@$(CC) $(CCFLAGS) -o $@ -c $<

obj/Cameras_%.o: src/Cameras/%.cpp
	@echo "Building $@"
	@$(CC) $(CCFLAGS) -o $@ -c $<

obj/ImagePlanes_%.o: src/ImagePlanes/%.cpp
	@echo "Building $@"
	@$(CC) $(CCFLAGS) -o $@ -c $<

obj/ImageUtil_%.o: src/ImageUtil/%.cpp
	@echo "Building $@"
	@$(CC) $(CCFLAGS) -o $@ -c $<

obj/Lights_%.o: src/Lights/%.cpp
	@echo "Building $@"
	@$(CC) $(CCFLAGS) -o $@ -c $<

obj/Main_%.o: src/Main/%.cpp
	@echo "Building $@"
	@$(CC) $(CCFLAGS) -o $@ -c $<

obj/Materials_%.o: src/Materials/%.cpp
	@echo "Building $@"
	@$(CC) $(CCFLAGS) -o $@ -c $<

obj/MathUtil_%.o: src/MathUtil/%.cpp
	@echo "Building $@"
	@$(CC) $(CCFLAGS) -o $@ -c $<

obj/Objects_%.o: src/Objects/%.cpp
	@echo "Building $@"
	@$(CC) $(CCFLAGS) -o $@ -c $<

obj/Ray_%.o: src/Ray/%.cpp
	@echo "Building $@"
	@$(CC) $(CCFLAGS) -o $@ -c $<

obj/Sequence_%.o: src/Sequence/%.cpp
	@echo "Building $@"
	@$(CC) $(CCFLAGS) -o $@ -c $<

obj/Scene_%.o: src/Scene/%.cpp
	@echo "Building $@"
	@$(CC) $(CFLAGS) -o $@ -c $<

obj/Shapes_%.o: src/Shapes/%.cpp
	@echo "Building $@"
	@$(CC) $(CCFLAGS) -o $@ -c $<

obj/Transform_%.o: src/Transform/%.cpp
	@echo "Building $@"
	@$(CC) $(CCFLAGS) -o $@ -c $<

clean:
	rm -f obj/* $(EXECUTABLE)

cleanall:
	rm -f obj/* output/* $(EXECUTABLE)
