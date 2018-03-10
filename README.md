# CG-Running-Man

This is a Computer Graphics project of Running man.
---
Collaborators:
--
Vinay Deshmukh<br />
Mandar Acharekar<br />
Rishabh Bhatnagar

Explanation:
---
Constants:
dist:
    Used as a representation for 1 Unit.
    By changing the value of dist, we can resize our person accordingly.

stepCount:
    This refers to the amount of pixels the head.x is moved to the right while moving as a animation.

Length variables for various bodyparts:
    const int LEN_NECK      = 20;// * dist;
    const int LEN_UP_ARM    = 20;// * dist;
    const int LEN_FOREARM   = 30;// * dist;
    const int LEN_MID       = 50;// * dist;
    const int LEN_THIGH     = 30;// * dist;
    const int LEN_CALF      = 40;// * dist;

    We need to replace '20' with '2 * dist', to make use of dist variable.
    To do this, we need to create a setup Function which will be called in main()

    Refer to ref-image.jpg for better understanding.

Structs:
Point
    x: x coordinate
    y: y coordinate

Polar:
    r: radius
    t: theta ie angle(in ClockWise Notation)

Person:
    Refer to ref-image.jpg for further clarification for it's attributes.

Functions:

Polar cart_to_polar(Point p)
Point polar_to_cart(Polar a)
    The above functions convert a Polar to a Point, or vice versa.

Person initPerson(Person p, int headx, int heady)
    Initializes the attributes of the passed variable p, and returns the modified version.
    int headx, heady indicate the starting position for the head.
    The rest of the body is derived from these coordinates

    Note: Since we have the setRunP1,2,3,4 functions, this function is redundant except for testing purposes.
    It also uses hard coded x,y values, when it should derive it's coordinates from head.x, head.y with help of R,Theta.


Point getResultPoint(Point refNode, int len, int polAngle)
    To ensure lines are of uniform length, we need to have a starting point, and then the end point has to be r units away at an angle t from our starting point.

    refNode: This Point gives us the starting location
    len: The len of the line we wish to create
    polAngle: The angle of the line with respect to origin
    Note: C uses ClockWise angles


Person setRunP1(Person p)
Person setRunP2(Person p)
Person setRunP3(Person p)
Person setRunP4(Person p)
    Refer images: run-reference.jpg and running.jpg

    The above four functions set the coordinates of all attributes of p, based on the coordinates of head, since we are changing the value of head outside the function in a loop.
    There are four functions since we have referred to the diagram(running.jpg) which has 8 stages for a 3d person.
    
    For a 2d person, the left and right limbs can't be seen separately so we can just write the code for four stages.
    The image run-reference.jpg can be referred to see how only 4 stages of 8 were used.

void printPerson(Person p)
    Debug function.
    Prints all attributes of the Person

void drawPerson(Person p)
Draws the
appropriate lines based on the attributes like midSecTop, l_elbow, etc


Images and OUTPUT:
---
![running](https://user-images.githubusercontent.com/20074475/37246146-bd4031ee-24c9-11e8-8fa7-0bc2befff61f.jpg)
![run-reference](https://user-images.githubusercontent.com/20074475/37246147-bd9eb4f8-24c9-11e8-80e8-8431445b85d4.jpg)
![ref-image](https://user-images.githubusercontent.com/20074475/37246148-be2c2bc6-24c9-11e8-9742-883d55e95352.jpg)
