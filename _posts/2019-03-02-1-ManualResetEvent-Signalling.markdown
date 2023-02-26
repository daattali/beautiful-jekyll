---
layout: post
title:  "Signalling Thread using ManualResetEvent"
date:   2019-03-02 15:11:00 -0800
categories: Technical
---

ManualResetEvent and AutoReset Event are some of the most important classes provided by the .Net Framework. These are used for the purpose of singalling threads (start/stop) etc and having a detailed knowledge of the these classes are very important for every developer. 

In this blog entry I will try to how ManualResetEvent works and how it can be used for the purpose of signalling. ManualResetEvent is  like a manned gate. If the gate is open it will allow any number of vehicles to go in until it is manually closed. Manualreset event maintains a state (Boolean:true/false). If it is set to true, then the gate is open and the call to WaitOne will return true else if set to false the call to WaitOne will return false.

![alt text][ManualResetEvent]

Important Methods in the ManualResetEvent Are

1) Set()
2) WaitOne()
3) Reset()

![alt text][ManualResetEvent1]

Below is an example which demonstrates the use of ManualResetEvent to keep recording the performance counter values until user takes some action, in which case it calls set. 

 WaitOne blocks the thread for a certain period of time and returns its state in this case its false, so it continues in the loop. When the user takes some action, set is called which set the state to true and the threads come out of the loop.

 I personally love these signalling mechanisms.


```csharp
void Main()
{
	System.Threading.EventWaitHandle stopper = new ManualResetEvent(false);
	new Thread(() => Monitor("Processor", "% Processor Time", "_Total", stopper)).Start();
	new Thread(() => Monitor("LogicalDisk", "% Idle Time", "C:", stopper)).Start();
	Console.WriteLine("Monitoring - press any key to quit");
	Console.Read();
	stopper.Set();
}

public static void Monitor(string category, string counter, string instance, EventWaitHandle stopper)
{
	if (!PerformanceCounterCategory.Exists(category))
	{
		throw new InvalidOperationException("Category does not exist");
	}
	
	if (!PerformanceCounterCategory.CounterExists(counter, category))
	    throw new InvalidOperationException("Counter does not exist");
		
    float lastValue = 0f;
	using (var pc = new PerformanceCounter(category, counter, instance))
	{
		while(!stopper.WaitOne(200, false))
		{
			float value = pc.NextValue();
			if (value != lastValue)
			{
				Console.WriteLine(value);
				lastValue = value;
			}
		}
	}
}
```


[ManualResetEvent]: https://loneshark99.github.io/images/ManualResetEvent.PNG "ManualResetEvent State"

[ManualResetEvent1]: https://loneshark99.github.io/images/ManualResetEvent1.PNG "ManualResetEvent.WaitOne()"