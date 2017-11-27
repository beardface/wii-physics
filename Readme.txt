WiiPhysics 2.2.0
  By Beardface
  
ChangeLog:

2.x.x
 +Added holding B to pan camera with cursor
 +Reset Camera on delete all objects
 +Added delete button (to selectively remove objects)
 +Added Camera button for setting camera (or you can still use 1)
 +Added Save/Load logic for saving and loading worlds
   +place wii physics files in /apps/wiiphysics/
 +Added on screen keyboard for saving to file.
 +Added Save/Load Buttons
 +Added New Rubber Band Joint, for all your elasticity needs
 +Added new open pen mode, you can now draw closed polygons or lines. (line rider anyone?)
 +Added zoom for clouds based on distance in sky
 +Updates to rope to render in a more believable way, using akima interpolation to spline rope points.

2.2.0 Now 2 Player!
 +Added Weld Joint
 +Added a second player (with limited capability)
	(Second player can drag, toss, freeze, unfreeze shapes)
 +Fixed Jumping of pen drawn shapes on create
 +Fixed placement of pin (proper pin joints now)
 +Added realistic grass.
 +Fixed bugs and crashes. (Specficially related to pully)
 +Restructured backend data management system.
 +Fixed pointer detection for selecting rectangles.
 +Added Support Button
 +Increased Object Limits

2.1.0
 +Added fully scrollable world with ground
    up, down, left, right to pan (Or just move the pointer to the edge of the screen)
 +Added minimap for scrolling around world
 +Added ability to fix camera to an object for easy following around world
    Hit 1 on any object to attach camera (works best on circles and squares)
    (To detach, just hit 1 anywhere on the screen)
 +Added sky, with dynamic clouds
    (You now know when you are in freeze b/c the clouds stop moving)
 +Fixed jumping of rectangles on draw
 +Lots of bug fixes
 +Now loads of fun! hooray!

2.0.0
 +Added pen joint for moving dynamic objects
   -You can now "Throw" objects
 +Added distinction between objects that are frozen and mobile to make it obvious to the user whats frozen
 +Fixed some bugs (Including crash from drawing small boxes/balls)
 +Keep objects from jumping when you select them
 +Improved intro screen
 +increased pen draw size
 +started on framework for zoomable worlds

1.3.0
 +In Game Help
 +Pen Drawing added
 +Reset Button Added
 +Added BG Music
 +Bug fixes
 +Initial action sounds (Using Sndlib) 
 +Intro Screen while wiiphysics constructs
 +Main Menu
 +Added Prismatic (Slider) Joint
 +Added Settings Menu
 +Added configurable Color
 +Added configurable Density
 +Added Show/Hide Menu Button
 +Increased world size (no longer hit the bottom with too many objects)
 +Fixed layout
 +Reset velocity to 0 if you grab an object
 +Set Velocity of Selected objects to whatever the velocity of the wiimote is
 +Fixed Freeze Unfreeze (Hit B while you have object selected to swap)
 +Dynamic Gravity Setting GUI
 +Dynamic Restitution GUI (Change individual object bouncieness)
 +Dynamic Friction GUI
 +Upgraded to libwiisprite 3.0

1.2
 +Undo Button
 +Pulleys, Ropes and Gears (Pin) work great now
 +Improved Icons and layout
 +Line Drawing works perfect now
 +Many Bug fixes, clean up

1.1
 +Added Line (Dynamic rectangle) Drawing
 +Clear Screen Button
 +Pulley/joint bug fixes to stop crashing!
 +fixed layout a bit
  
 Overview:
   A physics emulator for the wii using Box2d and libwiisprite!
   

 Installing:
   Copy everything in WiiPhysics folder to apps/ and launch from HBC
 
 Controls
  See In game help for how to.
	
Help/Request:
 beardfacemcbeard AT gmail DOT com
