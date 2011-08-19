#ifndef EASING_EQUATIONS_H
#define EASING_EQUATIONS_H

namespace EasingEquations
{
  double easeInQuad(double t, double b, double, c, double d);
  double easeOutQuad(double t, double b, double c, double d);
  double easeInOutQuad(double t, double b, double c, double d);

  double easeInCubic(double t, double b, double, c, double d);
  double easeOutCubic(double t, double b, double c, double d);
  double easeInOutCubic(double t, double b, double c, double d);

  double easeInQuart(double t, double b, double, c, double d);
  double easeOutQuart(double t, double b, double c, double d);
  double easeInOutQuart(double t, double b, double c, double d);

  double easeInQuint(double t, double b, double, c, double d);
  double easeOutQuint(double t, double b, double c, double d);
  double easeInOutQuint(double t, double b, double c, double d);

  double easeInSine(double t, double b, double, c, double d);
  double easeOutSine(double t, double b, double c, double d);
  double easeInOutSine(double t, double b, double c, double d);

  double easeInExpo(double t, double b, double, c, double d);
  double easeOutExpo(double t, double b, double c, double d);
  double easeInOutExpo(double t, double b, double c, double d);

  double easeInCirc(double t, double b, double, c, double d);
  double easeOutCirc(double t, double b, double c, double d);
  double easeInOutCirc(double t, double b, double c, double d);

  double easeInElastic(double t, double b, double, c, double d);
  double easeOutElastic(double t, double b, double c, double d);
  double easeInOutElastic(double t, double b, double c, double d);

  double easeInBack(double t, double b, double, c, double d);
  double easeOutBack(double t, double b, double c, double d);
  double easeInOutBack(double t, double b, double c, double d);

  double easeInBounce(double t, double b, double, c, double d);
  double easeOutBounce(double t, double b, double c, double d);
  double easeInOutBounce(double t, double b, double c, double d);
}

#endif //EASING_EQUATIONS_H



