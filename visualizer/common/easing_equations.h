///////////////////////////////////////////////////////////////////////////////
/// @file easing_equations.h
/// @description Contains a group of movement easing equations.
///////////////////////////////////////////////////////////////////////////////

#ifndef EASING_EQUATIONS_H
#define EASING_EQUATIONS_H
#include <cmath>
using namespace std;

namespace visualizer
{
  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeInLinear ( double t, double b, double c, double d )
  /// @brief Simple linear tweening, no easing.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////
  
  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeOutLinear ( double t, double b, double c, double d )
  /// @brief Simple linear tweening, no easing.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////
  
  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeInOutLinear ( double t, double b, double c, double d )
  /// @brief Simple linear tweening, no easing.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////
  
  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeInQuad( double t, double b, double c, double d )
  /// @brief Quadratic easing in, accelerating from 0 velocity.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeOutQuad( double t, double b, double c, double d )
  /// @brief Quadratic easing out, decelerating to 0 velocity.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeInOutQuad( double t, double b, double c, double d )
  /// @brief Quadratic easing in/out, accelerating halfway, and then decelerating
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeInCubic( double t, double b, double c, double d )
  /// @brief Cubic easing in, accelerating from 0 velocity.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeOutCubic( double t, double b, double c, double d )
  /// @brief Cubic easing out, decelerating to 0 velocity.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeInOutCubic ( double t, double b, double c, double d )
  /// @brief Cubic easing in/out, accelerating halfway, and then decelerating
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeInQuart( double t, double b, double c, double d )
  /// @brief Quartic easing in, accelerating from 0 velocity.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeOutQuart( double t, double b, double c, double d )
  /// @brief Quartic easing out, decelerating to 0 velocity.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeInOutQuart ( double t, double b, double c, double d )
  /// @brief Quartic easing in/out, accelerating halfway, and then decelerating
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeInQuint( double t, double b, double c, double d )
  /// @brief Quintic easing in, accelerating from 0 velocity.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeOutQuint( double t, double b, double c, double d )
  /// @brief Quintic easing out, decelerating to 0 velocity.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeInOutQuint ( double t, double b, double c, double d )
  /// @brief Quintic easing in/out, accelerating halfway, and then decelerating
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeInSine( double t, double b, double c, double d )
  /// @brief Sinusoidal easing in, accelerating from 0 velocity.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeOutSine( double t, double b, double c, double d )
  /// @brief Sinusoidal easing out, decelerating to 0 velocity.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeInOutSine ( double t, double b, double c, double d )
  /// @brief Sinusoidal easing in/out, accelerating halfway, and then decelerating
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeInExpo( double t, double b, double c, double d )
  /// @brief Exponential easing in, accelerating from 0 velocity.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeOutExpo( double t, double b, double c, double d )
  /// @brief Exponential easing out, decelerating to 0 velocity.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeInOutExpo ( double t, double b, double c, double d )
  /// @brief Exponential easing in/out, accelerating halfway, and then decelerating
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeInCirc( double t, double b, double c, double d )
  /// @brief Circular easing in, accelerating from 0 velocity.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeOutCirc( double t, double b, double c, double d )
  /// @brief Circular easing out, decelerating to 0 velocity.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeInOutCirc ( double t, double b, double c, double d )
  /// @brief Circular easing in/out, accelerating halfway, and then decelerating
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeInElastic (double t, double b, double c, double d, double a,
  ///                    double p )
  /// @brief Exponentially amplifying sine wave starting with 0 velocity and a
  ///        small amplitude.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /// @param a (optional) The amplitude.
  /// @param p (optional) The period.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeOutElastic (double t, double b, double c, double d, double a,
  ///                    double p )
  /// @brief Exponentially decaying sine wave starting with a large amplitude.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /// @param a (optional) The amplitude.
  /// @param p (optional) The period.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeInOutElastic (double t, double b, double c, double d, double a,
  ///                    double p )
  /// @brief Starts like easeInElastic and ends like easeOutElastic.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /// @param a (optional) The amplitude.
  /// @param p (optional) The period.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeInBack (double t, double b, double c, double d, double s)
  /// @brief Backtracking slightly, then reversing direction and moving to 
  ///        target.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /// @param s Controls the amount of overshoot. The greater the s, the greater
  ///          the overshoot.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeOutBack (double t, double b, double c, double d, double s)
  /// @brief Moving towards target, overshooting it slightly, then reversing 
  ///        and coming back to target.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /// @param s Controls the amount of overshoot. The greater the s, the greater
  ///          the overshoot.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeInOutBack (double t, double b, double c, double d, double s)
  /// @brief Backtracking slightly, then reversing direction and moving to 
  ///        target, then overshooting target, reversing, and finally coming
  ///        back to target.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /// @param s Controls the amount of overshoot. The greater the s, the greater
  ///          the overshoot.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeInBounce( double t, double b, double c, double d )
  /// @brief Exponentially increasing parabolic bounce.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeOutBounce( double t, double b, double c, double d )
  /// @brief Exponentially decreasing parabolic bounce.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  /// @fn easeInOutBounce( double t, double b, double c, double d )
  /// @brief Parabolic bounces increasing halfway, and then decreasing to 0.
  /// @param t The current time.
  /// @param b The beginning value.
  /// @param c The change in value.
  /// @param d The duration.
  /////////////////////////////////////////////////////////////////////////////

  double linearTween(double t, double b, double c, double d);

  double easeInQuad(double t, double b, double c, double d);
  double easeOutQuad(double t, double b, double c, double d);
  double easeInOutQuad(double t, double b, double c, double d);

  double easeInCubic(double t, double b, double c, double d);
  double easeOutCubic(double t, double b, double c, double d);
  double easeInOutCubic(double t, double b, double c, double d);

  double easeInQuart(double t, double b, double c, double d);
  double easeOutQuart(double t, double b, double c, double d);
  double easeInOutQuart(double t, double b, double c, double d);

  double easeInQuint(double t, double b, double c, double d);
  double easeOutQuint(double t, double b, double c, double d);
  double easeInOutQuint(double t, double b, double c, double d);

  double easeInSine(double t, double b, double c, double d);
  double easeOutSine(double t, double b, double c, double d);
  double easeInOutSine(double t, double b, double c, double d);

  double easeInExpo(double t, double b, double c, double d);
  double easeOutExpo(double t, double b, double c, double d);
  double easeInOutExpo(double t, double b, double c, double d);

  double easeInCirc(double t, double b, double c, double d);
  double easeOutCirc(double t, double b, double c, double d);
  double easeInOutCirc(double t, double b, double c, double d);

  double easeInElastic(double t, double b, double c, double d, double a, double p);
  double easeOutElastic(double t, double b, double c, double d, double a, double p);
  double easeInOutElastic(double t, double b, double c, double d, double a, double p);

  double easeInBack(double t, double b, double c, double d, double s);
  double easeOutBack(double t, double b, double c, double d, double s);
  double easeInOutBack(double t, double b, double c, double d, double s);

  double easeInBounce(double t, double b, double c, double d);
  double easeOutBounce(double t, double b, double c, double d);
  double easeInOutBounce(double t, double b, double c, double d);
}

#endif //EASING_EQUATIONS_H



