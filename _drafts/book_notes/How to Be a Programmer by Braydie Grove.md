[[Pragmatic Programmer]], [[Code Complete]] [CodeC93], [[Rapid Development]] , and [[Extreme Programming Explained ]]

Paul Graham and Eric Raymond

Idealists, those who think design, analysis, complexity theory, and the like are more fundamental than debugging, are not working programmers.

In fixing a bug, you want to make the smallest change that fixes the bug.

Each statement can be assigned a level and will only output a record if the system is currently configured to output that level.

There are two very fundamental techniques to improving I/O: caching and representation.

improve the locality of reference by pushing the computation closer to the data.

A classic mistake is to use a hash table as a cache and forget to remove the references in the hash table. Since the reference remains, the referent is non-collectable but useless. This is called a memory leak.

when you can define an upper bound on the number of objects you will need at one time. If these objects all take up the same amount of memory, you may be able to allocate a single block of memory, or a buffer, to hold them all. The objects you need can be allocated and released inside this buffer in a set rotation pattern, so it is sometimes called a ring buffer.

To get a working software system in active use as quickly as possible requires not only planning the development, but also planning the documentation, deployment, and marketing.

Prepare a written estimate by de-constructing the task into progressively smaller subtasks until each small task is no more than a day; ideally at most in length.

concrete things that are objective and easy to verify, for example the latest patch level of a software product, ask a large number of people politely by searching the internet

general knowledge about something subjective the history of what people have thought about it, go to the library

how to do something that is not trivial get two or three books on the subject and read them.

unique circumstance, talk to an expert.

The benefits of communication must be weighed against the costs.

Take time to really think about who will be reading your documentation, what they need to get out of it, and how you can teach that to them.

You may not be able to redesign a large block of code, but if you can add a certain amount of abstraction to it you can obtain some of the benefits of a good design without reworking the whole mess.

Part of designing the code is designing how it will be tested.

The unfortunate fact is that it is not a culture that values mental or physical health very much.

Each person needs to find a way to satisfy both their human rhythm and their work rhythm.

If programmers are asked to do something that is not beautiful, useful or nifty, they will have low morale. There's a lot of money to be made doing ugly, stupid, and boring stuff; but in the end, fun will make the most money for the company.

If no one knows about you, no trust will be invested in you.

With people that are not teammates, you may have to make a clear distinction between 'not knowing right off the top of my head' and 'not being able to figure it out, ever.'

The stress test needs to model reality well enough to be useful.

There is a certain dogma associated with useful techniques such as information hiding and object oriented programming that are sometimes taken too far.

What can you offer a potential mentor in exchange for their knowledge? At a minimum, you should offer to study hard so their time won't be wasted.

It is far better to gradually integrate things as they are completed over the course of the project.

UML is a rich formal system for making drawings that describe designs.

XML is a standard for defining new standards.

structuring the representation into a linear sequence and parsing back into a structure. It provides some nice type- and correctness-checking,

SQL is a very powerful and rich data query and manipulation language

data is the main concern of a well designed application.

In the long run, your choices of data determines how long your code will survive after you are finished with it.

The project plan exists to help make decisions, not to show how organized you are.

Never, ever, rest any hopes on vapour. Vapour is any alleged software that has been promised but is not yet available.

costs its duration multiplied by the number of participants.

Remember that a good design will be resilient against poor code implementations.

the period of bugginess and near inoperability that is often associated with software before it matures, through usage, into a usable product.

1.Is it vapour? (Promises are very immature). 
2.Is there an accessible body of lore about the software? 
3.Are you the first user? 
4.Is there a strong incentive for continuation? 
5.Has it had a maintenance effort? 
6.Will it survive defection of the current maintainers? 
7.Is there a seasoned alternative at least half as good? 
8.Is it known to your tribe or company? 
9.Is it desirable to your tribe or company? 
10.Can you hire people to work on it even if it is bad?

an obtain and integrate vs. build here and integrate

How well do your needs match those for which it was designed? 
• What portion of what you buy will you need? 
• What is the cost of evaluating the integration? 
• What is the cost of integration? 
• Will buying increase or decrease long term maintenance costs? 
• Will building it put you in a business position you don't want to be in? 


You should think twice

also consider the long term maintenance costs of both solutions. To estimate the integration costs,

something is impossible if either it cannot be grown from a simple system or it cannot be estimated.

If there is no crisp definition of success, you will not succeed.

Time-to-market pressure is the pressure to deliver a good product quickly.

Schedule pressure is the pressure to deliver something faster than it can be delivered

In a sense, a programmer should never say ‘no’, but rather to say ‘What will you give up to get that thing you want?’

Programmers cannot be hoodwinked. It is disrespectful and demoralizing to ask them to do something unrealistic.

programmer's jobs is to balance the immediate pay-off against future pay-off by wisely choosing a growth path expressed in milestones.

no large, complex system can be implemented from scratch, it can only be evolved from a simple system to a complex system in a series of intentional steps.

The best way to tell someone about a problem is to offer a solution at the same time.