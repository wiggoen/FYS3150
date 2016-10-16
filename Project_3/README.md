FYS3150/FYS4150 - Project 3 Building a model for the solar system using ordinary differential equations
============

By default, the program prints all positions every timestep to a file called positions.xyz. You can visualize this by using i.e. [Ovito](http://ovito.org/). 

Default setup:
* numTimesteps = 1000             (Number of timesteps)
* dt = 0.001                      (Distance between timesteps)
* outputmode = "Ovito"            (Use "Ovito" or "Python" for wrinting to file)
* outfilename = "positions.xyz"   (The output file name of your choice)
* integrator = "Verlet"           (Use "Verlet" or "Euler")
* system = "Sun-Earth"            (Use "Sun-Earth", "Planet-Escape", "Sun-Mercury", "Sun-Mercury-GR", "System-without-GR" or "System-with-GR")
* printEvery = 1                  (Writes every number of steps of your choice. "1" means every timestep. If you use 100000 timesteps for i.e. "System-without-GR", the output file will be approximately 50 MB. GitHub does not recommend files going over 50 MB if you want to upload them. So if you want to use more than 100000 timesteps you should consider printing i.e. every 500 timesteps.)

The systems:
* "Sun-Earth" gives the earth orbiting the sun.
* "Planet-Escape" gives a planet in distance 1 AU (like the earth) having enough velocity to ecape from the suns gravity.
* "Sun-Mercury" gives mercury orbiting the sun.
* "Sun-Mercury-GR" gives mercury orbiting the sun by calculating general relativity.
* "System-without-GR" gives the solar system (with Pluto) 
* "System-with-GR" gives the solar system (with Pluto) by calculating general relativity for Mercury.
