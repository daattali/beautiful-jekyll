---
layout: post
title: Change Control Process in SDLC
subtitle: Change Control Process in Software Engineering
tags:
  [
    business system analysis,
    system analysis,
    business analysis,
    requirement elicitation,
    change management,
    change control,
  ]
image: /assets/img/diary.png
bigimg: /assets/img/back.gif
thumbnail-img: /assets/img/diary.png
share-img: /assets/img/diary.png
cover-img: /assets/img/cover.jpg
---

What is Change Control?
Change Control is the process that a company uses to document, identify and authorize changes to an IT environment. It reduces the chances of unauthorized alterations, disruption and errors in the system.
Why Change Control?
Whenever any new or different changes are requested for the system, especially by stakeholders, it is neither optional nor ignorable. It has to be implemented without affecting other components of the system. This is when the change control comes handy. It helps project teams to modify the scope of the project using specified controls and policies. Change Control is practiced whenever a project is not progressing as planned.
It is mandatory that a formal document for change request is completed and reviewed in order to keep control of change requests.
Number of question one might encounter while analyzing Change Control like
• Who will approve the change?
• Does it require to run through a change control board?
• How much time will be required to research and implement the change?
• What are the impacts of changes to other components of the system (schedules, cost, resources, etc.)?
• Is there any threshold under which the project management can approve it?

Different factors of Change Control process
There are various factors that a Change Control process should consider
Steps in Change Control Process Action taken in Change Control
• Change request initiation and Control • Request for changes should be standardized and subject to management review
• Change requestor should be kept informed
• Impact Assessment • Make sure that all requests for change are assessed in a structured way for analyzing possible impacts
• Control and Documentation of Changes • A change log should be maintained that tells the date, person details who made changes and changes implemented
• Only authorized individual should be able to make changes
• A process for rolling back to the previous version should be identified
• Documentation and Procedures • Whenever system changes are implemented the procedures and associated document should update accordingly
• Authorized Maintenance • System access right should be controlled to avert unauthorized access
• Testing and User signoff • Software should be thoroughly tested
• Version Control • Control should be placed on production source code to make sure that only the latest version is updated
• Emergency Changes • A verbal authorization should be obtained, and the change should be documented as soon as possible

Process of Change Control
Before we look into what is involved in Change Control process, we will get familiarize with what documents are used in Change Control. While carrying out Change Control, there are mainly two documents involved
• Change Log: A change log is a document that list the details about all the Change Requests like project number, PCR (project change request) ID, priority, Owner details, Target date, status and status date, raised by, date when raised etc.

• Change Request Form: It is used to document details required to support the decision making process like type of change, benefits of change, name of resource requesting the change, time and estimate cost, priority of change, authorized person detail, change request status etc.

Change Process Flow-Diagram
Change Process follows a specific pattern to implement the changes in the product or system. Here through flow-diagram we explained what are the steps involved in the Change Process.

Steps for Change Control
Steps for Change Control Action
• Change request identification • Identify the need for a change and describe it on the project change request form
• Change request assessment • If the change is not valid, it has to be deferred or rejected
• Determine appropriate resources required to analyze the change request
• Perform quick assessment of the potential impact and update the change request form
• At this stage, rejected change request should stopped
• Change request analysis • For analysis assign the change request to an authorized member
• Deferred change re-enter this analysis step
• At this stage, rejected change request should stopped
• Change request approval • Identify change risk and complexity level before approval
• Identify the impact level of the change before approval
• Review impact of Change Request to authorized person for approval
• At this stage, rejected change request should stopped
• Change request implementation • Update project procedure and management plans
• Inform about the changes to the team
• Monitor progress of change request
• Record the completion of change request
• Close change request
NOTE: The approval for Change Control may be done by Project Manager, Lead IT or Lead Developer, Stakeholder.
Change Management Vs Change Control
Change Management Change Control
• It is responsible for managing and controlling change requests to effect changes to the IT infrastructure or any aspect of IT services to minimize the risk of disruption of services and promoting business benefit • Change control includes activities like submission, recording, analyzing and approval of change to improve the overall performance of the system or product

