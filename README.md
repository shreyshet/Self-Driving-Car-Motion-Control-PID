# Control and Trajectory Tracking for Autonomous Vehicle

# Proportional-Integral-Derivative (PID)

In this project, PID controller is designed to perform vehicle trajectory tracking. Given a trajectory as an array of locations, and a simulation environment, PID0 controller is coded and tested on the CARLA simulator used in the industry.

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

Lastly, numerous values of PID gains are guessed and tried. The repositories contains a few plots in `/project/results`.

## Plots and Videos

https://user-images.githubusercontent.com/16174913/225457456-7612c1b6-77c8-47bc-a0da-bfbf48c5072c.mp4




## Analysing the plot

What is the effect of the PID according to the plots, how each part of the PID affects the control command?
The answer explains the role of the different parts of the PID.

## Questions

 - How would you design a way to automatically tune the PID parameters?
 
    - First I would a Use the Twiddling algorithm to vary the PID gains such that error minimi
    - 
 
 -
This is an open question, the coherence and justification of the answer is valued.

- PID controller is a model free controller, i.e. it does not use a model of the car. Could you explain the pros and cons of this type of controller?
Find at least 2 pros and cons for model free versus model based.

