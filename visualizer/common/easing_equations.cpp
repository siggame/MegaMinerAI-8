#include "easing_equations.h"

namespace visualizer 
{

  // Linear Easing
  double linearTween(double t, double b, double c, double d)
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

  // Quadratic Easing
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
    t/=d/2;
    if (t < 1)
    {
      return c/2*t*t + b;
    }
    --t;
    return -c/2 * (t*(t-2) - 1) + b;
  }

  // Cubic Easing
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
    t/=d/2;
    if (t < 1)
    {
      return c/2*t*t*t + b;
    }
    t-=2;
    return c/2*(t*t*t + 2) + b;
  }

  // Quart Easing
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

  // Quint Easing
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

  // Sine Easing
  double easeInSine(double t, double b, double c, double d)
  {
    return -c * cos(t/d * (3.14159265/2)) + c + b;
  }
  double easeOutSine(double t, double b, double c, double d)
  {
    return c * sin(t/d * (3.14159265/2)) + b;
  }
  double easeInOutSine(double t, double b, double c, double d)
  {
    return -c/2 * (cos(3.14159265*t/d) - 1) + b;
  }

  // Exponential Easing
  double easeInExpo(double t, double b, double c, double d)
  {
    return (t==0) ? b : c * pow(2, 10 * (t/d - 1)) + b;
  }
  double easeOutExpo(double t, double b, double c, double d)
  {
    return (t==d) ? b+c : c * (-pow(2, -10 * t/d) + 1) + b;
  }
  double easeInOutExpo(double t, double b, double c, double d)
  {
    if (t==0) return b;
		if (t==d) return b+c;
    t/=(d/2);
		if (t < 1) return c/2 * pow(2, 10 * (t - 1)) + b;
		return c/2 * (-pow(2, -10 * --t) + 2) + b;
  }

  // Circular Easing
  double easeInCirc(double t, double b, double c, double d)
  {
    t/=d;
    return -c * (sqrt(1 - t*t) - 1) + b;
  }
  double easeOutCirc(double t, double b, double c, double d)
  {
    t=t/d-1;
    return c * sqrt(1 - t*t) + b;
  }
  double easeInOutCirc(double t, double b, double c, double d)
  {
    t/=(d/2);
    if (t < 1) return -c/2 * (sqrt(1 - t*t) - 1) + b;
    t-=2;
		return c/2 * (sqrt(1 - t*t) + 1) + b;
  }

  // Elastic Easing
  double easeInElastic(double t, double b, double c, double d,
    double a=0, double p=0)
  {
    if (t==0) return b;
    t/=d;
    if (t==1) return b+c;
    if(p==0) p=d*.3;
    double s;
		if (a==0 || a < abs(c)) { a=c; s=p/4; }
		else s = p/(2*3.14159265) * asin (c/a);
    t-=1;
		return -(a*pow(2,10*t) * sin( (t*d-s)*(2*3.14159265)/p )) + b;
  }
  double easeOutElastic(double t, double b, double c, double d,
    double a=0, double p=0)
  {
    if (t==0) return b;  
    t/=d;
    if (t==1) return b+c;
    if(p==0) p=d*.3;
    double s;
		if ( a==0 || a < abs(c)) { a=c; s=p/4; }
		else s = p/(2*3.14159265) * asin (c/a);
		return (a*pow(2,-10*t) * sin( (t*d-s)*(2*3.14159265)/p ) + c + b);
  }
  double easeInOutElastic(double t, double b, double c, double d,
    double a=0, double p=0)
  {
    if (t==0) return b;  
    t/=(d/2);
    if (t==2) return b+c;
    if(p==0) p=d*.3*1.5;
    double s;
		if (a==0 || a < abs(c)) { a=c; s=p/4; }
		else s = p/(2*3.14159265) * asin (c/a);
		if (t < 1) 
    {
      t-=1;
      return -.5*(a*pow(2,10*t) * sin( (t*d-s)*(2*3.14159265)/p )) + b;
    }
    t-=1;
		return a*pow(2,-10*t) * sin( (t*d-s)*(2*3.14159265)/p )*.5 + c + b;
  }

  // Back Easing
  double easeInBack(double t, double b, double c, double d, double s = 1.70158)
  {
    t/=d;
		return c*t*t*((s+1)*t - s) + b;
  }
  double easeOutBack(double t, double b, double c, double d, double s = 1.70158)
  {
    t=t/d-1;
		return c*(t*t*((s+1)*t + s) + 1) + b;
  }
  double easeInOutBack(double t, double b, double c, double d,
      double s = 1.70158)
  {
    t/=(d/2);
    s*=(1.525);
		if (t < 1) return c/2*(t*t*((s+1)*t - s)) + b;
    t-=2;
    s*=(1.525);
		return c/2*(t*t*((s+1)*t + s) + 2) + b;
  }

  // Bounce Ease
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
