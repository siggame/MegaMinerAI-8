#include "easing_equations.h"

//TODO----> Actually test all of these equations for accuracy
//
//
//
namespace easing_equations
{
  double easeInLinear(double t, double b, double c, double d)
  {
    return c*t/d + b;
  }
  double easeOutLinear(double t, double b, double c, double d)
  {
    return c*t/d + b;
  }
  double easeInOutLinear(double t, double b, double c, double d)
  {
    return c*t/d + b;
  }

  double easeInQuad(double t, double b, double c, double d)
  {
    t/=d;
    return (c*t*t + b);
  }
  double easeOutQuad(double t, double b, double c, double d)
  {
    t/=d;
    return (-c *t*(t-2) + b);
  }
  double easeInOutQuad(double t, double b, double c, double d)
  {
    t/=d;
    if (t < 1)
    {
      return c/2*t*t + b;
    }
    --t;
    return -c/2 * (t*(t-2) - 1) + b;
  }

  double easeInCubic(double t, double b, double c, double d)
  {
    t/=d;
    return c*t*t*t + b;
  }
  double easeOutCubic(double t, double b, double c, double d)
  {
    t=t/d-1;
    return c*(t*t*t + 1) + b;
  }
  double easeInOutCubic(double t, double b, double c, double d)
  {
    t/=d;
    if (t < 1)
    {
      return c/2*t*t*t + b;
    }
    t-=2;
    return c/2*(t*t*t + 2) + b;
  }

  double easeInQuart(double t, double b, double c, double d)
  {
    t/=d;
    return c*t*t*t*t + b;
  }
  double easeOutQuart(double t, double b, double c, double d)
  {
    t=t/d-1;
    return -c * (t*t*t*t - 1) + b;
  }
  double easeInOutQuart(double t, double b, double c, double d)
  {
    t/=(d/2);
    if (t < 1)
    {
      return c/2*t*t*t*t + b;
    }
    t-=2;
		return -c/2 * (t*t*t*t - 2) + b;
  }

  double easeInQuint(double t, double b, double c, double d)
  {
    t/=d;
    return c*t*t*t*t*t + b;
  }
  double easeOutQuint(double t, double b, double c, double d)
  {
    t=t/d-1;
    return c*(t*t*t*t*t + 1) + b;
  }
  double easeInOutQuint(double t, double b, double c, double d)
  {
    t/=(d/2);
    if (t < 1)
    {
      return c/2*t*t*t*t*t + b;
    }
    t-=2;
		return c/2*(t*t*t*t*t + 2) + b;
  }

  //TODO ----> Figure out how to get these Trig functions working
  /*
  double easeInSine(double t, double b, double c, double d)
  {
    return -c * Math.cos(t/d * (Math.PI/2)) + c + b;
  }
  double easeOutSine(double t, double b, double c, double d)
  {
    return c * Math.sin(t/d * (Math.PI/2)) + b;
  }
  double easeInOutSine(double t, double b, double c, double d)
  {
    return -c/2 * (Math.cos(Math.PI*t/d) - 1) + b;
  }
  */

  //TODO ----> Figure out how to get these Exp. functions working
  /*
  double easeInExpo(double t, double b, double c, double d)
  {
    return (t==0) ? b : c * Math.pow(2, 10 * (t/d - 1)) + b;
  }
  double easeOutExpo(double t, double b, double c, double d)
  {
    return (t==d) ? b+c : c * (-Math.pow(2, -10 * t/d) + 1) + b;
  }
  double easeInOutExpo(double t, double b, double c, double d)
  {
    if (t==0) return b;
		if (t==d) return b+c;
    t/=(d/2);
		if (t < 1) return c/2 * Math.pow(2, 10 * (t - 1)) + b;
		return c/2 * (-Math.pow(2, -10 * --t) + 2) + b;
  }
  */

