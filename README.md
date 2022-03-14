# Computer Graphics Projects
 
This repository contains two C++ projects that implement a simple graphic scene using OpenGL.

## Coconut Island - Coral Reef

The beauty and simplicity of watching water ripple around an island is 
mesmerizing. The goal of this project is to try to capture it as much as 
possible.

The main concept tackled in this project is the creation of realistic water
around an island.

This project was solo developed for the course of Graphics Engine for Computer Games

### Snapshots

The upper side of the coral was composed of a plane containing the water shader simulating the water effect. It created a nice effect in contrast with the beach and the corals in the reef. Some corals and dunes crossed the water showing the proper reflection when submerged.

![coral_ref_1](https://user-images.githubusercontent.com/24237112/152091477-857989b1-e576-419e-8dc8-9e251cf85b81.PNG)

The scene had a camera that allowed the user to swirl around the scene, therefore he could also look to the under side of the of the reef. This was implemented by adding a blue fog tuned to look like the camera was submerged and in adition some caustic textures were added to the beach and the corals to give the look of being underwater.

![underwater_pretty](https://user-images.githubusercontent.com/24237112/152091497-35233fc4-bacd-4946-87e7-1baba4029709.PNG)

### What I learned

This project helped me develop better time management skills. This project follow a Scrum type method of evaluation where the students would first agree on the overall goals to be achieved for that week and would be evaluated each week based on the results achieved. This meant that I would always have to be consistent since the overall end result wasn't the only piece being evaluated, our progress and development was being evaluated too.

I also learned a lot of concepts related to computer graphics needed to complete this project and implement them in C++ such as how to simulate Refraction and Reflection, create a Fresnel Effect, applying Du/Dv maps to create ripples, among others.


## Peaceful Breeze

A small scene containing a tree surrounded by procedurally generated grass which is
enhanced by post-processing features and shadows to create beautiful scenes that can
be captured

My contribution to this project was mostly around the toon shading effect and shadow-mapping.

This project was developed as between 4 students for the course of Animation and 3D Visualization 


### Snapshots

The scene was built in a way that the contrast of lighting, bloom and hdr post processing could be visible from various angles. Therefore we had a simple camera that could swirl around the scene allowing for example a good contrast of the sun's liginting and the tree's shade.

![Initial_Screen](https://user-images.githubusercontent.com/24237112/152091670-2c02a5e1-af0c-486b-a480-fd6cdeffd4f0.png)

The project high definition shadow resulitions for better quality  

![Shadow_Resolution_High](https://user-images.githubusercontent.com/24237112/152091677-11700a2f-47e5-4334-833e-d7cc2bdabf3a.png)

The Depth of Field also allowed a better focus on the scene highlighting the center of the scene in contrast with the background.

![DOF_On](https://user-images.githubusercontent.com/24237112/152091702-00d6fd64-f1b6-4a6c-bb63-0626e406b531.png)


### What I learned

This project was done a year after the Coconut Island - Coral Reef and followed the same principles of the afore mentioned project. So it allowed me to test what I had learned in the previous iteration. In addition, in this project I partook in a team of 4 elements which presented a new challenge as my previous work was done solo. This made me learn more about project management and task delegating as each student was assigned to a specific part of the project.

The project also helped me further develop my understanding of computer graphic concepts mainly Toon Shading and Shadow Mapping.

