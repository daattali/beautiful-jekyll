---
layout: post
published: true
title: 'Do I Need to test my code?'
subtitle: 'What should I test?'
date: '2019-07-20'
image: /assets/img/test.jpeg
share-img: /assets/img/test.jpeg
tags: [tests, notes]
---

It is difficult to find any developer who does not agree with the title of this publication, even more, if asked in a job interview. Although, some developers took what Kent Beck once said ["I get paid for **code that works**, not for tests"](https://stackoverflow.com/questions/153234/how-deep-are-your-unit-tests/153565#153565) as a license to not create tests at all. I think we should take his words with special care. He did not mean that you should not develop tests because you are not paid for that, but that you must _concentrate_ on your production code.

Tests are important because they give you confidence when you make changes and ensures a certain level of quality in the service being tested. They also serve as some kind of documentation of the expected behavior of a piece of code. But everything needs moderation, no tests might be as harmful as too many bad tests. 

Now, if the title question creates debate, the subtitle is even worse...

## What should I test? 

I know of companies that do not care at all about test coverage, others that think anything below 90% is bad. So, *how much testing is enough?*

### Do I need 100% Coverage?

Continuing with Kent Beck quotes I would like to bring one of your tweets on this topic:

> Being proud of 100% test coverage is like being proud of reading every word in the newspaper. Some are more important than others.
>
> --Kent Beck (@KentBeck) [Dec 24, 2016](https://twitter.com/kentbeck/status/812703192437981184)

Also, as pointed in his book [Extreme Programming Explained: Embrace Change](https://www.amazon.com/dp/0201616416/):

> It is impossible to test absolutely everything, without the tests being as complicated and error-prone as the code.

Testing everything will probably lead you to perform non-orthogonal tests, which increases the likelihood that when you make a small change in your code, thousands of tests will be broken. Then, you spend more time fixing tests than creating **code that works**.

When making small changes causes many tests to break, developers are afraid to make changes because each time this happens they feel frustrated and unproductive. If we take into consideration that one of the reasons for testing is to feel safe when making changes to the production code, then we can agree that there is something wrong with the equation.

So, no, I don't think you need 100% coverage. I know that is a controversial statement, there are some good reasons to argue the contrary, but I think that the pros of that aren't enough to aim for 100% coverage.

## What is (not) a Unit Test?

Sometimes is easier to define something by saying what is NOT, and Michael Feathers can help us with that. For him [a test is not a unit test if:](https://www.artima.com/weblogs/viewpost.jsp?thread=126923)

> It talks to the database
> It communicates across the network
> It touches the file system
> It can't run at the same time as any of your other unit tests
> You have to do special things to your environment (such as editing config files) to run it.

You might ask: Why? Well, mainly because tests that do that sort of thing are generally slow and cause unstable tests. The idea of tests is to give you quick feedback on your code; If something broke or if you have the desired behavior; If you have tests that work sometimes and fail other times without obvious reasons, you will lose confidence in your tests, ignore them because "it is normal for these tests to fail".

Finally, unit tests must be quick, they are designed to give you quick feedback. You should not have to think twice before executing them. If they are slow, they lose their reason. Developers will not execute them so often, they will avoid wasting that time.

### Should I test third-party libraries?

Well, if you do it, for sure it won't be an easy task. Steve Freeman in his book [Growing Object-Oriented Software, Guided by Tests](https://www.amazon.es/Growing-Object-Oriented-Software-Guided-Signature/dp/0321503627) has a couple of good arguments to persuade you to avoid it:

> Depending on the quality of the library might be hard to get the right state to be able to test it.

When you use a third-party library, you must adapt to its design implementation. You gain the value of what they provide but lose some freedom in the implementation. Sometimes, that design is not easy to test and will require a lot of work just to establish the correct state to be able to test it. Also, you have to deal with the second point:

> Pain to keep test up to date with upgrades to the library.

Even if you are using an open-source library and can redefine the API to facilitate testing and use for your purpose, you will have to spend some time each time a library update is required.

So, what should we do? No tests at all? No. Define an adapter, test the adapter. And later test these adapters with focused integration tests to confirm your understanding of how the third-party API works.

There are some exceptions where mocking third-party libraries can be helpful. We might use mocks to simulate behavior that is hard to trigger with the real library, such as throwing exceptions. Similarly, we might use mocks to test a sequence of calls, for example making sure that a transaction is rolled back if there’s a failure.

### Testing private methods

In [Pragmatic Unit Testing](https://www.amazon.es/Pragmatic-Unit-Testing-Junit-Programmers/dp/0974514012), Dave Thomas and Andy Hunt write:

> Most of the time, you should be able to test a class by exercising its public methods. If there is significant functionality that is hidden behind private or protected access, that might be a warning sign that there's another class in there struggling to get out.

A private method usually is an implementation detail. Testing implementation details is not good for your health. Usually causes that when you do a small refactor many tests fail. You should be able to test your classes through its public methods.

### Testing implementation Details

Programmer tests should be sensitive to behavior changes and insensitive to structural changes. You write a new test when you need to fulfill a new requirement, no because you created a new method or class. That means that you should not write a new test just because you refactored the code, a refactor is a structural change, hence the behavior should remain the same.

When you test implementation details instead of behavior there are a couple of things that can go wrong:

*  Break when you refactor application code.  **False negatives**
*  Not fail when you break the application code.  **False positives**

The first one, because your test is highly coupled to the structure of your application code. The second one, because you are testing structure, not behavior.
 
To put closure on this subject I would like to quote Ryan Fynke. In [his article](https://teamgaslight.com/blog/testing-behavior-vs-testing-implementation) he found an elegant way to put the difference between testing implementation details and behavior:

>### When I test for behavior, I’m saying:
>“I don’t care how you come up with the answer, just make sure that the answer is correct under this set of circumstances”
>### When I test for implementation, I’m saying:
>“I don’t care what the answer is, just make sure you do this thing while figuring it out.”

PD: Just for fun, read [this](http://edw519.posthaven.com/it-takes-6-days-to-change-1-line-of-code) story.