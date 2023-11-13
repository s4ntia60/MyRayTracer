cmake_minimum_required(VERSION 3.0)

project(ray_tracer)

# Set the source files for the main executable
set(SOURCE_FILES 
  main.cpp 
  RayTracer.h 
  RayTracer.cpp  
  MyImage.h  
  MyImage.cpp  
  RenderSettings.h  
  RenderSettings.cpp  
  readfile.h  
  readfile.cpp  
  Scene.h  
  Scene.cpp  
  Camera.h  
  Camera.cpp  
  MyTriangle.h  
  MyTriangle.cpp  
  MySphere.h  
  MySphere.cpp  
  MyObject.h  
  MyObject.cpp  
  Light.h Light.cpp  
  Ray.h  
  Ray.cpp  
  HitInfo.h  
  HitInfo.cpp  
  MyMaterial.h  
  MyMaterial.cpp  
  Transform.h  
  Transform.cpp
  )


# Add an executable
add_executable(main ${SOURCE_FILES})

# Specify where to find header files for the main project and dependencies
target_include_directories(main PRIVATE include)

# If you have external dependencies in the include directory, you can link them
# target_link_libraries(main PRIVATE FreeImage)
