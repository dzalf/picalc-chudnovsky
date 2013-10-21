/*
 * pi.cpp
 * Copyright (C) 2013 Tobias Markus <tobias@markus-regensburg.de>
 * 
 */

#include <chrono>
#include <iostream>
#include <iomanip>
#include <vector>
#include <thread>
#include <future>
#include <gmp.h>
#include <gmpxx.h>
#include "pi.h"
#include "tsio.h"
#include "util.h"
#include <cstdlib>
#include <ncurses.h>

using namespace std;
using namespace picalc;

void pi::calculate(const unsigned long runs)
{
	vector<thread> t (threads);
	run_info r(runs, precision, 0, threads);

	ts << "All threads are finished." << endl;

	for (; r.phase < threads; r.phase++)
	{
		//ts << "Starting thread number " << r.phase + 1 << "." << endl;
		t[r.phase] = thread(
			[&] (run_info info)
			{
				euler e(info);
				add_sum(e.get());
				++finished_threads;
				(threads >= 10) ? \
				(ts.lprintf("\r%2u/%2u threads are finished.",	finished_threads.load(), threads)) : \
				(ts.lprintf("\r%u/%u threads are finished.", 	finished_threads.load(), threads));
			},
			r);

		/*
		t[phase] = thread(
			[&] (const unsigned long _phase, const unsigned long _runs)
			{ this->do_calculate(_phase, _runs); }
			, phase, runs);
		*/
	}

	ts << "All threads are finisheasdfasdfd." << endl;

	join_all(t);

	ts << "blabal " << endl;

	(threads >= 10) ? (ts.lprintf("\r%2u/%2u threads are finished.\n", finished_threads.load(), threads)) : \
		(ts.lprintf("\r%u/%u threads are finished.\n", finished_threads.load(), threads));

	ts << "All threads are finished." << endl;
}

/*void pi::do_calculate(const unsigned long phase, const unsigned long runs)
{
	mpf_class local_sum(0, precision);
	mpz_class n(phase + 1);
	if (phase == 0)
	{
		ts.lock();

		print_percent(0, 100);
		chrono::time_point<chrono::high_resolution_clock> start = chrono::high_resolution_clock::now();
		for (thread_local unsigned long i = 0; i <= runs; i++)
		{
			local_sum += (dividend / pow(n, 2));
			n += threads;
			if ((i % 1000) > 0|| (i < 10000))
				continue;

			chrono::time_point<chrono::high_resolution_clock> middle = chrono::high_resolution_clock::now();
			chrono::duration<double> runs_took = middle - start;
			double rel = 1.0f / ((double)i / (double)runs);
			chrono::seconds remaining_s = chrono::duration_cast<chrono::seconds>((runs_took * rel) - runs_took);
			chrono::minutes remaining_m = chrono::duration_cast<chrono::minutes>(remaining_s);
			chrono::hours   remaining_h = chrono::duration_cast<chrono::hours>  (remaining_s);
			remaining_s -= remaining_h + remaining_m;
			remaining_m -= remaining_h;

			clear_line();
			ts.lprintf("\r");
			print_percent(i, runs);
			ts << fixed << setprecision(1) << "\tEstimated remaining time: " << remaining_h.count() << "h " << remaining_m.count() << "m " << remaining_s.count() << "s";
		}
		chrono::time_point<chrono::high_resolution_clock> end = chrono::high_resolution_clock::now();
		chrono::duration<double> elapsed_seconds = end - start;
		ts.lprintf("\n");
		ts << "Calculation took " << fixed << setprecision(10) << elapsed_seconds.count() << "s" << endl;
		(threads >= 10) ? (ts.lprintf("\r 0/%2u threads are finished.", threads)) : \
			(ts.lprintf("\r0/%u threads are finished.", threads));

		ts.unlock();
	}
	else
	{
		for (thread_local unsigned long i = 0; i <= runs; i++)
		{
			local_sum += (dividend / pow(n, 2));
			n += threads;
		}
	}
	add_sum(local_sum);
	++finished_threads;
	(threads >= 10) ? (ts.lprintf("\r%2u/%2u threads are finished.", finished_threads.load(), threads)) : \
		(ts.lprintf("\r%u/%u threads are finished.", finished_threads.load(), threads));
}*/
