![alt tag](http://store.picbg.net/pubpic/16/84/b98488c81d151684.png)

RAVEN
=====

Open source educational robot

Description
====
The universe is the biggest unknown for humankind. Historically, there were many unknowns - the shape of
Planet Earth, how to prepare for a spaceflight, how to land on the Moon, etc.   
Very skilled scientiests and engineers and therefore very few were smart enough to 
design the tools and invent the technology in order to gather
more knowledge needed to explore the space.    Nowadays, more than 50 years after the first successful
spaceflight, people have wide variety of technologies and tools. Unfortunately, not many of them are
easy to learn and use.    On the contrary, there are many willing to learn, participate and innovate for
that cause - space exploration - the next challenge for the mankind. 

**RAVEN** is built to overcome that challenge and expose the right set of tools, hardware and software to
everyone who wants to try and experiment, even children. It consists of:
1) a model of an intelligent autonomous robot,
2) a modular hardware system that is easily upgradeable and cheap,
3) an easy to use API to control it.
Having all that a lot of algorithms can be developed, tested and emulated on Earth, in schools, at home before
applied in a real robot that can be sent to explore the space.
**RAVEN** construction
====
**Arduino** -> An open source enviroment with flourishing and growing community, lots of examples giving you idea
how to start and allows the user to rapidly prototype algorithms. In the test example obstacle avoidance algorithm
is implemented on top of Arduino.   

**Raspberry Pi Model B** -> This is a fully functional PC which is cheap and powerful enough. Using this computer 
a map with the robot's movement can be drawn, a live streaming of what robot is seeing can be viewed and a
navigation API can be exposed so that one can control the robot easily without taking care of the low level
problems in the entire system.   

**Navigation API** -> one can easily control the robot with it.   

**Web** -> There is a web page where one can browse on a map which is showing where the robot is and where it was.   
The map is built dynamically based on the robot's movement. An obstacles which robot is encountering are saved
on the map so clicking over an obstacle one can see a picture of it.   
There a live stream video can also be watched showing
what the robot is viewing now.     Another functionality is to make the robot move to a specific place.


