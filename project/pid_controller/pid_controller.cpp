/**********************************************
 * Self-Driving Car Nano-degree - Udacity
 *  Created on: December 11, 2020
 *      Author: Mathilde Badoual
 **********************************************/

#include "pid_controller.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kpi, double Kii, double Kdi, double output_lim_maxi, double output_lim_mini) {
   /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   **/
  this->Kp = Kpi;
  this->Ki = Kii;
  this->Kd = Kdi;
  this->err 	= 0.0;
  this->preverr 	= 0.0;
  this->toterr 	= 0.0;
  this->output_lim_max = output_lim_maxi;
  this->output_lim_min = output_lim_mini;
  this->dt  = 0.0;
}


void PID::UpdateError(double cte) {
   /**
   * TODO: Update PID errors based on cte.
   **/
   
  this->preverr = this->err;
  this->err	  = cte;
  this->toterr  += cte*this->dt;
}

double PID::TotalError() {
   /**
   * TODO: Calculate and return the total error
    * The code should return a value in the interval [output_lim_mini, output_lim_maxi]
   */
    double control;
    err = this->err;
    preverr = this->preverr;
    toterr  = this->toterr;
  	Kp = this->Kp;
    Ki = this->Ki;
    Kd = this->Kd;
    dt = this->dt;
    output_lim_max = this->output_lim_max;
    output_lim_min = this->output_lim_min;
  	
  	if(dt>0)
    {
      
      control = Kp*err + Ki*toterr + Kd*(err - preverr)/dt;
    }
    else
    {
      control = Kp*err + Ki*toterr;
    }
    
    if(control > output_lim_max)
    {
        control = output_lim_max;
    }
    else if(control < output_lim_min)
    {
        control = output_lim_min;
    }
    

    return control;
}

double PID::UpdateDeltaTime(double new_delta_time) {
   /**
   * TODO: Update the delta time with new value
   */
   this->dt = new_delta_time;
}