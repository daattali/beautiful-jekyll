---
layout: post
title: What is Software Requirements
subtitle: Everything About Software Requirements
tags:
  [business system analysis, system analysis, business analysis, requirement]
image: /assets/img/diary.png
bigimg: /assets/img/back.gif
thumbnail-img: /assets/img/diary.png
share-img: /assets/img/diary.png
cover-img: /assets/img/cover.jpg
---

Requirement is a description of the service that software must offer. A requirement can range from the high-level abstract statement of the sender's necessity to detailed mathematical functional requirement specifications.

Software requirement is a functional or non-functional need to be implemented in the system. Functional means providing particular service to the user. For example, in context to banking application the functional requirement will be when customer selects "View Balance" they must be able to look at their latest account balance.

Software requirement can also be a non-functional; it can be a performance requirement. For example, a non-functional requirement is where every page of the system should be visible to the users within 5 seconds.

_Quick Links to Topic:_

- [Overview of Requirement](#overview-of-requirement)
	- [What is Requirement?](#what-is-requirement)
	- [Requirements Can be Categorized in the following:](#requirements-can-be-categorized-in-the-following)
	- [Functional Requirements:](#functional-requirements)
	- [Non-Functional Requirements:](#non-functional-requirements)
	- [Product Constraints:](#product-constraints)
	- [What Makes a Good Requirements?](#what-makes-a-good-requirements)
- [SMART Requirement](#smart-requirement)
- [Tips for producing valid requirement](#tips-for-producing-valid-requirement)
- [Terms to Avoid:](#terms-to-avoid)
- [Business Rules](#business-rules)
	- [Business Rules Vs Business Requirement](#business-rules-vs-business-requirement)

# Overview of Requirement

Why Do I Need Requirements?
- Guides the design of the eventual solution.
- Without correct requirements, you cannot design or build the correct product.

**About 60% of project failures originate with the requirements.**

## What is Requirement?

Something a product must do or a quality it must have. Software requirement is a functional or non-functional need to be implemented in the system.

## Requirements Can be Categorized in the following:

    1. Function Requirements:
    	a. Things the product must do.
    	b. Action the product must take.
    2. Non-Functional Requirements:
    	a. Properties or qualities the product must have.
    	b. How the product will behave.
    3. Constraints
    	a. Global Requirement:
    		i. Purpose of the project
    		ii. Users of a product

## Functional Requirements:

- Scope of the Product – defines the boundaries and connections to other products
- Functional and Data Requirements – Things the product must do and data manipulated by the functions

**Functional Requirements Example:**
- The product must track recipes down the ingredient and quantity level
- The recipes must be editable by an administrator
- The product must display the orders that need to be completed
- The product must display the recipes to make the orders
- The product must track ingredients including their cost, vendors, and quantity in inventory
- The product must interact with the current Point of Sale system

## Non-Functional Requirements:

    • Look and Feel Requirements – intended appearance
    • Usability Requirements – based on the intended users
    • Performance Requirements – how fast, big, accurate, safe, reliable, etc.
    • Operational Requirements – product’s intended operating environment
    • Maintainability and Portability Requirements – how changeable product must be
    • Security Requirements – security, confidentiality, and integrity of the product
    • Cultural and Political Requirements – human factors
    • Legal Requirements – conformance to applicable laws

**Non-Functional Requirements Example:**

- The product shall use the company colors and logos
- The product shall be intuitive, even to first time users
- The product shall only allow bakers and administrators to view recipes
- The product shall be easily upgraded for future business needs
- The product shall be scalable to multiple bakery locations

## Product Constraints:

    • Purpose of the Product – reason for building the product
    • Client, Customer, and Stakeholders – people that interact with the product'
    • Users of the Product – intended end-users and how they affect product usability
    • Requirements Constraints – limitations of the project and restrictions on design
    • Naming Conventions and Definitions – vocabulary of the product
    • Relevant Facts – outside influences that make a difference to this product
    • Assumptions – assumptions developers are making

**Product Constraint Example:**

- The product budget must not exceed $50,000
- The product shall run on the company’s existing machines
- Implementation of the product cannot interrupt daily business
- The last 5 years of historical data needs to be made available in the product

## What Makes a Good Requirements?

A can make a long list of word like:
☑ Accountable, ☑ Understandable, ☑ Attainable, ☑ Modifiable, ☑ Testable, ☑ Traceable, ☑ Measurable, ☑ Feasible, ☑ Allocable, ☑ Concise, ☑ Consistent, ☑ Complete, ☑ Correct, ☑ Feasible, ☑ Design Independent, ☑ Necessary, ☑ Organized, ☑ Unambiguous, ☑ Prioritized, and so on.

But we will use SMART formula like setting goal.

# SMART Requirement

**SMART** = Specific, Measurable, Attainable, Reasonable, Traceable
What is a SMART Requirement?

    1. Specific:
    Overall:
    	○ Clear, no ambiguity
    	○ Consistent, same terminology throughout
    	○ Simple

    Question to Ask:
    	○ What?
    	○ Why?
    	○ Who ?
    	○ Where?

    Guidelines:
    	○ Avoid "Some", "Several", "Many"
    	○ State pronouns clearly "A calls B it is updated".
    	○ Specify units all with numbers
    	○ Use pictures to clarify understanding
    	○ Provide explanations for terms like "Transmitted", "Sent", "Downloaded", and "Processed"

    2. Measurable:
    	Overall:
    		○ Measure progress towards goal
    		○ Indicators should be quantifiable

    	Question to Ask:
    		○ How much?
    		○ How many?
    		○ How will I know when it is accomplished?

    	Guidelines:
    		○ Ensure measurable during requirement elicitation
    		○ Validate unequivocal success can be proven with that requirement
    		○ Determine tests that will need to be used to verify the requirement was met.
    3. Attainable :
    	Overall:
    		○ Validate requirement is feasible
    			□ Within technical expertise
    			□ Within scope of project
    			□ Within budget
    		○ Sanity check of the project

    	Question to Ask:
    		○ Is there a theoretical solution to the problem?
    		○ Has it been before?
    		○ Are there any known constraint (environment, political, etc.)?

    	Guidelines:
    		○ Determine who has responsibility for satisfying the requirement and validate they can deliver
    		○ Ensure sufficient time, resources, and budget
    		○ Reuse pieces from previous projects.
    4. Reasonable:
    	Overall:
    		○ Validate the effort is worth the requirement

    	Question to Ask:
    		○ Is this worthwhile?
    		○ Is the timing right?
    		○ Does this match our other effort/ needs

    	Guidelines:
    		○ Run all requirements through a "sanity check'
    		○ Ensure the requirement makes sense in context
    5. Traceable:
    	Overall:
    		○ Trace requirement through design, implementation, and testing

    	Question to Ask:
    		○ Can I ensure this requirement has been met in the design solution?
    		○ Can I ensure this requirement has been met in the implementation?
    		○ Can I ensure this requirement has been met in during testing?

    	Guidelines:
    		○ Requirement should include:
    			□ Originators
    			□ Assumptions
    			□  Business justifications
    			□ Dependencies on other requirements
    			□ Importance

# Tips for producing valid requirement

Tips for Producing Valid Requirement:
- Should use the word shall
- Only one shall per requirement
- Written in short, simple sentences
- Consistent terminology
- Stated positively
- Accompanied by notes and comments to support and clarify
- Stated imperatively
- Don’t use will and should
  Tips for Producing Valid Requirement:
- Or – Select one of the options
- Can, should – Expresses desire or suggestion instead of requirement
- Must – 100% reliability
- Are, is, will – Descriptive part to lead into the requirement
- Support, and/or – Confusing
- But not limited to, etc. – Incomplete requirement/thought
- Shall – dictates specification and functional capability

# Terms to Avoid:
• Adequate • Approximately • Better than • Comparison • Easy • Maintainable • Maximize • Minimize • Normally • Optimize • Quality product • Quick • Rapid • Substantial • Sufficient • Timely

**Phase of the Requirements Process:**
1. Requirement Elicitation
2. Requirement Analysis
3. Requirement Specification
4. Requirements Approval


# Business Rules
- What are Business Rules?
- Business Rules vs Business Requirements
- Best Practices

Business Rules Explained

**Definition:** A business rule is a rule that defines or constrains some aspect of business and always resolves to either true or false. Rules is like the system must do this or must not do this. It is always either black or white. Yes or No. Not the both.

**Example:**
- You must be home by curfew.
- Entered email addresses must appear valid (contain @ and .)
- Each class must have at least one instructor
- Customers must have a valid driver’s license to rent a vehicle
- A quote must be completed prior to an invoice being generated

Then business requirement will help you to fulfill that rule. Like Wearing a watch that alarm before 30 minutes of curfew.

**Purpose:** Business rules are intended to assert business structure or to control or influence the behavior of the business.

## Business Rules Vs Business Requirement

**Rule:** Entered email addresses must appear valid (contain @, then later .)

**Possible Requirements:**
- Capability to enter email address
- Alert agent when the email doesn’t appear to be valid
- Allow for correction of email if invalid email format is entered

**Rule:** Each course must have at least one instructor

**Possible Requirements:**
- Capability for Dean to assign instructor to course
- Course registration cannot be opened until an instructor is assigned

**Rule:** Customers must have a valid driver’s license to rent a vehicle

**Possible Requirements:**
- Employee to inspect driver’s license
- Ability for employee to validate driver’s license

**Rule:** A quote must be completed prior to an invoice being generated

**Possible Requirements:**
- Capability to enter a quote
- Details from quote must automatically flow to the invoice
- Ability to tie the quote and invoices together for reporting

**Business Rules Best Practices:**
- When documenting business rules, keep it simple.
- Business requirements are used to comply with business rules. Keep them both in same document
- Each business rule may need multiple requirements
- Business rules should not be changed
- Changes can cause major constraints down the road

{: .box-success}
Enjoy !!!
See Yaaa, Next.

For Any Query or Task Contact Me @
[![Linkedin](https://img.shields.io/badge/-LinkedIn-blue?style=flat&logo=Linkedin&logoColor=white)](https://www.linkedin.com/in/rafayet13/)
[![Gmail](https://img.shields.io/badge/-Gmail-c14438?style=flat&logo=Gmail&logoColor=white)](mailto:rafayet13@gmail.com)
