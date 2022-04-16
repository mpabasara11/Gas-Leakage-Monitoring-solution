# Gas-Leakage-Monitoring-solution


Main functions 
1.	Provide Realtime data about both sensing areas through the web page
2.	Provide audible notification about sensing environments
•	normal gas leak (Only one sensor will detect leakage) 
•	severe gas leak (Both sensors will detect a gas leakage).
3.	RGB notification Lights also Provide System Information’s
•	Red-Gas Detected
•	Green-Monitoring 
•	Blue-System is Off

Technologies used
AJAX (Asynchronous JavaScript and XML) -used to display Realtime data on webpage sent by the controller
XMLHttpRequest -AJAX uses this protocol for requesting to the web server


Hardware Setup


•	NodeMCU Version 3    -it has built in WIFI and could find at affordable price in the market

•	MQ-2 Gas Sensors *2   -comes in a module which we can easily connect with a controller board

•	RGB Units *2 -comes with built in resistors so that we don’t need to connect those though resistors (board Outputs 3.5V could harm the leds otherwise)

•	Active Buzzers*2 - no specific reason


