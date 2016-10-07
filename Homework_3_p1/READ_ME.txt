#Changed the g_projectionMatrix var in GLObject.cpp file to 
g_projectionMatrix = glm::perspective(0.5f, (float)1366 / (float)720, 0.01f, 100000.f);

-this changes the resolution of the window and the viewing angle.

Please change these values in the GLObject.cpp file or use the file that I havve uploaded to see the correct appearance.