  //TODO ----> Figure out how to get these Sqrt. functions working
  /*
  double easeInCirc(double t, double b, double c, double d)
  {
    t/=d;
    return -c * (Math.sqrt(1 - t*t) - 1) + b;
  }
  double easeOutCirc(double t, double b, double c, double d)
  {
    t=t/d-1;
    return c * Math.sqrt(1 - t*t) + b;
  }
  double easeInOutCirc(double t, double b, double c, double d)
  {
    t/=(d/2);
    if (t < 1) return -c/2 * (Math.sqrt(1 - t*t) - 1) + b;
    t-=2;
		return c/2 * (Math.sqrt(1 - t*t) + 1) + b;
  }
  */

  //TODO ----> Figure out how to get these Math functions working
  /*
  double easeInElastic(double t, double b, double c, double d
    double a, double p)
  {
    if (t==0) return b;
    t/=d;
    if (t==1) return b+c;
    if (!p) p=d*.3;
		if (!a || a < Math.abs(c)) { a=c; var s=p/4; }
		else var s = p/(2*Math.PI) * Math.asin (c/a);
		return -(a*Math.pow(2,10*t) * Math.sin( (t*d-s)*(2*Math.PI)/p )) + b;
  }
  double easeOutElastic(double t, double b, double c, double d
    double a, double p)
  {
    if (t==0) return b;  
    t/=d;
    if (t==1) return b+c;  if (!p) p=d*.3;
		if (!a || a < Math.abs(c)) { a=c; var s=p/4; }
		else var s = p/(2*Math.PI) * Math.asin (c/a);
		return (a*Math.pow(2,-10*t) * Math.sin( (t*d-s)*(2*Math.PI)/p ) + c + b);
  }
  double easeInOutElastic(double t, double b, double c, double d
    double a, double p)
  {
    if (t==0) return b;  
    t/=(d/2);
    if (t==2) return b+c;  if (!p) p=d*(.3*1.5);
		if (!a || a < Math.abs(c)) { a=c; var s=p/4; }
		else var s = p/(2*Math.PI) * Math.asin (c/a);
    t-=1;
		if (t < 1) return -.5*(a*Math.pow(2,10*t) * Math.sin( (t*d-s)*(2*Math.PI)/p )) + b;
    t-=1;
		return a*Math.pow(2,-10*t) * Math.sin( (t*d-s)*(2*Math.PI)/p )*.5 + c + b;
  }
  */

  double easeInBack(double t, double b, double c, double d, double s)
  {
    //if (s == undefined) s = 1.70158;
    t/=d;
		return c*t*t*((s+1)*t - s) + b;
  }
  double easeOutBack(double t, double b, double c, double d, double s)
  {
    //if (s == undefined) s = 1.70158;
    t=t/d-1;
		return c*(t*t*((s+1)*t + s) + 1) + b;
  }
  double easeInOutBack(double t, double b, double c, double d,
      double s)
  {
    //if (s == undefined) s = 1.70158; 
    t/=(d/2);
    s*=(1.525);
		if (t < 1) return c/2*(t*t*((s+1)*t - s)) + b;
    t-=2;
    s*=(1.525);
		return c/2*(t*t*((s+1)*t + s) + 2) + b;
  }

  double easeOutBounce(double t, double b, double c, double d)
  {
    t/=d;
    if (t < (1/2.75)) {
			return c*(7.5625*t*t) + b;
		} else if (t < (2/2.75)) {
      t-=(1.5/2.75);
			return c*(7.5625*t*t + .75) + b;
		} else if (t < (2.5/2.75)) {
      t-=(2.25/2.75);
			return c*(7.5625*t*t + .9375) + b;
		} else {
      t-=(2.625/2.75);
			return c*(7.5625*t*t + .984375) + b;
		}
  }
  double easeInBounce(double t, double b, double c, double d)
  {
    return c - easeOutBounce (d-t, 0, c, d) + b;
  }
  double easeInOutBounce(double t, double b, double c, double d)
  {
    if (t < d/2) return easeInBounce (t*2, 0, c, d) * .5 + b;
		else return easeOutBounce (t*2-d, 0, c, d) * .5 + c*.5 + b;
  }
}
