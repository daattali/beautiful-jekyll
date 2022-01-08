---
layout: post
title: Software Testing Process
subtitle: An Introduction to Test Activities
tags: [sqa, software testing, testing, test process, test activities]
image: /assets/img/diary.png
bigimg: /assets/img/cover.jpg
thumbnail-img: /assets/img/diary.png
share-img: /assets/img/diary.png
---

Testing is not a single activity but a whole process. This process begins with test planning and ends with test case design, test execution, and evaluation. Therefore, we can divide the basic functions of the testing process into certain steps:

1. Planning & Control
2. Analysis & Design
3. Implementation & Execution
4. Evaluating Exit Criteria & Reporting
5. Test Closing Activities

_Qucik Link to Specific Topic:_

- [Planning & Control](#planning--control)
- [Analysis and design](#analysis-and-design)
- [Implementation and Execution:](#implementation-and-execution)
- [Exit criteria and report evaluation:](#exit-criteria-and-report-evaluation)
- [Test closing activities:](#test-closing-activities)

Let's learn more about the different steps of testing activity:

# Planning & Control

1.1) The main functions of test planning are:

1. Test scope and risk determination and identification of testing objectives.
2. To determine the test method
3. Test policy, test strategy implementation
   - Test strategy is an outline that describes part of the software development cycle. It is designed to inform project managers, testers, and developers about some of the key aspects of the testing process.
   These include test objectives, test procedures, total time and manpower required for the project and testing environment
4. Determining the required test resources such as manpower, test environment, PC, Smartphone, etc. required for the test.
5.Test Analysis and Schedule of Design, Test Implementation, Execution, and Evaluation.
6. To determine the exit criteria. We need to set criteria like coverage criteria.
   - Coverage Criteria is the percentage of software statement; it is advisable to complete as much as possible during the test. This will help us to find out if we are performing the test activities correctly.

1.2) The main tasks performed in test control are:

1. Measure and analyze the review and test results.
2. Monitoring and documenting the progress of test coverage and exit criteria.
3. Provide test information.
4. Initiate corrective activities.
5. Making decisions.

# Analysis and design

The main tasks of test analysis and test design are:

1. Review the test basis.
   -The information required to initiate test analysis and create our own test case is the basis of the test. Basically, it is the document on which the test case is based, such as Requirement, Design Specification, Product Risk Analysis, Architecture, and Interface. Using Test Basis Document Once we have created the system we understand what it should do.
2. Identify test conditions.
3. Test design.
4. Evaluate the requisite and testability of the system.
5. Design the test environment setup and identify the necessary infrastructure and equipment.

# Implementation and Execution:

  During the implementation and application of the test, we accept the test conditions in the test case and method and other tests such as automation script, test environment, and any other test infrastructure. A **test case** is a set of conditions under which an examiner will determine if an application is working properly.

3.1) The tasks that are done in test implementation are:

1. Develop and prioritize our test cases using techniques and create test data for those tests. 
 - To test a software application, you will need to input some data for most feature tests. The specifically identifiable data used in the test is known as test data.)

We also write some instructions for running tests which is known as the test method.
We may need to automate some tests using some automated test scripts and test harnesses. (Test harness is a collection of some software and test data to monitor the behavior and results of different program units operating in different situations.)

1. To create a test suit of effective test execution from the test case. (The test suite is used to test a set of test cases that contains a specific set of behaviors in a software program. The test suite's system configuration often contains detailed instructions and information for each collection of test cases for use during the test. Is used.)
2. To implement and verify the test environment.

3.2) All the work done in test execution is:
1. To implement test suites and individual test cases by following the test procedure.
2. To perform the test again to make sure that any previously failed tests have been fixed. This is known as confirmation testing or re-testing.
3. To log the result of the test application and to record the identity and version of the software under test. Used for audit test logs.
- The test log is tested, why it was tested, who performed the test and what is the status of the test case (pass/fail). These statements are recorded and are called test logs.
4. To compare the actual result with the expected result.
5. To report discrepancies as facts where there are differences between actual and expected results.

# Exit criteria and report evaluation:

Based on the project risk assessment we will set criteria for each test level against which we will measure "test adequacy". These criteria vary from project to project and are known as exit criteria. The exit criteria come in the picture, when: -
-Most test cases are executed with a certain pass percentage.

- Bug rate drops below a certain level.
- Arrives on time for the project.

The main tasks in the exit criteria assessment are:

1. To verify the test logs against the specific exit criteria in the test plan.
2. If further tests are needed to determine whether or not the specific departure criteria should be changed.
3. To write a test summary report for the stakeholders.

# Test closing activities:

Test Closure activities are performed after the software has been provided. Testing may be stopped for other reasons such as:
When all the information required for the test is collected.
When a project is canceled.
When some goal is achieved.
When a maintenance release or update is completed.

The tasks that need to be done in the test closure activity are:

1. To verify which planned deliverables are provided and to ensure that all incident reports have been resolved.

2. To finalize and save for testware reuse like test script, test environment, etc.
3. To transfer the test equipment to the maintenance organization. They will provide software support.
4. To evaluate how the test is going and to learn lessons for future publications and projects.

{: .box-success}
Enjoy !!!
#See Yaaa, Next
