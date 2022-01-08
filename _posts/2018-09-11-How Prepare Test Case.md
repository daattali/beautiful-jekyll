---
layout: post
title: How to Prepare Test Case
subtitle: Best Practices for Preparation of Test Case
tags: [sqa, software testing, testing, test case]
image: /assets/img/diary.png
bigimg: /assets/img/cover.jpg
share-img: /assets/img/diary.png
---

Consider any of your software systems under testing as Disneyland Park that you may want to explore. Of course, if you want, you can just buy tickets and visit the park as you wish. While this is fun to do, there is a good chance that you will miss out on interesting places.

In this case, all you can do is collect a map of the park. The same goes for your project, you need maps to know what to test, what you tested, what you don't need to test. And that's how the idea of ​​preparing a test case comes about. Test cases are considered to be one of the most important parts of software testing. It is used by the QA team, development as well as middle management executives.

_Qucik Link to Specific Topic:_

- [Use a clear title](#use-a-clear-title)
- [Include a strong description](#include-a-strong-description)
- [Include estimates and prerequisites](#include-estimates-and-prerequisites)
- [Keep test steps clear and concise](#keep-test-steps-clear-and-concise)
- [Make it reusable](#make-it-reusable)
- [A Complete Checklist to Check Web Application:](#a-complete-checklist-to-check-web-application)
- [Checklist During Test Execution Phase:](#checklist-during-test-execution-phase)

If we look at the quality, then the test case is the condition by which one assures that the tested product is functional up to a certain level and ready to go live.
If we look at it from the point of view of a tester, then test cases provide the conditions by which a tester performs the task of verifying the authenticity of a particular function or feature of a system.

How to write a software test case:

# Use a clear title

A good test case starts with a clear and strong title. As a standard practice, it is best to name the test case according to the module you are testing. For example, if you check the login page, include "login page" in the title of the test case.

# Include a strong description

Read the description so that the examiner can understand what they are testing. Sometimes this section may include other relevant information such as test environment, test data, and prerequisites/assumptions. Test descriptions should be easy to read and immediately understand the high-level goals and objectives of the test.

# Include estimates and prerequisites

Any assumptions applicable to the test and any prerequisites must be met before the test can be performed. This information may include which page the user should start the test on, depending on the test environment and the need for a special setup before running the test.

# Keep test steps clear and concise

Remember, the person who wrote the test case may not be the one to carry out the test himself. The test steps should include the necessary data and information on how to conduct the test. This is probably the most important part of any test case. Write the test case in such a way that anyone can follow it and test.
Include expected results
Expected Outcomes Tell the examiner what results should be obtained as opposed to their test steps. This is how the examiner determines if the test case has "passed" or "failed".

# Make it reusable

A good test case provides reusable and long-term value to the software testing team. Keep this in mind when writing a test case. You can save a lot of time by reusing the test case instead of rewriting it.
For beginners, the best practice for writing test cases is to read the software requirements document a few times until the requirements are clear and then start writing by identifying the situation based on the information provided in the required documents. For practical convenience, a test case template is provided which you can use in test case preparation.

# A Complete Checklist to Check Web Application:

- [x] Has the correct template been used?
- [x] Have the following details been filled up correctly? Requirement reference, Test script description, Author’s name, Date created, Setup Procedure, Pre-requisites – where applicable
- [x] Have the Test conditions (scenarios) been identified along with the Risk factor, if applicable?
- [x] Have all the scenarios specified in the requirement – both explicit and implicit, been converted into Test conditions?
- [x] Have the related areas that could possibly be affected by the implementation of the requirement been identified and included in the test cases? (Identify the impact areas and check with the test cases)
- [x] Has equivalence partitioning been done? Have all the classes of the domain been identified correctly?
- [x] Has the test data set, if required been generated appropriately?
- [x] Have the boundary values, special values and invalid values been identified and included in the Test data set?
- [x] Has the Test data been embedded into the test cases?
- [x] Have the required negative scenarios been identified in the test conditions?
- [x] Have the steps been correctly given in appropriate sequence for each test scenario? Steps/Actions should state very clearly the sequence of actions to be carried out on the system by the user. All statements should be definite. Ensure that terms like “If”, “In case” etc are not used.
- [x] "Have the Expected Results been identified correctly? Expected Results should clearly state how the system should respond to the user actions given in each step/action.
- [x] Ensure that too many things are not included to be verified under one expected output.
- [x] Ensure that separate cases are written for multiple verifications of the application’s behavior.
- [x] Vague statements like “Appropriate message/value/screen” etc, should not be part of expected result. Every detail should be clearly spelt out."
- [x] Are all the statements free from grammatical errors?

# Checklist During Test Execution Phase:

- [x] Have the Actual Results been updated for each of the steps? Has the actual result been documented for a failed step and for its subsequent re-runs?
- [x] Have all the steps been executed successfully? Every failed step should have retest details or some disposition if it is not fixed.
- [x] Have the defect details like Defect id, description etc. been given for a failed step?
- [x] Has the reason for the failure been recorded? (For example, invalid input data, new functionality not tested before, existing problem)
- [x] Did a peer recreate the defect before logging it in the Defects database? Have these details been documented?
- [x] Has the defect been retested and if so, have the retest details and the result documented along with the date on which the retest was done?
- [x] Have the Execution details like executed by and executed date, been filled up correctly
- [x] Have the results from different environments (Browsers, for example) been recorded? (If applicable)
- [x] Have the metrics related to the test cases been updated in all applicable metrics documents? (Number of Test cases prepared, executed, Number of test case executions with defects, Total Number of defects etc.)
- [x] Are all the statements free from grammatical errors?

{: .box-success}
Enjoy !!!
See Yaaa, Next.
