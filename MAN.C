#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<math.h>

#define PI 3.141
int dist = 10;
/* represents the no of pixels to be used as one unit for the human*/
 /* since i'm translating the gimp co ordinates to turboc
 grid size in gimp is 10, i've set default value of dist as 10
 if need be, we can just change the value of dist
 to resize the human proportionately
 */

const int stepCount = 10;
//replace hardcode with *dist, have to do in function
const int LEN_NECK      = 20;// * dist;
const int LEN_UP_ARM    = 20;// * dist;
const int LEN_FOREARM   = 30;// * dist;
const int LEN_MID       = 50;// * dist;
const int LEN_THIGH     = 30;// * dist;
const int LEN_CALF      = 40;// * dist;

/*
FUNCTIONS:
initPerson();
    Initializes the co ordinates of the person variable

*/

typedef struct{
  int x;
  int y;
} Point;

typedef struct{
 int r;
 int t;
} Polar;


/* Converts cartesian Point to Polar*/
Polar cart_to_polar(Point p){
Polar a;
int sqreq = p.x * p.x + p.y * p.y;
if(sqreq<1) printf("DOMAIN: %3d\n", sqreq);
a.r = sqrt( sqreq );
a.t = atan( p.y/(float)p.x) * 180/PI;//converting radians to degrees

return a;
}// cart_to_polar

/* Converts Polar to cartesian Point*/
Point polar_to_cart(Polar a){
Point p;
p.x = a.r * cos(a.t * PI/180.0 ); //converting degrees to radians
p.y = a.r * sin(a.t * PI/180.0 );

return p;
}// polar_to_cart

typedef struct{

 Point head;
 int head_r;
 /* co ordinates of the centre of the circle which represents the head*/

 Point neck_head;
 //Point neck_body;
 /* Co-ordinates of the line that is neck
  neck_head - midSecTop = This is the neck
  */

 Point midSecTop;
 Point midSecBot;
 /* Co ordinates of the mid section line */

 Point l_elbow, r_elbow;
 Point l_hand, r_hand;
 /* Co ordinates corresponding to 4 lines such that
 midSecTop - l_elbow;
 midSecTop - r_elbow;
 l_elbow   - l_hand;
 r_elbow   - r_hand;

       |     midSecTop
      /|\    The lines that are described above
    /  |  \

 */


 Point l_knee, r_knee;
 Point l_foot, r_foot;
 /* Co ordinates of the legs
 Lines to be made as
 midSecBot - l_knee
 midSecBot - r_knee
 l_knee    - l_foot
 r_knee    - r_foot

	|    midSecBot
       / \
     /     \


 */

} Person;


Person initPerson(Person p, int headx, int heady){
p.head.x = headx; //100;
p.head.y = heady; //100;
p.head_r = 2 * dist;  /* upper end will always be at below point of circle*/

// neck_head
p.neck_head.x = p.head.x;
p.neck_head.y = p.head.y + p.head_r;

// midSecTop
p.midSecTop.x = p.head.x;
p.midSecTop.y = p.neck_head.y + dist;

// midSecBot
p.midSecBot.x = p.head.x;
p.midSecBot.y = p.midSecTop.y + 5 * dist;

// l_elbow
p.l_elbow.x = p.midSecTop.x - 2 * dist;
p.l_elbow.y = p.midSecTop.y + dist;

// r_elbow
p.r_elbow.x = p.midSecTop.x + 2 * dist;
p.r_elbow.y = p.midSecTop.y + dist;

// l_hand
p.l_hand.x = p.l_elbow.x;
p.l_hand.y = p.l_elbow.y + 3 * dist;

// r_hand
p.r_hand.x = p.r_elbow.x;
p.r_hand.y = p.r_elbow.y + 3 * dist;

// l_knee
p.l_knee.x = p.midSecBot.x - 2 * dist;
p.l_knee.y = p.midSecBot.y + 3 * dist;

// r_knee
p.r_knee.x = p.midSecBot.x + 2 * dist;
p.r_knee.y = p.midSecBot.y + 3 * dist;

// l_foot
p.l_foot.x = p.l_knee.x;
p.l_foot.y = p.l_knee.y + 4 * dist;

// r_foot
p.r_foot.x = p.r_knee.x;
p.r_foot.y = p.r_knee.y + 4 * dist;

return p;
}

Point getResultPoint
      (Point refNode, int len, int polAngle){
/*
This function generates the end point of the line specified
by the length and polar angle paramter.


Sample Usage:
start point is 100,100
we want a line such that it is len=80, and angle=10deg
Point o = 100,100

Point endPoint = getResultPoint(o, 80, 10);

Now, we can draw the required line as
line(o, endPoint);

*/
Point ap, ap2;//temps for calculation
Polar ar, ar2;
Point resultNode;

ap = refNode;
ar.r = len; ar.t = polAngle;
ap2 = polar_to_cart(ar);
resultNode.x = ap.x + ap2.x;
resultNode.y = ap.y + ap2.y;

return resultNode;
}//getResultPoint
/*
setP1, setP2, setP3, setP4 functions will set new co ordinates to
the passed Point, and then drawPerson will be called.
These functions represent one stage each out of four.
*/

