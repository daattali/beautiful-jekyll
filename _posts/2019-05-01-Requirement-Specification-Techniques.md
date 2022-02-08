---
layout: post
title: Requirements Specification Techniques
subtitle: Requirements Specifications
tags:
  [
    business system analysis,
    system analysis,
    business analysis,
    requirement elicitation,
  ]
image: /assets/img/diary.png
bigimg: /assets/img/back.gif
thumbnail-img: /assets/img/diary.png
share-img: /assets/img/diary.png
cover-img: /assets/img/cover.jpg
---

Section: Requirement Specifications

In previous lectures and in previous sections we talk about requirements elicitation where we worked through and pulled out those requirements out of stakeholders and out of documentation and understood what the as-is process and the to-be process was to look like. We then went through and did requirement analysis where we took those requirements we wrote them in multiple ways so groups, whether there are technical groups or business groups, can understand them and we created visual models to help do that. Now this is a third stage, this is requirement specification.

And really what we're doing here is we're taking those requirements that we have and we're categorizing them, we're breaking them down. So if one requirements a little long or convoluted what may be driving them into multiple requirements so it's a little bit more easier to read in plain and simple. So we're categorizing, we're deriving those requirements and then we're prioritizing the requirements. And it's very important that you prioritize requirements, that you put a kind of a level of priority with them because as the project moves forward and you have your scheduled date that you're trying to hit for the implementation you don't want to be at the place where you're 90% through the project you realize you're not going to get every single requirement in and now trying to circle back to the business to find out what, you know, based on what you haven't done, what could you leave out.

That is the wrong time to do it, you're going to spin your wheels and you're going to cause a lot of against. So prioritizing requirements within this step is very important. And then finally, as a last step to this requirement specification you're getting validation of those requirements. So you're going back to the business and making sure that they approve of the requirements at least from a few stakeholders. And that's kind of to make sure that you're on the right track. That way as you move into the final phase of requirements the requirements approval.

Lecture: Categorizing Requirements
One of the first steps in the requirements specification phase is to categorize requirements and so really what this means is breaking the requirements down into functional, nonfunctional or supplemental and constraint requirements. And this helps in a lot of different areas.

Why Categorize Requirement?

    1. Aids in documentation
    2. Helps to prioritize
    3. Assist Estimating the system cost.
    4. Identifies areas that require further investigation.

Categories of Requirement:

    1. Functional Requirements:
    	a. Things the product must do.
    	b. Action product must take
    2. Non-Functional Requirements:
    	a. Properties or qualities the product must have
    	b. How the product will behave
    3. Constraints:
    	a. Global Requirements :
    		i. Purpose of the project
    		ii. Users of the project.

you've elicited and now you're going to go through in and categorize them all out.

Lecture: Deriving Requirements
Your captured requirement is document may required further development through derived. And deriving requirement is about three key things: 1. Adding further details 2. Adding clarity to this requirement 3. Removing ambiguity.

Techniques that you can utilize to deriving requirement:
• Parsing Requirement
• Interpreting Requirements
• Focusing Requirements
• Qualifying Requirements.

    1. Parsing Requirements:
    § Breaking down requirements that are too broad.
    § Removing "and" from requirements
    	- Risk is high that only one of the conditions will be tested
    	- Hard to trace the requirement bug/ failure

Example: Breaking Down
• Original Requirement:
○ “User-completed fields on tax forms shall be converted to electronic text documents.”
• Parsed Requirements:
○ “The system shall be able to convert handwriting to text.”
○ “The system shall be able to convert machine print to text.”
○ “The system shall be able to electronically correct user-completed fields.

    2. Interpreting Requirements:

§ Reduce generalness and ambiguity of stated requirements .
Example:
• Original Requirement:
○ “Each PC shall have state-of-the-art software installed.”
• Interpreted Requirement:
○ “Each PC shall have Microsoft Office 2013 and Windows 10 installed.”
• Parsed Requirements:
○ "Each PC shall have Microsoft Office 2013 installed.”
○ “Each PC shall have Windows 10 installed."

    3. Focusing Requirements:

