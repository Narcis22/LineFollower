***The Evil Knivels***
 ================
 
 > Made by [Narcis Necula](https://github.com/Narcis22) & [Denisa Predescu](https://github.com/denisapredescu)
 >
 > Coordinated by Andrei Dumitriu
  
  🏁🚦🏎️⏲️🏁🚦🏎️⏲️🏁🚦🏎️⏲️🏁🚦🏎️⏲️🏁🚦🏎️⏲️🏁🚦🏎️⏲️🏁🚦🏎️⏲️🏁🚦🏎️⏲️🏁🚦🏎️⏲️🏁
  
  ### <i>Context</i>
  > <i>The line follower project consists of a little robot made from the components listed underneath (see [Components](#components)), that has to complete a course (white background with a black stripe) following the black line and completing a full lap in the fastest time (best out of 3 laps).  </i> <br>
 
  ### <i>Task requirements</i>
  > Given a robot kit, we had to assembled it and programmed it to follow the black line and to complete the course in less than 20s. Also we had to do automatic calibration and we choose to do turn signal indicators.
  
  ### <i>Details</i>
  <b><i>Sensor Calibration</i></b>: There are more than one way to calibrate the machine but the most elegant one that we found was making the robot swivel to the left ultil the last sensor on the right sees the black tape, and then change direction of swivel until the last sensor on the left sees the black tape. It keeps repeting this process for a number of given seconds then proceeds to follow the line.
  
  Tuning the software for the robot to make him fast and at the same time very cunning in the corners required playing with the PID values for power and error correction values(did not touch i). The process was as follows:
   -  ajusted the PID values (not the i value) until the results were good enough but the car still had overshoot problems that couldn't be fixed with more power;
   -  after some trial and error we found some decent values for the PID but after some tests on sharper turns we found that adding power still couldn't correct that much because of the overshoot that would occure. So we managed to to change the former way of taking a turn from: stopping a wheel and moving the other at full throttle; to : moving a wheel at full speed forward and the other full speed backwards.
   -  after the last test was a success and the robot managed to pass withouth fail multiple times all types of tracks we started implementing the blinkers(optional for bonus)
   - the blinkers are two led lights , one on the right and one on the left, for which we measured the error and depending on it we determined which and if a led blinks. We gave the error a buffer so that it doesn't consider the minor moves to keep a straight line as a turn and start blinking for no aparent reason.
   

  ### <a name="components"></a><i>Components</i>:
 <img src="https://user-images.githubusercontent.com/62501946/212529655-0b4233cc-996a-4588-9c81-03e6b01a0ffd.png" 
 width="50%" height="50%">

  1. Arduino Uno
  2. Zip-ties
  3. Power source (can be of different shape). In our case, a LiPo battery
  4. Wheels (2) 
  5. Wires for the line sensor (female - male)
  6. QTR-8A reflectance sensor, along with screws
  7. Ball caster
  8. Extra wires from the kit or lab
  9. Chassis
  10. Breadboard - medium (400pts)
  11. L293D motor driver
  12. DC motors (2)
  13. (Bonus points for 'Blinkers') Two RGB Leds
 
 
 [<i><b>Code</b></i>](https://github.com/Narcis22/LineFollower/blob/main/LineFollower.ino)

 
<details>
<summary><i><b>Setup photos</b></i></summary>
<br> 

<!--
  ![image](https://user-images.githubusercontent.com/62501946/212529655-0b4233cc-996a-4588-9c81-03e6b01a0ffd.png)
  -->

<br>![IMG_1236](https://user-images.githubusercontent.com/62501946/212530192-3f48939c-fcc3-4220-8670-a135f8b630c2.jpg)

<br>![IMG_1239](https://user-images.githubusercontent.com/62501946/212530198-288ea9b2-57aa-4519-b42d-2f514094efa6.jpg)

<br>![IMG_1254](https://user-images.githubusercontent.com/62501946/212530213-dbe5cd1c-04f3-4fae-b90f-3d3058a3c565.jpg)

<br>![IMG_1240](https://user-images.githubusercontent.com/62501946/212530469-e9d2e3b8-5e0b-46bb-8add-2698c7f19fae.jpg)

<br>![IMG_1238](https://user-images.githubusercontent.com/62501946/212530470-f27cdac4-bfdb-4f34-8b25-8b08c1b870a0.jpg)

</details>

<i><b>Video with contest lap: </b></i>
[Go to youtube to see video.](https://youtu.be/cpxjYtifI8o)