Person setRunP1(Person p){
/*
This function will set the coordinates for running stage 1 of 4
All points will be based on the assumption, head.x has been modified outside
this function
*/

Polar ar, ar2; //temp variables for calc
Point ap, ap2;

// head.x has been incremented outside, so we will not change that
// head.y also is constant, for now atleast

// neck_head
p.neck_head.x = p.head.x;
//p.neck_head.y ; //blank for now

//////////////////////////////////////////////////
/////////// ALL ANGLES ARE IN CW FORM  ///////////
//////////////////////////////////////////////////

// midSecTop
p.midSecTop = getResultPoint( p.neck_head, LEN_NECK, 120);

//l_elbow
p.l_elbow = getResultPoint( p.midSecTop, LEN_UP_ARM, 60);

//l_hand
p.l_hand = getResultPoint( p.l_elbow, LEN_FOREARM, 300);

//r_elbow
p.r_elbow = getResultPoint( p.midSecTop, LEN_UP_ARM, 160);

//r_hand
p.r_hand = getResultPoint(p.r_elbow, LEN_FOREARM, 110);

//midSecBot
p.midSecBot = getResultPoint(p.midSecTop, LEN_MID, 120);//same angle as midSecTop

//r_knee
p.r_knee = getResultPoint(p.midSecBot, LEN_THIGH, 50);

//r_foot
p.r_foot = getResultPoint(p.r_knee, LEN_CALF, 50);//same angle as r_knee

//l_knee
p.l_knee = getResultPoint(p.midSecBot, LEN_THIGH, 110);

//l_foot
p.l_foot = getResultPoint(p.l_knee, LEN_CALF, 190);

return p;
}// setRunP1

Person setRunP2(Person p){
/*
This function will set the coordinates for running stage 1 of 4
All points will be based on the assumption head.x has been modified outside
this function
*/
p.neck_head.x = p.head.x;

p.midSecTop = getResultPoint( p.neck_head, LEN_NECK   , 100);
p.l_elbow   = getResultPoint( p.midSecTop, LEN_UP_ARM , 85);
p.l_hand    = getResultPoint( p.l_elbow  , LEN_FOREARM, 350);
p.r_elbow   = getResultPoint( p.midSecTop, LEN_UP_ARM , 150);
p.r_hand    = getResultPoint( p.r_elbow  , LEN_FOREARM, 95 );
p.midSecBot = getResultPoint( p.midSecTop, LEN_MID    , 100);//same as midSecTop
p.r_knee    = getResultPoint( p.midSecBot, LEN_THIGH  , 60 );
p.r_foot    = getResultPoint( p.r_knee   , LEN_CALF   , 95 );
p.l_knee    = getResultPoint( p.midSecBot, LEN_THIGH  , 90 );
p.l_foot    = getResultPoint( p.l_knee   , LEN_CALF   , 180);

return p;
}// setRun2

Person setRunP3(Person p){
/*
This function will set the coordinates for running stage 1 of 4
All points will be based on the assumption head.x has been modified outside
this function
*/
p.neck_head.x = p.head.x;

p.midSecTop = getResultPoint( p.neck_head, LEN_NECK   , 95 );
p.l_elbow   = getResultPoint( p.midSecTop, LEN_UP_ARM , 90 );
p.l_hand    = getResultPoint( p.l_elbow  , LEN_FOREARM, 15 );
p.r_elbow   = getResultPoint( p.midSecTop, LEN_UP_ARM , 95 );
p.r_hand    = getResultPoint( p.r_elbow  , LEN_FOREARM, 80 );
p.midSecBot = getResultPoint( p.midSecTop, LEN_MID    , 95 );//same as midSecTop
p.r_knee    = getResultPoint( p.midSecBot, LEN_THIGH  , 87 );
p.r_foot    = getResultPoint( p.r_knee   , LEN_CALF   , 93 );
p.l_knee    = getResultPoint( p.midSecBot, LEN_THIGH  , 73 );
p.l_foot    = getResultPoint( p.l_knee   , LEN_CALF   , 165);

return p;
}// setRun3