• Combine overlapping requirements into one focused requirement.
Example:
• Original Requirement:
• “Each PC must have a standard spreadsheet tool installed that runs in Windows.”
• Focused Requirement:
• “Each PC on the LAN shall have Microsoft Office Excel 2013.”

    4. Qualifying Requirements:

• Add a requirement to provide a method of verification or compliance .
Example:
• Original Requirement:
• “The xxx command must perform the following actions…”
• Qualified Requirement:
• “Each command shall be executed during system testing to demonstrate its functionality.”

Lecture: Assigning Requirement Attributes
Why Assign Requirement Attributes : 1. Clarification: More details 2. Filtering: Filter by type functional, non-functional, constraints, and priority. 3. Validation: Requirement met the business need.

Typical Attributes:
• Unique Identifier: A unique identifier means that that identifier is unique to that specific requirement. It never changes.
• Acceptance Criteria: what is the criteria that's going to use to validate that that has been met?
• Author: who's actually writing the requirements?
• Complexity: how hard is this going to be to implement in scale of 1 to 10?
• Ownership: a group, the department that's been affected by the requirement (Not the raiser).
• Performance: If there is any performance attribute like how fast it should response.
• Urgency: How quickly it is needed, in which iteration of agile approach?
• Business Value: What business value it will add.
• Status: Started, Confirmed, Developed, Tested, etc.
• Type: Functional, Non- Functional, Constraints.
• Priority: High, Medium, Low
• Source: Who raise this, in case any clarification is needed to whom to consult?

Lecture: Prioritizing Requirement
Why Prioritize Requirement:
Generally there are too many functions and features to implement within the project schedule and budget.

Prioritize Factors:
• Value to the business
• Value to the customer
• Minimize cost to develop
• Time to implement
• Ease of technical implementation
• Ease of business implementation
• Obligation to some external authority

Three (03) Step Prioritization Process: 1. Define usefulness to business (critical, important, nice to have) 2. Estimate cost (1-5 scale) 3. Determine timeframe (1-5 scale)

Requirement Prioritization Best Practices:
• Keep it simple
• Business value reigns supreme
• Remove prioritization away from politics
• Prioritize (and re-prioritize) after each project iteration

\*\*\*Validate your requirement using SMART formula.

Lecture: Business Requirement Document (BRD)
Business Requirement Document (BRD) Basics:
What is a Business Requirements Document?
It's a document that houses all of the requirements, the business rules, the use cases, the version history, stakeholders, basically everything that you're eliciting as part of the requirements of the project are documented within here.
Who prepares it?
Well it's pretty obvious. The business analyst is responsible for filling out the BRD and making sure that it's complete and accurate. And that's really what's utilized as you move into the next phases of the project to pass the requirements phase.
What is it used for?
Number one it houses all of the requirements for the specific project. That's the most critical use of the business requirements document is to house all of those requirements. Information of Stakeholder mapping, approvals, etc. will be kept here. Eventually the original system shall be design, implemented, and tested based on this document.
What is the standard format?
No there is no standard but it is pretty obvious that every organization use a BRD format based on their needs. But most of the information are almost similar.
One question that comes up a lot is 'hey, when do I fill this out?', you'll see as we go through kind of an example template and format that it's a pretty formal document. You have your elicitation, then you have your analysis, then your specification, then your validation. So in the elicitation that's when you're meeting with everyone, that's when you're doing all your different elicitation activities and at that time I'm not documenting inside of a BRD, I'm trying to write good requirements, write SMART requirements because I don't want to rewrite them all later, is when I start to put a lot of the details into the BRD and also in the specification phases when I kind of finalize that.

{: .box-success}
Enjoy !!!
See Yaaa, Next.

![Diary](/assets/img/diary.png "Diary")
