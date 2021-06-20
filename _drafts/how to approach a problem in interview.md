---
created: 2021-04-25T17:09:48+05:30
modified: 2021-04-25T17:10:51+05:30
---

"There is a web application built in Stack Whatever. It gives the user a read-only field that says the number of toasters in the company's inventory, and a form containing a text field and submit button for ordering a specific number of toasters. An end user reports that the toaster counter did not update when he submitted two toasters to order. What would you do to find the source of this problem? Provide as much detail as you can."

1. Do I have a testing environment available, and how extensive is it? Do I have a test machine I can deploy to? Is there a test database? Is there a Postman collection available for sending calls to the test version of the API?

 2. Is there an error log available? If I'm lucky, I might see an error in the log after reproducing the bug.

When the questions about the problem description are taken care of, you can start getting to the root of the issue. This will require some involvement on the interviewer to say what the interviewee will see after doing whatever it is they will do. Here is an example of how such a conversation would go from that point:

 1. "I'll try to reproduce the bug on the test version. Do I see the reported problem there?" 

 1. "You see that the count updated properly on your attempt to reproduce the bug."

 2. "Perhaps something was deployed incorrectly. If I deploy the front end on another test machine and point to the already deployed test back end, am I still unable to reproduce the error?" 

 1. "Yes, the error is still not there."

 3. "If I also deploy the back end to the machine I deployed the duplicate front end and point the duplicate front end to it, am I still unable to reproduce the error?" 

 1. "The error is still not there."

 4. "I look into the backend call code used when the toaster count is updated. How does the call update the database?" 

 1. "It calls the stored procedure spUpdateToasters with a single integer parameter called count. The stored procedure then returns an integer representing the revised toaster count. This count is then returned in the API response."

 5. "How does the backend connect to the database? Does it use something like Kerberos, or does it use an explicit SQL user?" 

 1. "It uses an explicit SQL user. The connection string is loaded from config file app.config. The username and password are also located in this connection string."

 6. "I try to connect to the database myself using the supplied username and password on the test database, and open spUpdateToasters. I then do the same in the production database. Do I see a difference between the two stored procedures?" 

 1. "Although you are successful in opening the stored procedure in test, you are unable to open the stored procedure in production. It claims you do not have access to the database containing the stored procedure."

 7. "I feel confident that may be the problem. Can I add the permission myself or open a ticket for giving the SQL user access?" 

 1. "The permission is now applied to the user after your request. Also, to answer your previous question, you do not see a difference between the test and prod versions of the stored procedure once you connect to prod."

 8. "I see. Now I ask the ticket reporter to try reproducing the bug again." 

 1. "The ticket reporter now says the bug is gone." 