Person setRunP4(Person p){
/*
This function will set the coordinates for running stage 1 of 4
All points will be based on the assumption head.x has been modified outside
this function
*/
p.neck_head.x = p.head.x;

p.midSecTop = getResultPoint( p.neck_head, LEN_NECK   , 95 );
p.l_elbow   = getResultPoint( p.midSecTop, LEN_UP_ARM , 105 );
p.l_hand    = getResultPoint( p.l_elbow  , LEN_FOREARM, 60 );
p.r_elbow   = getResultPoint( p.midSecTop, LEN_UP_ARM , 80 );
p.r_hand    = getResultPoint( p.r_elbow  , LEN_FOREARM, 30 );
p.midSecBot = getResultPoint( p.midSecTop, LEN_MID    , 95 );//same as midSecTop
p.r_knee    = getResultPoint( p.midSecBot, LEN_THIGH  , 95 );
p.r_foot    = getResultPoint( p.r_knee   , LEN_CALF   , 120 );
p.l_knee    = getResultPoint( p.midSecBot, LEN_THIGH  , 60 );
p.l_foot    = getResultPoint( p.l_knee   , LEN_CALF   , 110);

return p;

}// setRunP4
void printPerson(Person p){

printf("Person details:\n");
printf("Head:      x= %3d, y= %3d, r= %3d\n", p.head.x, p.head.y, p.head_r);
printf("Neck_head: x= %3d, y= %3d\n", p.neck_head.x, p.neck_head.y);
printf("MidSecTop: x= %3d, y= %3d\n", p.midSecTop.x, p.midSecTop.y);
printf("MidSecBot: x= %3d, y= %3d\n", p.midSecBot.x, p.midSecBot.y);

printf("L_Elbow  : x= %3d, y= %3d  ", p.l_elbow.x,   p.l_elbow.y  );
printf("R_Eblow  : x= %3d, y= %3d\n", p.r_elbow.x,   p.r_elbow.y  );

printf("L_Hand   : x= %3d, y= %3d  ", p.l_hand.x,    p.l_hand.y   );
printf("R_Hand   : x= %3d, y= %3d\n", p.r_hand.x,    p.r_hand.y   );

printf("L_Knee   : x= %3d, y= %3d  ", p.l_knee.x,    p.l_knee.y   );
printf("R_Knee   : x= %3d, y= %3d\n", p.r_knee.x,    p.r_knee.y   );

printf("L_Foot   : x= %3d, y= %3d  ", p.l_foot.x,    p.l_foot.y   );
printf("R_Foot   : x= %3d, y= %3d\n", p.r_foot.x,    p.r_foot.y   );
}//print Person



void drawPerson(Person p){
  // draw Head
  circle( p.head.x, p.head.y, p.head_r);

  // draw neck
  line( p.neck_head.x, p.neck_head.y ,
	p.midSecTop.x, p.midSecTop.y );

  // draw midSection
  line( p.midSecTop.x, p.midSecTop.y ,
	p.midSecBot.x, p.midSecBot.y );

  // shoulder to left elbow
  line( p.midSecTop.x, p.midSecTop.y ,
	p.l_elbow.x  , p.l_elbow.y   );

  // left elbow to left hand
  line( p.l_elbow.x  , p.l_elbow.y   ,
	p.l_hand.x   , p.l_hand.y    );

  // right elbow to right hand
  line( p.r_elbow.x  , p.r_elbow.y   ,
	p.r_hand.x   , p.r_hand.y    );

  // shoulder to right elbow
  line( p.midSecTop.x, p.midSecTop.y,
	p.r_elbow.x  , p.r_elbow.y   );

  // midSecBot to left knee
  line( p.midSecBot.x, p.midSecBot.y,
	p.l_knee.x   , p.l_knee.y    );

  // midSecBot to right knee
  line( p.midSecBot.x, p.midSecBot.y,
	p.r_knee.x   , p.r_knee.y    );

  // left knee to left foot
  line( p.l_knee.x   , p.l_knee.y   ,
	p.l_foot.x   , p.l_foot.y   );

  // right knee to right foot
  line( p.r_knee.x   , p.r_knee.y   ,
	p.r_foot.x   , p.r_foot.y   );

}// drawPerson

int main(){

/* request auto detection */
int gdriver = DETECT, gmode, errorcode;
int xmax, ymax;
Point ap, ap2; //temp variables
Polar ar, ar2;


Person pp;

clrscr();

pp = initPerson(pp, 300, 100);

/* initialize graphics and local variables */
initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");

// testing angles section
ap.x = 100; ap.y = 100;
ar.r = 100; ar.t = 53;//36.87
ap2 = polar_to_cart(ar);
circle(ap.x, ap.y, 10);//original point 100 100
circle(ap.x + ap2.x, ap.y + ap2.y, 10); //expected to be 160 180
line(ap.x, ap.y, ap.x + ap2.x, ap.y + ap2.y); // line connecting them
line(ap.x, ap.y, ap.x, ap.y+ap2.y);//vertical line
line(ap.x, ap.y+ap2.y, ap.x+ap2.x, ap.y+ap2.y);//horizontal line

printf("100: %3d; 100:%3d\n", ap.x, ap.y);
printf("160: %3d; 180:%3d\n", ap.x+ap2.x, ap.y+ap2.y);
// testing angles section


//for(i=0;i<3;i++){
drawPerson(pp);
pp.head.x += stepCount;


getch();
cleardevice(); //clear out the screen

pp = setRunP1(pp);
drawPerson(pp);
pp.head.x += stepCount;
getch();
cleardevice();

pp = setRunP2(pp);
drawPerson(pp);
pp.head.x += stepCount;
getch();
cleardevice();

pp = setRunP3(pp);
drawPerson(pp);
pp.head.x += stepCount;
getch();
cleardevice();

pp = setRunP4(pp);
drawPerson(pp);
pp.head.x+= stepCount;
//}//for

getch();
closegraph();
return 0;
}//main