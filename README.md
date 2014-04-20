![alt tag](http://store.picbg.net/pubpic/16/84/b98488c81d151684.png)

RAVEN
=====

Open source educational robot

Video
====
https://vimeo.com/92450833


Description
====
Ever since the first space exploration programs were founded but have been run by closed groups in institutes around the world.    
The technologies used, being complex and costly, have driven away many interested people willing to work in the area.    
**RAVEN’s** main goal is to change this and allow any open-minded person to contribute to the common cause of space exploration.Our project so far has achieved just the beginning of the whole idea. We have built a basic robot entirely made up of affordable and easy to get parts, and with open-source software.Our rover is the base, on top of which people can implement their ideas anywhere – at universities, schools, or even at home.   
The rover’s modularity allows parts to be easily appended or replaced.    
The processing powers of both the microcontroller and the microcomputer included are enough to implement highly complex logic.The mechanical parts – sensors, wheels, etc. – can easily be manipulated by the code via a communication interface, which is the combination of the parts’ drivers.Community-run open-source development can rapidly gather a large quantity of solutions.Combining them can lead to qualitative changes in the way we explore space.    
**RAVEN’s** visionary goal is to create modular landing gear that can be upgraded and updated based on the need that it faces on the working spot; a self-adjustable robot that can provide feedback back to Earth and secure safe laboratory space prior to astronauts’ arrival.   

**RAVEN** construction
====
Arduino: An open source environment with a growing community, providing lots of trials, showing developers how to start prototyping ideas. In our base build, the obstacle-avoidance algorithm is implemented on Arduino.   

**Raspberry Pi Model B:** This is a fully functional microcomputer, which is cheap and powerful enough to run all necessary services to utilize any idea.    
Using this computer with Linux, we have been able to set up a web server – LAMP (Linux, Apache, MySQL, PHP) – to forward information to users.    
Separating it from the Arduino code allows the development of high level logic, which communicates with the rover’s firmware through an interface, so it doesn’t have to bother with the low level implementations.   
**Web:** We have set up a web server on the Raspberry Pi, which is the intermediate layer transforming the sensors’ raw data into user-friendly visualization.   
Currently, it draws a map of the rover’s movement, on which it shows pictures associated with each obstacle the robot has passed round, provides a video live stream, and navigation controls to point the rover to a specific place, or turn its cameras to see a particular object.   

**Navigation API:** that is the aforementioned interface between the high and low level logics. It consists of the rover’s drivers – the used elements’ public communication functions, which can be readily used in any programming logic, even in basic frameworks like Scratch for children.