Impact Analysis in Software Testing
What is Impact Analysis?
Impact Analysis is defined as analyzing the impact of changes in the deployed product or application. It gives the information about the areas of the system that may be affected due to the change in the particular section or features of the application.
The impact is analyzed on Requirements, Design & Architecture, impact on Test and impact on schedule.
With the incorporation of new features into application or product, it becomes imperative to check the influence of these new features or changes on the performance of the system. For this reason, Impact Analysis is done.

Why is Change Impact Analysis is done?
• It is done to understand the possible outcome of implementing the change. Inducing too much functionality into a product can reduce the overall performance of the product.
• To identify all the files, documents and models that might have to be modified if a team decides to implement the change in product
• To estimate the effort needed behind implementing the change
• To identify the task required to implement the change
• It will list the dependencies on a specific element
What is Impact Analysis Document?
Impact Analysis document can be used as a checklist. It is used to evaluate change request before working on them. The Impact Analysis document should give details like
• Brief description of an issue
• Explain or show an example of how the defect is causing failure and/or inefficiency
• Include an estimate of complexity
• Include an estimate of cost and time for a fix
• Functionality to be tested
• List down the new test cases created for the change
• Reference document- Mention the reference document, technical specification, etc.
Example:
Impact Analysis Document.

1. Change Request ID:
2. Title:
3. Description:
4. Date Prepare:
5. Prioritization estimate:
   o Relative Benefit
   o Relative Penalty
   o Relative cost
   o Relative risk
6. Estimated total effort: …..hours
7. Estimated lost effort: ……..hours
8. Estimated schedule Impact:……days
9. Quality Impacted;
10. Other Requirement affected:
11. Other tasks affected:
12. Integration issues:
    How to present Impact Analysis influence level
    Impact Analysis can be marked as per the color code to represent the criticality of the changes or impact of the changes over the system. The color code could be anything as shown below.
    • Red- Strong
    • Yellow- Moderate
    • Green- Weak

The above table explains the impact of the implemented changes
• Features that are marked with red indicates the main features which are changed, those with yellow are the features that are less influenced by the change and those with the green are the least one.
• Features mentioned vertically resembles those features that are changed while horizontally those features are mentioned which performed changes can influence. For example, in above example the change in feature 1 influence the feature3
• For a larger project where features and functionalities are more then above table may not be of any use. In such case, another approach is adopted, where developer straightaway marks the level of influence due to the changes in main features. As shown below where the impact of the Main feature is marked for respective sub-features.

Sample Questions to be addressed for performing Impact Analysis
• What are the adverse side effects or risks of making the proposed change?
• Does any tool be acquired in order to implement and test the change?
• If the change is accepted how much effort will be lost that is already been invested?
• Does a proposed change adversely affect performance requirements?
• To verify the proposed change does other user input be required?
• Does the change increase the product cost?
• Does the proposed change is something the current staff has knowledge and skills?
• Does the proposed change place any unacceptable demand on any computer resource?
Best practices for change Impact Analysis
• Before initiating with Impact Analysis, make sure testing request contained no information about those part of the project that was influenced by changes
• Continue communication between developer and tester is must, not to miss any change needed to implement in the final product
• Identify if any user interface changes, deletions or additions are required.
• Estimate the number of acceptance, system or integration test cases that will be required
• Identify any impact of the proposed change to another project plan, configuration management plan or quality assurance plan.
Summary
• The impact analysis will assure what part of an application need to be changed
• The impact on the system is analyzed on Requirements, Design & Architecture, impact on Test, etc.
• It helps to analyze what level of regression testing is required

For Any Query or Task Contact Me @
[![Linkedin](https://img.shields.io/badge/-LinkedIn-blue?style=flat&logo=Linkedin&logoColor=white)](https://www.linkedin.com/in/rafayet13/)
[![Gmail](https://img.shields.io/badge/-Gmail-c14438?style=flat&logo=Gmail&logoColor=white)](mailto:rafayet13@gmail.com)

{: .box-success}
Enjoy !!!
See Yaaa, Next.
