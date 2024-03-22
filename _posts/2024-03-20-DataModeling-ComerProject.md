---
layout: post
title: Data Modeling - Comer project
subtitle: Practice to make a data modeling for Comer project (web application - solo project)
# thumbnail-img: /assets/img/rootMe/11d59cb34397e986062eb515f4d32421.png
tags: [MongoDB, data modeling, user case, NOSQL]
comments: true
author: Lantana Park
---

<!-- [Comer Website](https://comer-experience-app.onrender.com/) -->

![myproject](/assets/img/comerProject/Screenshot%202024-03-20%20at%2020.49.53.png)

Node.js, Express.js, Mongoose, MongoDB(NoSQL)

## User Case (Entities)

1. **Users:**

   They have the capability to create an account, view booked experiences, and access their previously opened events. Users can also edit their profiles. They also can find forgotpassword and reset the password. They cannot save prevously saved password, so it should not be matched with the current password and old one. To sign up, individuals must provide an email address, create a password, and confirm that password again. Upon submitting this information, they will receive an email containing a verification token. This token is appended to a URL(user will be redirected to this url address); clicking on the hyperlinked URL in the email activates the user's account, allowing them to participate in any desired activities on the website. If users complete to verify their email addresses, the email token string will change from a string to a null value. Additionally, users can reset their passwords once their email addresses are found in the database. In this sitation, emailToken will be issued. Once user click the url sent to their email address, the emailToken will be changed into null. And then user can reset the password, which should not be matched with the previously saved password. Finally, users can delete their accounts, which will change their isActive status to false, not deleting whole data.

   ![login](/assets/img/comerProject/Screenshot%202024-03-20%20at%2020.51.19.png)

2. **Experiences:**

   Users can create/edit events. They can upload image files, which are stored on AWS S3 bucket. The event details, including title, description, perks (such as food, beverages, transportation, equipment, and others), guest requirements (minimum age, allowance of kids and pets, maximum group size), languages spoken, general availability (start time, end time, date range), tags, price with currency, additional notes for consideration by users, likes from other users, and cancellation policy, are stored in the database. To facilitate event location, information such as country, city, state, address (including street number), longitude, latitude, coordinates, and full address are also stored in the database. These location details are provided via the Mapbox library from the client side.

   ![opening1](/assets/img/comerProject/Screenshot%202024-03-20%20at%2020.54.14.png)

   ![opending2](/assets/img/comerProject/Screenshot%202024-03-20%20at%2020.54.33.png)

   ![event](/assets/img/comerProject/Screenshot%202024-03-20%20at%2020.58.49.png)

   ![even2](/assets/img/comerProject/Screenshot%202024-03-20%20at%2020.59.01.png)

3. **Comments:**

   Users are able to create and delete comments on the detailed event pages. An experience page may contain multiple comments. When a comment is posted, the user ID and experience ID are stored as foreign keys, along with the comment's description.

   ![comment](/assets/img/comerProject/Screenshot%202024-03-20%20at%2021.00.40.png)

4. **Availiabilities:**

   When a user opens their event, an availability entity is created based on data from the start time, end time, and date range (Experience entity). This entity includes the experience ID as a foreign key, dateMaxGuestPairs, booking information (to track who booked the event), and a timestamp. Within the dateMaxGuestPairs, objects are stored that include details such as the date, start time, end time, maximum number of guests allowed, price, and current status. When an event is booked by a user, the number of maximum guests allowed is accordingly decreased. In addition to it, an object (including date, slotId, userId, experienceId, experienceTitle, UserEmail, startTime, endTime) will be created in the availibilities.booking array.

   ![list](/assets/img/comerProject/Screenshot%202024-03-20%20at%2021.01.26.png)

## ER Diagram

```
erDiagram

    USER {
        string _id PK "Unique identifier"
        string email "Email address"
        string password "Hashed password with salt"
        boolean isActive "Status indicating if the user's account is active"
        boolean isVerified "Status indicating if the user's email is verified"
        string emailToken "Token for email verification process"
        dateTime createdAt "Creation Timestamp"
        dateTime updatedAt "Last Update Timestamp"
    }

     EXPERIENCE {
        string _id PK "Unique identifier"
        string userId FK "Reference to User"
        string title "Title of the Experience"
        string[] language "Languages Offered"
        string description "Brief Description"
        number runningTime "Duration in Minutes"
        number minimumAge "Minimum Age Requirement"
        string country "Country"
        string city "City"
        string state "State (if applicable)"
        string address "Street Address"
        number longitude "Longitude"
        number latitude "Latitude"
        string[] coordinates "String version of longitude and latitude"
        string fullAddress "Full Postal Address"
        string[] files "Associated Files (e.g., images)"
        string[] likes "User Likes - userId"
        object perks "Perks Object"
        string notice "Special Notice from Host"
        string startTime "Starting Time"
        boolean kidsAllowed "Kids Allowed"
        boolean petsAllowed "Pets Allowed"
        string endTime "Ending Time"
        number maxGuest "Maximum Number of Guests"
        number price "Price"
        string currency "Currency"
        string[] tags "Experience Tags"
        dateTime startDate "Start Date"
        dateTime endDate "End Date"
        boolean cancellation1 "Cancellation Policy - Condition 1"
        boolean cancellation2 "Cancellation Policy - Condition 2"
        dateTime createdAt "Creation Timestamp"
        dateTime updatedAt "Last Update Timestamp"
    }

    PERKS {
         string food "Description of Food Provided"
         string beverage "Description of Beverages Provided"
         string transportation "Description of Transportation Provided"
         string alcohol "Description of Alcohol Provided"
         string equipment "Description of any equipment Provided"
         string others "Description of any others Provided"
    }

    COMMENT {
        string _id PK "The unique identifier of the comment."
        string userId FK "Associates the comment with its author."
        string experienceId FK "Links the comment to the relevant experience."
        string description "The content of the comment."
        dateTime createdAt "Creation Timestamp"
        dateTime updatedAt "Last Update Timestamp"
    }

    AVAILABILITY {
        string _id PK "Unique identifier for availability record"
        string experienceId FK "Reference to Experience"
        object[] dateMaxGuestPairs "Array of Date, Time, and Guest Information"
        object[] booking "Array of booking detailed information"
        dateTime createdAt "Creation Timestamp"
        dateTime updatedAt "Last Update Timestamp"
    }

    DATEMAXGUESTPAIR {
        string _id PK "Unique identifier for date-maxGuest pair"
        dateTime date "Date of Availability"
        string startTime "Start Time"
        string endTime "End Time"
        number maxGuest "Maximum Number of Guests"
        number price "Price"
        string currency "Currency"
    }

    BOOKING {
        string _id PK "Unique identifier for booking"
        dateTime date "Date of Booking"
        string slotId FK "Reference to DateMaxGuestPair"
        string userId FK "User who made the booking"
        string experienceId FK "Reference to Experience"
        string experienceTitle "Title of the Experience"
        string userEmail "Email of the User"
        string startTime "Start Time"
        string endTime "End Time"
        dateTime createdAt "Creation Timestamp"
        dateTime updatedAt "Last Update Timestamp"
    }

    USER ||--o{ EXPERIENCE : "creates/edits/likes"
    USER ||--o{ COMMENT : "creates/deletes"
    AVAILABILITY ||--o{ DATEMAXGUESTPAIR : "includes"
    AVAILABILITY ||--o{ BOOKING : "includes"
    DATEMAXGUESTPAIR ||--|| BOOKING : "booked for"
    EXPERIENCE ||--o{ COMMENT : "includes"
    EXPERIENCE ||--o{ PERKS : "has"
    EXPERIENCE ||--o{ AVAILABILITY : "has"
```

![diagram](/assets/img/comerProject/mermaid-diagram-2024-03-21-112751.png)
