# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.FireSim.Debug:
PostBuild.glfw.Debug: /Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/Debug/FireSim
PostBuild.glad.Debug: /Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/Debug/FireSim
/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/Debug/FireSim:\
	/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/external/glfw/src/Debug/libglfw3.a\
	/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/Debug/libglad.a
	/bin/rm -f /Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/Debug/FireSim


PostBuild.glad.Debug:
/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/Debug/libglad.a:
	/bin/rm -f /Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/Debug/libglad.a


PostBuild.glfw.Debug:
/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/external/glfw/src/Debug/libglfw3.a:
	/bin/rm -f /Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/external/glfw/src/Debug/libglfw3.a


PostBuild.FireSim.Release:
PostBuild.glfw.Release: /Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/Release/FireSim
PostBuild.glad.Release: /Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/Release/FireSim
/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/Release/FireSim:\
	/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/external/glfw/src/Release/libglfw3.a\
	/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/Release/libglad.a
	/bin/rm -f /Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/Release/FireSim


PostBuild.glad.Release:
/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/Release/libglad.a:
	/bin/rm -f /Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/Release/libglad.a


PostBuild.glfw.Release:
/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/external/glfw/src/Release/libglfw3.a:
	/bin/rm -f /Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/external/glfw/src/Release/libglfw3.a


PostBuild.FireSim.MinSizeRel:
PostBuild.glfw.MinSizeRel: /Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/MinSizeRel/FireSim
PostBuild.glad.MinSizeRel: /Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/MinSizeRel/FireSim
/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/MinSizeRel/FireSim:\
	/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/external/glfw/src/MinSizeRel/libglfw3.a\
	/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/MinSizeRel/libglad.a
	/bin/rm -f /Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/MinSizeRel/FireSim


PostBuild.glad.MinSizeRel:
/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/MinSizeRel/libglad.a:
	/bin/rm -f /Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/MinSizeRel/libglad.a


PostBuild.glfw.MinSizeRel:
/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/external/glfw/src/MinSizeRel/libglfw3.a:
	/bin/rm -f /Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/external/glfw/src/MinSizeRel/libglfw3.a


PostBuild.FireSim.RelWithDebInfo:
PostBuild.glfw.RelWithDebInfo: /Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/RelWithDebInfo/FireSim
PostBuild.glad.RelWithDebInfo: /Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/RelWithDebInfo/FireSim
/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/RelWithDebInfo/FireSim:\
	/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/external/glfw/src/RelWithDebInfo/libglfw3.a\
	/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/RelWithDebInfo/libglad.a
	/bin/rm -f /Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/RelWithDebInfo/FireSim


PostBuild.glad.RelWithDebInfo:
/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/RelWithDebInfo/libglad.a:
	/bin/rm -f /Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/RelWithDebInfo/libglad.a


PostBuild.glfw.RelWithDebInfo:
/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/external/glfw/src/RelWithDebInfo/libglfw3.a:
	/bin/rm -f /Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/external/glfw/src/RelWithDebInfo/libglfw3.a




# For each target create a dummy ruleso the target does not have to exist
/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/Debug/libglad.a:
/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/MinSizeRel/libglad.a:
/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/RelWithDebInfo/libglad.a:
/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/Release/libglad.a:
/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/external/glfw/src/Debug/libglfw3.a:
/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/external/glfw/src/MinSizeRel/libglfw3.a:
/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/external/glfw/src/RelWithDebInfo/libglfw3.a:
/Users/joakimwingard/Desktop/DATX02-PhysicallyBasedFire/FireSim/build/external/glfw/src/Release/libglfw3.a:
