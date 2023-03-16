# Control and Trajectory Tracking for Autonomous Vehicle

# Proportional-Integral-Derivative (PID)

In this project, PID controller is designed to perform vehicle trajectory tracking. Given a trajectory as an array of locations, and a simulation environment, PID controller is coded and tested on the CARLA simulator used in the industry.

### Installation

Run the following commands to install the starter code in the Udacity Workspace:

Clone the <a href="https://github.com/udacity/nd013-c6-control-starter/tree/master" target="_blank">repository</a>:

`git clone https://github.com/udacity/nd013-c6-control-starter.git`

## Run Carla Simulator

Open new window

* `su - student`
// Will say permission denied, ignore and continue
* `cd /opt/carla-simulator/`
* `SDL_VIDEODRIVER=offscreen ./CarlaUE4.sh -opengl`

## Compile and Run the Controller

Open new window

* `cd nd013-c6-control-starter/project`
* `./install-ubuntu.sh`
* `cd pid_controller/`
* `rm -rf rpclib`
* `git clone https://github.com/rpclib/rpclib.git`
* `cmake .`
* `make` (This last command compiles your c++ code, run it after every change in your code)

## Testing

To test your installation run the following commands.

* `cd nd013-c6-control-starter/project`
* `./run_main_pid.sh`
This will silently fail `ctrl + C` to stop
* `./run_main_pid.sh` (again)
Go to desktop mode to see CARLA

If error bind is already in use, or address already being used

* `ps -aux | grep carla`
* `kill id`


# Results
There are two parts of the PID design. First is the development of PID class as shown in `pid_controller.cpp` and `pid_controller.h`. This is used for both the Steering and Throttle Control. Second part consist of the error computations for steer and throttle. 

The steering error in two steps:
    
 - The target waypoint/index on the trajectory which has the minimum distance from ego vehicle is computed.
    
 - The difference between vehicle yaw and the angle from target point and ego point is given as steer error.

For throttle error, the difference between desired velocity and current velocity is computed. The desired velocity is found using the same target index (closest) as before. 

Lastly, numerous values of PID gains are guessed and tried. This repository contains all those plots in `/project/results`.

## Plots and Videos

Following values have proven the below results, for Steering, `Kp = .4, Ki = .001, Kd = .5` and for Throttle, `Kp = .2, Ki = .001, Kd = .06`

![Steer_error](/project/results/t5_s.png)

*Plot for Steer Error (blue) and Steer Control Input (orange)*

![Throttle_error](/project/results/t5_t.png)

*Plot for Throttle Error (blue), Throttle Control Input (orange), Brake Control Input*


A small video shows the utput in CARLA simulator. The complete video can be found [here](https://www.youtube.com/watch?v=f0r3q2EoyhE).

https://user-images.githubusercontent.com/16174913/225457456-7612c1b6-77c8-47bc-a0da-bfbf48c5072c.mp4


## Analysing the plot

*What is the effect of the PID according to the plots, how each part of the PID affects the control command?*

Generally, Kp makes the system track the trajectory but may result in oscillations. Kd damps the input by penalising the change of error and Ki makes sure that there in no steady state error. Here the values of Kp, Kd and Ki are a few orders different. This does not affect the final output as long as, the correct values of Kp, Ki, Kd is found. However while tuning it makes a big difference as these are inherently scaled by timestep, and PID error design.     

- Steer Controller: It seems like the system is sensitive to controller, i.e. small input from controller over corrects the system and throws in the other direction. The total error (integral error) seems to keep the system bounded.
- Throttle Controller: The throttle error seems to have a slow progress towards zero. This can be because the integral gain is not high enough, as compared to Kp and Kd, to penalise the sum of error. 

## Questions

 - How would you design a way to automatically tune the PID parameters?
    - To automatically find the PID gains, a similar idea as Twiddle algorithm can be used to vary the PID gains. The crosstrack error and the heading error can be used as a cost function to penalize the gains. This is also somewhat similar to model-free reinforcement learning on an online agent. However this method, might be suspected to finding the gains that are suitable for the given test manuevers.
    - Another class of methods would include using a simplified dynamic model of the car. Then a learning method (model-based reinforcement learning) or Adaptive control can be used. As compared to twiddle this will give a smarter guess of the next set of PID gains. But this might require detailed physics model of the system and a little more complicated code.

- PID controller is a model free controller, i.e. it does not use a model of the car. Could you explain the pros and cons of this type of controller?
    - Pros: Its intuitive nature of the gains. These gains directly tune the system in time domain instead of frequency domain, thus making it easier to correlate the sensitively of the gains to the output. Another pro is that such controller keeps the design computationally light, thus giving quick enough output. Controller delays an adversely effect the results and keeping the design simple avoids such situations. 
    - Cons: The tuning is an arduous process. It often requires trials and guesses. And if done blindly this may result in local minimum of performance. Secondaly, even though once tuned, PID may not give the same result for other test manuevers.
           

