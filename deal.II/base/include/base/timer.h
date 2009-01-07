//---------------------------------------------------------------------------
//    $Id$
//    Version: $Name$
//
//    Copyright (C) 1998, 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2009 by the deal.II authors
//
//    This file is subject to QPL and may not be  distributed
//    without copyright and license information. Please refer
//    to the file deal.II/doc/license.html for the  text  and
//    further information on this license.
//
//---------------------------------------------------------------------------
#ifndef __deal2__timer_h
#define __deal2__timer_h

#include <base/config.h>

DEAL_II_NAMESPACE_OPEN

/**
 * This is a very simple class which provides information about the time
 * elapsed since the timer was started last time. Information is retrieved
 * from the system on the basis of clock cycles since last time the computer
 * was booted. On a SUN workstation, this information is exact to about a
 * microsecond. 
 *
 *
 * <h3>Usage</h3>
 *
 * Use of this class is as you might expect by looking at the member
 * functions:
 * @code
 *   Time timer;
 *   timer.start ();
 *
 *   // do some complicated computations here
 *   ...
 *
 *   timer.stop ();
 *
 *   std::cout << "Elapsed CPU time: " << timer() << " seconds.";
 *   std::cout << "Elapsed wall time: " << timer.wall_time() << " seconds.";
 *
 *   // reset timer for the next thing it shall do
 *   timer.reset();
 * @endcode
 *
 * Alternatively, you can also restart the timer instead of resetting
 * it. The times between successive calls to start()/ stop() will then be
 * accumulated. The usage of this class is also explained in the
 * @ref step_12 "step-12" and @ref step_29 "step-29" tutorial programs.
 *
 * @note Implementation of this class is system
 * dependent. Unfortunately, it does not work with multithreading
 * right now. In this case, we would like to sum up the time needed by
 * all children.
 *
 * @ingroup utilities
 * @author G. Kanschat, W. Bangerth
 */
//TODO:[?] make class work with multithreading as well. better docs.
class Timer
{
  public:
				     /**
				      * Constructor. Starts the timer at 0 sec.
				      */
    Timer ();

				     /**
				      * Re-start the timer at the point where
				      * it was stopped. This way a cumulative
				      * measurement of time is possible.
				      */
    void start ();

				     /**
				      * Sets the current time as next
				      * starting time and return the
				      * elapsed time in seconds.
				      */
    double stop ();

				     /**
				      * Stop the timer if necessary and reset
				      * the elapsed time to zero.
				      */
    void reset ();

				     /**
				      * Access to the current CPU time
				      * without disturbing time
				      * measurement. The elapsed time is
				      * returned in units of seconds.
				      */
    double operator() () const;

				     /**
				      * Access to the current wall time
				      * without disturbing time
				      * measurement. The elapsed time is
				      * returned in units of seconds.
				      */
    double wall_time () const;

  private:

				     /**
				      * Value of the user time when start()
				      * was called the last time or when the
				      * object was created and no stop() was
				      * issued in between.
				      */
    double              start_time;


				     /**
				      * Similar to #start_time, but
				      * needed for children threads
				      * in multithread mode. Value of
				      * the user time when start()
				      * was called the last time or
				      * when the object was created
				      * and no stop() was issued in
				      * between.
				      *
				      * For some reason (error in
				      * operating system?) the
				      * function call
				      * <tt>getrusage(RUSAGE_CHILDREN,.)</tt>
				      * gives always 0 (at least
				      * on Solaris7). Hence the
				      * Timer class still does not
				      * yet work for multithreading
				      * mode.
				      */
    double              start_time_children;

				     /**
				      * Value of the wall time when start()
				      * was called the last time or when the
				      * object was created and no stop() was
				      * issued in between.
				      */
    double              start_wall_time;

				     /**
				      * Accumulated time for all previous
				      * start()/stop() cycles. The time for
				      * the present cycle is not included.
				      */
    double              cumulative_time;

				     /**
				      * Accumulated wall time for all
				      * previous start()/stop() cycles. The
				      * wall time for the present cycle is
				      * not included.
				      */
    double              cumulative_wall_time;

				     /**
				      * Store whether the timer is presently
				      * running.
				      */
    bool                running;
};

DEAL_II_NAMESPACE_CLOSE

#endif
